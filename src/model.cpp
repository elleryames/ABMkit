    
    
#include "model.h"
#include <random>

double Model::getRandomDouble(double min, double max)
{
    std::random_device rdVec;
    std::mt19937_64 eng(rdVec());
    std::uniform_real_distribution<double> distr(min, max);
    return distr(eng);
}