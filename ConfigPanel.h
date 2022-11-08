#include "emp/config/ArgManager.hpp"
EMP_BUILD_CONFIG(MyConfigType,
VALUE(SEED, int, 7, "What value should the random seed be?"), 
VALUE(Population, int, 20, "The number of starting organism in the world"),
VALUE(Reward, float, 0.1, "Points given for solving each task"),
)