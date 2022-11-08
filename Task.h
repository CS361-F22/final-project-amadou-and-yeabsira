
#include <cmath>
#include <string>

class Task {
public:
  virtual double CheckOutput(float output, float inputs[4], float reward) = 0;
  virtual std::string name() = 0;
};


class Task_1 : public Task {

   public:
   //return a double if the organism manages to fidn the trig function of the input numbers
     double CheckOutput(float output, float inputs[4], float reward) override {
         for (int i = 0; i < 4; i++) {
          float cube = cos(inputs[i]) / inputs[i];
          if (fabs(output - cube) < 0.001) {
              std::cout << "Cubbed!" << std::endl;
              return reward;
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


class Task_2 : public Task {

   public:
   //return a double if the organism manages to find the log base 10 of the input numbers
     double CheckOutput(float output, float inputs[4], float reward) override {
         for (int i = 0; i < 4; i++) {
          float log = log10(inputs[i]);
          if (fabs(output - log) < 0.001) {
              std::cout << "Logarithm!"  << std::endl;
              return reward;
          }
        }
         return 0;
     }
    public: 
    //returns the name of the task solved
     std::string name()  override {
        std::string n = "log";
        return n;
     }

};



class Task_3 : public Task {

   public:
   //return a double if the organism manages to find the absolute value of the input numbers
     double CheckOutput(float output, float inputs[4], float reward) override {
         for (int i = 0; i < 4; i++) {
          float magnitude = fabs(inputs[i])*5;

          //Since these are floats, allowing for some floating point error
          if (fabs(output - magnitude) < 0.001) {
              std::cout << "Aboslute Value!" << std::endl;
              return reward;
          }
        }
         return 0;
     }
     public: 
     //returns the name of the task solved
      std::string name()  override{
        std::string n = "abs";
        return n;
      }

};


class Task_4 : public Task {

   public:
   //return a double if the organism manages to find the floor of of the input numbers multiplied by the square
     double CheckOutput(float output, float inputs[4], float reward) override {
         for (int i = 0; i < 4; i++) {
          float floor_i = floor(inputs[i])*(inputs[i])*(inputs[i]);
          if (fabs(output - floor_i) < 0.001) {
              std::cout << "Floor Function!" << std::endl;
              return reward;
          }
        }
         return 0;
     }

    public: 
    //returns the name of the task solved
     std::string name()  override{
        std::string n = "floor";
        return n;
     }

};

class Task_5 : public Task {

   public:
   //return a double if the organism manages to find the ceiling of the input numbers
     double CheckOutput(float output, float inputs[4], float reward) override {
         for (int i = 0; i < 4; i++) {
          float ceil_i = ceilf(inputs[i]);
          if (fabs(output - ceil_i) < 0.001) {
              std::cout << "Ceil Function!" << std::endl;
              return reward;
          }
        }
         return 0;
     }
   public: 
   //returns the name of the task solved
     std::string name()  override{
        std::string n = "ceil";
        return n;
     }

};
