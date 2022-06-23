/* Flocking Simulator 
    A simulation of 2D flocking.
*/

#include "flock.h"
#include <random>
#include <iostream>

int main()
{
    // Parameters
    int spaceDim = 2;
    int flockSize = 6;
    double boidSize = 0.1;

    // Initialize and run simulation
    Flock myFlock(spaceDim, flockSize, boidSize);
    myFlock.setInitialData();
    myFlock.runModel();

    return 0;
}