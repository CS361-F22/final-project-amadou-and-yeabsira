
#include <cmath>
#include <string>

class Task {
public:
  virtual double CheckOutput(int output, int inputs[4]) = 0;
  virtual std::string name() = 0;
};


class Task_1 : public Task {

   public:
     double CheckOutput(int output, int inputs[4]) override {   
          return output;
     }
     public: 
     //returns the name of the task solved
     std::string name() override{
        std::string n = "Send_Self_ID";
        return n;
     }

};


