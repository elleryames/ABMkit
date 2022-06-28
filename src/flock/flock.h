/* FLOCK
    A model class describing a flock of boids.
*/

#ifndef FLOCK_H
#define FLOCK_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "boids.h"
#include "model.h"
#include "domain.h"

class Flock : public Model
{
// Agents can access members of Model
friend class Boid;

private:
    // Basic parameters of flock
    int _flockSize = 2;
    double _boidSize = 0.1;

    // a domain may be shared among multiple flocks.
    std::shared_ptr< Domain > _phaseSpace;

    // container for members of flock (boids), stored in heap.
    std::unique_ptr< std::vector<Boid> > _boids;

    // Flock evolution
    int _maxRunSteps;

public:
    template <typename T>
    const std::vector<T> generateRandomArray(const std::vector<T> valMin, 
                                             const std::vector<T> valMax);

    // Constructors 
    // FIXME: provide constructors with differing arguments.
    Flock(int baseDim, int flockSize, double boidSize, int maxRunSteps);

    // Set bounds in position and velocity space
    void setPhaseSpace( std::vector<double> sMin, 
                        std::vector<double> sMax, 
                        std::vector<double> vMin, 
                        std::vector<double> vMax);

    // print info
    template <typename T>
    const std::string printVector(const std::vector<T>& vec);
    // print info for one boid and all boids w/wo header
    void boidInfo(Boid& boid);
    void boidInfo(bool print_header = false);

    // Methods for evolution of agents (boids)
    std::vector<double> computeMeanPosition();
    std::vector<double> computeMeanHeading();

    // inherited methods
    void setInitialData() override;
    void evolveAgent(Agent& boid) override;
    void runModel() override;
};

// Template function definitions 
template <class T>
const std::vector<T> Flock::generateRandomArray(const std::vector<T> valMin, 
                                                const std::vector<T> valMax)
{
    std::vector<T> out_arr;
    for (int i = 0; i < Flock::_baseDimension; i++)
    {
        out_arr.push_back(Flock::getRandom(valMin[i], valMax[i]));
    }
    return out_arr;
}

// Simply print components of vector separated by a space
template <typename T>
const std::string Flock::printVector(const std::vector<T>& vec)
{
    std::string strout = "";
    for (int i=0; i < vec.size(); i++)
    {
        strout += std::to_string(vec[i]);
        strout += " ";
    }
    return strout;
}

#endif