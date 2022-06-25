/* FLOCK
    A model class describing a flock of boids.
*/

#ifndef FLOCK_H
#define FLOCK_H

#include <vector>
#include <string>
#include <iostream>

#include "boids.h"
#include "model.h"

class Flock : public Model
{
// Agents can access members of Model
friend class Boid;

private:
    int _flockSize = 2;
    double _boidSize = 0.1;
    // Diagonal corners of rectangle in velocity space.
    std::vector<double> _minVel = {-1,-1}; 
    std::vector<double> _maxVel = {1,1};
    // Diagonally opposed points of rectangular domain. 
    std::vector<double> _domainMin = {0,0};
    std::vector<double> _domainMax = {1,1}; 
    std::vector<Boid> _boids;

public:
    template <typename T>
    std::vector<T> generateRandomArray(std::vector<T> valMin, std::vector<T> valMax);

    Flock(int baseDim, int flockSize, double boidSize);
    void evolveAgent(Boid boid);

    // Set bounds in position and velocity space
    void setDomain(std::vector<double> dMin, std::vector<double> dMax);
    void setVelocityBounds(std::vector<double> vMin, std::vector<double> vMax);

    // print info
    template <typename T>
    std::string printVector(std::vector<T> vec);
    void boidInfo();

    // inherited methods
    void setInitialData();
    void runModel();
};

// Template function definitions 
template <class T>
std::vector<T> Flock::generateRandomArray(std::vector<T> valMin, std::vector<T> valMax)
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
std::string Flock::printVector(std::vector<T> vec)
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