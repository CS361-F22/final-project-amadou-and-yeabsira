#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "Task.h"
#include "Org.h"

class OrgWorld : public emp::World<Organism> {
  emp::Random &random;
  std::vector<emp::WorldPosition> reproduce_queue;
  std::vector<Task *> tasks{new Task_1(),new Task_2(),new Task_3(),new Task_4(),new Task_5()};
  std::vector<std::string> task_name;
  int task_index;
  
  

public:
int count;
  OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) { }

  ~OrgWorld() {}

  const pop_t &GetPopulation() { return pop;}

  void Update() {

    emp::World<Organism>::Update();
    
    
    
    //Process each organism
    emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    for(int i : schedule) {
      if(!IsOccupied(i)) {continue;}
      pop[i]->Process(i);
    }

    //Time to allow reproduction for any organisms that ran the reproduce instruction
    for (emp::WorldPosition location : reproduce_queue) {
      if (!IsOccupied(location)) {
        return;
      }
      std::optional<Organism> offspring =
          pop[location.GetIndex()]->CheckReproduction();
      if (offspring.has_value()) {
        DoBirth(offspring.value(), location.GetIndex());
      }
    }
    reproduce_queue.clear();
  
  }
  //Check whether the task has been complemted by the organism and assing points based on the result
  void CheckOutput(float output, OrgState &state) {
    task_index = 0;
    for (Task *task : tasks) {
     output = task->CheckOutput(output, state.last_inputs);
     state.points += output;
     if(output!=0){
       std::cout << task->name();
       task_name[task_index] = task->name();
       task_index++;
     }
    }
  }

  //returns the task name of the solved task
  std::string GetTask(int i){
    return task_name[i];
  }
  void ReproduceOrg(emp::WorldPosition location) {
    // Wait until after all organisms have been processed to perform
    // reproduction. If reproduction happened immediately then the child could
    // ovewrite the parent, and then we would be running the code of a deleted
    // organism
    reproduce_queue.push_back(location);
  }
};

//  int getDemeIndex(int x, int y){
    
//     for(int i = 0;i<6;i++){

//     }
//  }

#endif