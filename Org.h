#ifndef ORG_H
#define ORG_H

#include "CPU.h"
#include "OrgState.h"
#include "emp/Evolve/World_structure.hpp"

class Organism {
  CPU cpu;

public:
  Organism(OrgWorld *world, double points = 0.0) : cpu(world) {
    SetPoints(points);

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
};

#endif