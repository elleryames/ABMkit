
#include <iostream>
#include "flock.h"

Flock::Flock(int baseDim, int flockSize, double boidSize) : _flockSize(flockSize), _boidSize(boidSize) 
{
    Flock::setBaseDimension(baseDim);
};

void Flock::setDomain(std::vector<double> dMin, std::vector<double> dMax)
{
    // Set if sensible
    if (dMin < dMax)
    {
        _domainMin = dMin;
        _domainMax = dMax;
    }
}

void Flock::setVelocityBounds(std::vector<double> vMin, std::vector<double> vMax)
{
    // Set if sensible
    if (vMin < vMax)
    {
        _minVel = vMin;
        _maxVel = vMax;
    }
}

void Flock::setInitialData()
{
    for (int i = 0; i < _flockSize; i++)
    {
        std::vector<double> pos = generateRandomArray(_domainMin, _domainMax);
        std::vector<double> vel = generateRandomArray(_minVel, _maxVel);
        _boids.emplace_back(Boid(pos, vel, _boidSize));
    }
}

void Flock::boidInfo()
{
    std::cout << "Boid ID, " << "size, "
              << "position, " << "velocity"
              << std::endl;
    for (auto boid : _boids)
    {
        std::cout << boid.getID()
                  << boid.getSize()
                  << Flock::printVector(boid.getPosition())
                  << Flock::printVector(boid.getVelocity())
                  << std::endl;
    }
}

void Flock::evolveAgent(Boid boid)
{
    // update position and velocity of each boid.
}

void Flock::runModel()
{
    // Evolve boids in some fashion until termination criteria is reached.
}