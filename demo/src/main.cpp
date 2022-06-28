/* Flocking Simulator 
    A simulation of 2D flocking.
*/

#include "flock/flock.h"
#include <random>
#include <iostream>

int main()
{
    // Parameters
    int spaceDim = 2;
    int flockSize = 6;
    double boidSize = 0.1;
    int maxRunSteps = 2;

    // Initialize and run simulation
    Flock myFlock(spaceDim, flockSize, boidSize, maxRunSteps);
    myFlock.setInitialData();
    myFlock.boidInfo(true);
    myFlock.runModel();

    return 0;
}