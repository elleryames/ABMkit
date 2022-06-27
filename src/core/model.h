/* MODEL
    An abstract class for managing the simulation model 
*/ 

#ifndef MODEL_H
#define MODEL_H

#include <random>

#include "agents.h"

class Model
{
protected:
    int _baseDimension{2}; // base dimension of model

public:
    // Random number within specified range
    // FIXME: Make template.
    template <typename T>
    T getRandom(T min, T max);

    void setBaseDimension(int bD) 
    { 
        _baseDimension = bD; 
    }

    // Set initial configuration and state of agents
    virtual void setInitialData() = 0;

    // Evolve agents
    // FIXME
    //virtual void evolveAgent(Agent agent) = 0;

    // Run simulation
    virtual void runModel() = 0;
};

template <typename T>
T Model::getRandom(T min, T max)
{
    std::random_device rdVec;
    std::mt19937_64 eng(rdVec());
    std::uniform_real_distribution<T> distr(min, max);
    return distr(eng);
}

#endif