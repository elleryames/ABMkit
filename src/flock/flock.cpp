
#include <iostream>
#include "flock.h"

Flock::Flock(int baseDim, int flockSize, double boidSize) 
    : _flockSize(flockSize), _boidSize(boidSize) 
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

void Flock::boidInfo()
{
    std::cout << "Boid ID, " << "size, "
              << "position, " << "velocity"
              << std::endl;
    
    if (_boids && _boids->size() > 0 )
    {
        for (auto boid : *_boids)
        {
            std::cout << boid.getID() << " "
                    << boid.getSize() << " "
                    << Flock::printVector(boid.getPosition())
                    << Flock::printVector(boid.getVelocity())
                    << std::endl;
        }
    }
    else 
    {
        std::cout << "Warning! List of boids is empty" << std::endl;
    }
}

void Flock::evolveAgent(Agent& boid)
{
    // update position and velocity of each boid.
}

void Flock::runModel()
{
    // Evolve boids in some fashion until termination criteria is reached.
}