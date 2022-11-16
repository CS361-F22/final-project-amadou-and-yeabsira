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

public:
  Organism(OrgWorld *world, int _seqID, double points = 0.0) : cpu(world) {
    SetPoints(points);
    SetSeqID(_seqID);
    

  }
  int getFacing(int pos){
    return 5;
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
    
    if (GetPoints() > 20) {
      Organism offspring = *this;
      offspring.Reset();
      offspring.SetSeqID(offspring_id);
      offspring_id++;
      offspring.Mutate();
      AddPoints(-20);
      return offspring;
    }
    return {};
  }

  void Process(emp::WorldPosition current_location) {
    cpu.state.current_location = current_location;
    cpu.RunCPUStep(10);
    //TODO: Run the CPU!

  }

  void PrintGenome() {
    std::cout << "program ------------" << std::endl;
    cpu.PrintGenome();
    std::cout << "end ---------------" << std::endl;
  }

  int GetMaxId(){

  }

  int GetSeqId(){
    return cpu.state.Seq_ID;
  }
  void SetSeqID(int Id){
    cpu.state.Seq_ID = Id;
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