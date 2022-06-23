/* MODEL
    An abstract class for managing the simulation model 
*/ 

#ifndef MODEL_H
#define MODEL_H

class Model
{
protected:
    int _baseDimension{2}; // base dimension of model

public:
    // Random number within specified range
    // FIXME: Make template.
    double getRandomDouble(double min, double max);

    void setBaseDimension(int bD) 
    { 
        _baseDimension = bD; 
    }

    // Set initial configuration and state of agents
    virtual void setInitialData() = 0;

    // Run simulation
    virtual void runModel() = 0;
};

#endif