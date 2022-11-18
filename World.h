#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "Task.h"
#include "Org.h"
#include <stdlib.h>
#include <cstdlib>
#include "emp/data/DataFile.hpp"

class OrgWorld : public emp::World<Organism>
{
  emp::Random &random;
  std::vector<emp::WorldPosition> reproduce_queue;
  std::vector<Task *> tasks{new Task_1()};
  std::vector<std::string> task_name;
  int leader;
  int task_index;
  int highestId = 99;
  int highestIdCount = 0;
  int nonHighestIdCount = 1;

public:
  float reward;
  int count;
  emp::Ptr<emp::DataMonitor<int>> data_node_messagesCount; // data node to track messages
  OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {}

  /*
    Destuctor of data nodes
  */
  ~OrgWorld() {if (data_node_messagesCount)
      data_node_messagesCount.Delete();}

  const pop_t &GetPopulation() { return pop; }

  void Update()
  {

    emp::World<Organism>::Update();

    // Process each organism
    emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    for (int i : schedule)
    {
      if (!IsOccupied(i))
      {
        continue;
      }
      pop[i]->Process(i);
    }

    SetPosWorld();

    // Time to allow reproduction for any organisms that ran the reproduce instruction
    for (emp::WorldPosition location : reproduce_queue)
    {
      if (!IsOccupied(location))
      {
        return;
      }
      std::optional<Organism> offspring =
          pop[location.GetIndex()]->CheckReproduction();
      if (offspring.has_value())
      {
        DoBirth(offspring.value(), location.GetIndex());
      }
    }
    reproduce_queue.clear();
  }

  emp::DataMonitor<int>& GetMsgCountDataNode() {
if(!data_node_messagesCount) {
    data_node_messagesCount.New();
    OnUpdate([this](size_t){
    data_node_messagesCount -> Reset();
    for (size_t i = 0; i < pop.size(); i++)
        if(IsOccupied(i))
        data_node_messagesCount->AddDatum(1); // each organism sends 1 message per update
    });
}
return *data_node_messagesCount;
}

emp::DataFile & SetupMsgFile(const std::string & filename) {
    auto & file = SetupFile(filename);
    auto & node1 = GetMsgCountDataNode();
    file.AddVar(update, "update", "Update");
    file.AddTotal(node1, "count", "Total number of messages");

    file.PrintHeaderKeys();

    return file;
  }

  // Check whether the task has been complemted by the organism and assing points based on the result
  void CheckOutput(float output, OrgState &state)
  {
    for (Task *task : tasks)
    {
      emp::Ptr<Organism> currentOrg;
      int output = task->CheckOutput(output, state.last_inputs);
      srand(output);
      int sent = rand() % 1000;
      currentOrg = initiateMsg(state.Seq_ID, sent);
      if (!currentOrg)
      {
        continue;
      }
      if (sent != highestId)
      {
        // std::cout << "No: " << nonHighestIdCount <<std::endl;
        nonHighestIdCount++;
      }
      else
      {
        std::cout << "Yes: " << highestIdCount << std::endl;
        highestIdCount++;
      }

      // std::cout << "Percent: " << highestIdCount/nonHighestIdCount << std::endl;
      std::cout << "Max-ID: " << currentOrg->GetMaxId() << std::endl;
      if (sent == currentOrg->GetSeqId())
      {
        // std::cout << "seq_id" << std::endl;
        state.points += reward;
      }
      if (sent == currentOrg->GetMaxId())
      {
        // std::cout << "max_id" << currentOrg->GetMaxId() << std::endl;
        state.points += reward;
      }
      if (sent != currentOrg->GetSeqId())
      {
        // std::cout << "non_id" << std::endl;
        state.points -= 0.1;
      }
    }
  }

  emp::Ptr<Organism> initiateMsg(int org, int msg)
  {

    emp::Ptr<Organism> sender = getOrgByID(org);
    int neighbour = getFacing(sender->GetPos());
    if (IsOccupied(neighbour))
    {
      emp::Ptr<Organism> reciever = &GetOrg(neighbour);
      sender->SendMsg(msg, reciever);
      return sender;
    }
    return NULL;
  }

  void SetPosWorld()
  {
    emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    for (int i : schedule)
    {
      if (!IsOccupied(i))
      {
        continue;
      }
      pop[i]->SetPos(i);
    }
  }

  emp::Ptr<Organism> getOrgByID(int id)
  {
    emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    for (int i : schedule)
    {
      if (!IsOccupied(i))
      {
        continue;
      }
      if (pop[i]->GetSeqId() == id)
      {
        pop[i]->SetPos(i);
        return pop[i];
      }
    }
    return NULL;
  }

  int getFacing(int pos)
  {
    emp::WorldPosition new_position = GetRandomNeighborPos(pos);
    return new_position.GetIndex();
  }

  bool isLeader()
  {
    int percentageMax = highestIdCount / nonHighestIdCount;
    if (percentageMax >= 0.95)
    {
      return true;
    }
    return false;
  }

  // returns the task name of the solved task
  std::string GetTask(int i)
  {
    return task_name[i];
  }
  void resetTask(int i)
  {
    task_name[i] = "";
  }
  void ReproduceOrg(emp::WorldPosition location)
  {
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