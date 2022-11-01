
//in web.cpp at the VERY top
#define UIT_VENDORIZE_EMP
#define UIT_SUPPRESS_MACRO_INSEEP_WARNINGS
#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"
#include "emp/config/ArgManager.hpp"
#include "emp/prefab/ConfigPanel.hpp"
#include "emp/web/UrlParams.hpp"
#include "ConfigPanel.h"


MyConfigType config;
emp::web::Document doc{"target"};
emp::web::Document settings("settings");


class Animator : public emp::web::Animate {
    const int num_h_boxes = 50;
    const int num_w_boxes = 50;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::web::Canvas canvas{width, height, "canvas"};
    emp::Random random{config.SEED()};
    OrgWorld world{random};

public:


//Constructor for the class that sets up the Gui for the animation
Animator() {    
        
        
        auto specs = emp::ArgManager::make_builtin_specs(&config);
        emp::ArgManager am(emp::web::GetUrlParams(), specs);
        am.UseCallbacks();
        if (am.HasUnused()) std::exit(EXIT_FAILURE);
        emp::prefab::ConfigPanel config_panel(config);
        config_panel.SetRange("Population", "1", "25");
        settings << config_panel;
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        doc << "\n\n\n" << "The starting organisms and their off springs are trying to solve 5 tasks defined as some Mathematical function. As they keep solving the tasks successfully, they are able to gain points which subsequently determines whether they are able to reprdocue or not. They then trasnfer their genome to their offspring which creates a favorable condition for evolution. The change in color observed as they keep reproducing represents the five different tasks.";
        random.ResetSeed(config.SEED());
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
        for(int i = 0;i<config.Population();i++){
         Organism* new_org1 = new Organism(&world, 1);
         world.Inject(*new_org1);
        }

        world.Resize(num_w_boxes, num_h_boxes);


        
}


void DoFrame() override {
        canvas.Clear();
        world.Update();
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++){
            for (int y = 0; y < num_h_boxes; y++) {
                if (world.IsOccupied(org_num)) {
                    Organism organism = world.GetOrg(org_num); 
                    for(int i = 0;i<1;i++){                         //Change the real time color of the cells depending on the task solved
                        if(world.GetTask(i)=="abs"){
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                        }
                        if(world.GetTask(i)=="trig"){
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "blue", "blue");
                        }
                        if(world.GetTask(i)=="log"){
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "green");
                        }
                        if(world.GetTask(i)=="floor"){
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "grey", "grey");
                        }
                        if(world.GetTask(i)=="ceil"){
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "red", "red");
                        }
                    }

                }
                else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "yellow", "yellow");
                }
                org_num++;
            }
        }
    }
    
};

Animator animator;

int main() {
    animator.Step();
}





