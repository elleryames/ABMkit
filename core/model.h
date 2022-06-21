/* MODEL
    An abstract class for managing the simulation model 
*/ 

#ifndef MODEL_H
#define MODEL_H

class Model
{
private:
    int numBaseDimensions; // spatial or otherwise base dim

public:
    Model();
    ~Model();

    // Set initial configuration and state of agents
    virtual void setInitialData() = 0;

    // Run simulation
    virtual void runModel() = 0;
};

#endif