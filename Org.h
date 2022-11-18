#ifndef ORG_H
#define ORG_H

#include "CPU.h"
#include "OrgState.h"
#include "emp/Evolve/World_structure.hpp"
#include <iostream>
#include <list>

class Organism {

  CPU cpu;
  std::vector<int> inbox = {};
  int offspring_id = 20;
  int org_pos;

public:
  Organism(OrgWorld *world, int _seqID, double points = 0.0) : cpu(world) {
    SetPoints(points);
    SetSeqID(_seqID);
    

  }
  
  void SetPoints(double _in) { cpu.state.points = _in; }
  void AddPoints(double _in) { cpu.state.points += _in; }
  double GetPoints() {return cpu.state.points;}
  bool GetSolved() {return cpu.state.solved;}

  void Reset() {
    cpu.Reset();
  }

  void Mutate() {
    cpu.Mutate();
  }

  std::optional<Organism> CheckReproduction() {
    
    if (this->GetPoints() > 20) {
      Organism offspring = *this;
      offspring.Reset();
      offspring.SetSeqID(offspring_id);
      offspring_id++;
      offspring.Mutate();
      offspring.AddPoints(-20);
      return offspring;
    }
    return {};
  }

  void Process(emp::WorldPosition current_location) {
    cpu.state.current_location = current_location;
    cpu.RunCPUStep(10);
    // if(GetMaxId()==599){
    //   inbox.clear();
    // }
    //AddPoints(0.1);
    //TODO: Run the CPU!

  }

  void PrintGenome() {
    std::cout << "program ------------" << std::endl;
    cpu.PrintGenome();
    std::cout << "end ---------------" << std::endl;
  }

  int GetMaxId(){
    int maxId = 0;
    for(int i = 0;i<inbox.size();i++){
      if(inbox[i]>maxId){
        maxId = inbox[i];
      }
    }
    return maxId;
  }

  int GetSeqId(){
    return cpu.state.Seq_ID;
  }
  void SetSeqID(int Id){
    cpu.state.Seq_ID = Id;
  }
  int GetPos(){
    return org_pos;
  }
  void SetPos(int pos){
    org_pos = pos;
  }
  void SendMsg(int msg, emp::Ptr<Organism> destination){
    destination->RecMsg(msg);
    
  }
  void RecMsg(int msg){
    inbox[0] = msg;
    
  }
  int GetInbox(int index){
   return inbox[index];
  }

  
};

#endif