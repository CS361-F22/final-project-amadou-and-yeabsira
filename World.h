#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "Task.h"
#include "Org.h"
#include <stdlib.h>

class OrgWorld : public emp::World<Organism> {
  emp::Random &random;
  std::vector<emp::WorldPosition> reproduce_queue;
  std::vector<Task *> tasks{new Task_1(),new Task_2(),new Task_3(),new Task_4(),new Task_5()};
  std::vector<std::string> task_name;
  int task_index;
  int highestID = 0;

 
  
  

public:
 float reward;
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
     output = task->CheckOutput(output, state.last_inputs, reward);
     state.points += output;
     if(output!=0){
       std::cout << task->name();
       task_name[task_index] = task->name();
       task_index++;
     }
    }
  }
  struct Cell{
        int x;
        int y;
        int size;
        int seq_id;
        int random_id;
     };
     
Cell cell[25];

  void processCell(int x, int y, Organism organism){

    int cell_id = 0;

    cell[cell_id].size = 5 * 5;
    cell[cell_id].x = x;
    cell[cell_id].y = y;
    cell[cell_id].random_id = rand() % 100 + 4000000;
    cell[cell_id].seq_id = x*y;
    organism.SetSeqID(cell[cell_id].seq_id);
    cell_id++;
    
  }

  //returns the task name of the solved task
  std::string GetTask(int i){
    return task_name[i];
  }
  void resetTask(int i){
    task_name[i] = "";
  }
  void ReproduceOrg(emp::WorldPosition location) {
    // Wait until after all organisms have been processed to perform
    // reproduction. If reproduction happened immediately then the child could
    // ovewrite the parent, and then we would be running the code of a deleted
    // organism
    reproduce_queue.push_back(location);
  }

  int getLeader(){
    
    emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    for(int i : schedule) {
      if(!IsOccupied(i)) {continue;}
      std::cout << pop[i]->GetSeqId();
      if(pop[i]->GetSeqId()>highestID){
        highestID=pop[i]->GetSeqId();
      }
    }
    return highestID;
  }


//   int getDemeIndex(int x, int y){
//     std::vector<std::vector<int>> cells;
//     cells.resize(100, std::vector<int>(100, 0));
//     for(int m = 0;m<10;m++){
//       for(int k = 0;k<10;k++){
//         for(int i = 0;i<6;i++){
//           for(int j = 0;j<6;j++){
//             cells[i+(6*m)][(j+(6*k))] = k+1;
//           }
//         }
//       }
//     }
//     return cells[x][y];
//  }
};

#endif