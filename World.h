#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "Task.h"
#include "Org.h"
#include <stdlib.h>
#include<cstdlib>

class OrgWorld : public emp::World<Organism> {
  emp::Random &random;
  std::vector<emp::WorldPosition> reproduce_queue;
  std::vector<Task *> tasks{new Task_1()};
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

    SetPosWorld();

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
      for (Task *task : tasks) {
        emp::Ptr<Organism> currentOrg;
        srand(task->CheckOutput(output, state.last_inputs));
        int sent = rand()%100;
        currentOrg = initiateMsg(state.Seq_ID, sent);
        if(!currentOrg){continue;}
        //std::cout << "Sent: " << sent << " - " << "SeqId: " << currentOrg->GetSeqId() << std::endl;
        if(sent==currentOrg->GetSeqId()){
          std::cout << "seq_id" << std::endl;
          state.points += 0.1;
        }
        if(sent==currentOrg->GetMaxId()){
         //std::cout << "max_id" << std::endl;
         state.points += 0.2;
        }
        if(sent!=currentOrg->GetSeqId()){
         //std::cout << "non_id" << std::endl;
         state.points -= 0.1;
        }
      }
  }

  emp::Ptr<Organism> initiateMsg(int org, int msg){
    
      emp::Ptr<Organism> sender = getOrgByID(org);
      int neighbour  = getFacing(sender->GetPos());
      if(IsOccupied(neighbour)){
        emp::Ptr<Organism> reciever = &GetOrg(neighbour);
        sender->SendMsg(msg,reciever);
        return sender;
      }
      return NULL;
      
    
  }

  void SetPosWorld(){
    emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    for(int i : schedule) {
      if(!IsOccupied(i)) {continue;}
        pop[i]->SetPos(i);
    }
  }

  

  emp::Ptr<Organism> getOrgByID(int id){
    emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    for(int i : schedule) {
      if(!IsOccupied(i)) {continue;}
      if(pop[i]->GetSeqId()==id){
        pop[i]->SetPos(i);
        return pop[i];
      }
    }
    return NULL;
  }


  int getFacing(int pos){
    emp::WorldPosition new_position = GetRandomNeighborPos(pos);
    return new_position.GetIndex();
  }

  // Organism getLeader(){
  //   emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
  //   for(int i : schedule) {
  //     if(!IsOccupied(i)) {continue;}
  //     if(pop[i]->GetSeqId()==id){
  //       pop[i]->SetPos(i);
  //       return pop[i];
  //     }
  //   }
  //   return NULL;
  // }

  


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