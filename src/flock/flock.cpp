
#include <iostream>
#include "flock.h"

Flock::Flock(int baseDim, int flockSize, double boidSize, int maxRunSteps) 
    : _flockSize(flockSize), _boidSize(boidSize), _maxRunSteps(maxRunSteps)
{
    Flock::setBaseDimension(baseDim);
    _boids  = std::make_unique< std::vector<Boid> >();
    _phaseSpace = std::make_shared< Domain >();
};

void Flock::setInitialData()
{
    for (int i = 0; i < _flockSize; i++)
    {
        std::vector<double> pos = Flock::generateRandomArray(_phaseSpace->_sMin, _phaseSpace->_sMax);
        std::vector<double> vel = Flock::generateRandomArray(_phaseSpace->_vMin, _phaseSpace->_vMax);
        _boids->emplace_back(Boid(pos, vel, _boidSize));
    }
}


void Flock::setPhaseSpace(  std::vector<double> sMin, 
                            std::vector<double> sMax, 
                            std::vector<double> vMin, std::vector<double> vMax)
{
    Flock::_phaseSpace->setSpace(sMin, sMax);
    Flock::_phaseSpace->setVelocity(vMin, vMax);
}

void Flock::boidInfo(Boid& boid)
{
    std::cout << boid.getID() << " "
              << boid.getSize() << " "
              << Flock::printVector(boid.getPosition())
              << Flock::printVector(boid.getVelocity())
              << std::endl;
}

void Flock::boidInfo(bool print_header)
{
    if (print_header)
    {
        std::cout << "Boid ID, "  << "size, "
                  << "position, " << "velocity"
                  << std::endl;
    }

    if (_boids && _boids->size() > 0 )
    {
        for (auto boid : *_boids)
        {
            Flock::boidInfo(boid);
        }
    }
    else 
    {
        std::cout << "Warning! List of boids is empty" << std::endl;
    }
}

std::vector<double> Flock::computeMeanPosition()
{
    //
    return {0,0};
}

std::vector<double> Flock::computeMeanHeading()
{
    //
    return {0,0};
}

void Flock::evolveAgent(Agent& boid)
{
    std::vector<double> mean_position = Flock::computeMeanPosition();
    std::vector<double> mean_heading  = Flock::computeMeanHeading();
}

void Flock::runModel()
{
    // Evolve boids in some fashion until termination criteria is reached.
    int n = 0;

    while (n < _maxRunSteps)
    {
        std::cout << "n = " << n << std::endl;
        for (auto boid : *_boids)
        {
            Flock::evolveAgent(boid);
            Flock::boidInfo(boid);
        }
        n++;
    }
    
}