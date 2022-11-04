
#include <cmath>
#include <string>
#include <iostream>

class Task {
public:
  virtual double CheckOutput(uint32_t output, uint32_t inputs[4]) = 0;
  virtual std::string name() = 0;
};


class Task_1 : public Task {

   public:
   //return a double if the organism manages to fidn the trig function of the input numbers
     double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
         for (int i = 0; i < 4; i++) {
          uint32_t cube = cos(inputs[i]) / inputs[i];
          if (fabs(output - cube) < 0.001) {
              return 0.1;
          }
        }
         return 0;
     }
     public: 
     //returns the name of the task solved
     std::string name() override{
        std::string n = "trig";
        return n;
     }

};

class NOT : public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    // did they calculate NOT of a number?
    for (int i = 0; i < 4; i++) {
    uint32_t not_val = ~inputs[i]; //~ is bitwise NOT in C++
      if (not_val == output) {
        // 10 points for success
        return 10.0;
    }
    // 0 points for failure
    return 0.0;
  }

  public:
     //returns the name of the task solved
     std::string name() override{
        std::string n = "NOT";
        return n;
     }

};
