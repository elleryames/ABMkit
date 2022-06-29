
#include <iostream>
#include <algorithm>
#include <math.h>
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
        _boids->emplace_back(Boid(pos, vel));
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
              << Flock::printVector(boid.Position())
              << Flock::printVector(boid.Velocity())
              << std::endl;
}

void Flock::boidInfo(bool print_header)
{
    if (print_header)
    {
        std::cout << "Boid ID, "
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

/* Helper Functions for evolveAgent */
// --------------------------------
// Returns the scalar product of two vectors v1 and v2
double scalarProduct(std::vector<double> v1, 
                     std::vector<double> v2)
{
    try
    {
        if (v1.size() == v2.size())
        {
            double sum = 0.0;
            for (int i = 0; i< v1.size(); i++)
            {
                sum += v1[i] * v2[i];
            }
            return sum;
        }
        else
        {
            throw 1;
        }
    }
    catch(const int& e)
    {
        std::cerr << "Vectors not the same size" << '\n';
    }
    return 0;
}

// Returns norm of a vector v
double vectorNorm(std::vector<double>& v)
{
    double v2 = scalarProduct(v, v);
    return sqrt(v2);
}

// Returns angle in radians between vectors v1 and v2
double computeAngleBetweenTwoVectors(std::vector<double> v1, 
                                     std::vector<double> v2)
{
    double sp = scalarProduct(v1, v2);
    double v1_norm = vectorNorm(v1);
    double v2_norm = vectorNorm(v2);
    return acos(sp/(v1_norm * v2_norm));
}                            
// --------------------------
/* End Helper functions */

std::vector<double> Flock::computeLocalMeanPosition(Boid& boid)
{
    // get current boids position
    std::vector<double> bp = boid.Position();
    // initialize local mean position and number of nearby boids.
    std::vector<double> locMean(bp.size(), 0);
    int numNearbyBoids = 0;
    // loop thru boids, update local mean position if nearby
    for (auto oboid : *_boids)
    {
        // overwrite bp to bp-oboid.Position()
        std::vector<double> obPosition = oboid.Position();
        std::transform(bp.begin(), bp.end(), obPosition.begin(), bp.begin(), std::minus<>{});
        if (vectorNorm(bp) < boid.perceptionRadius())
        {
            // locMean += oboid.Position();
            std::transform(locMean.begin(), locMean.end(), obPosition.begin(), locMean.begin(), std::plus<>{});
            numNearbyBoids++;
        }
    }
    return locMean;
}

std::vector<double> Flock::computeMeanHeading()
{
    //
    return {0,0};
}

void Flock::updatePosition(Boid& boid)
{
    std::vector<double> mean_position = Flock::computeLocalMeanPosition(boid);
    std::vector<double> newPosition (mean_position.size(), 0);
    std::vector<double> bPosition = boid.Position();
    double bs = boid.Sensitivity();
    std::transform(bPosition.begin(), bPosition.end(), mean_position.begin(), newPosition.begin(), 
    [bs](double bp, double mp){ return bp + bs * mp; });
    boid.Position(newPosition);
}

void Flock::maintainSeparation(Boid& boid)
{
    // 
}

void Flock::evolveAgent(Agent& aboid)
{
    // recast agent as boid
    Boid& boid = dynamic_cast<Boid&>(aboid);

    // update position 
    Flock::updatePosition(boid);

    // maintain separation
    // Flock::maintainSeparation(boid);

    // update velocity 
    // Flock::updateVelocity(boid);
    // std::vector<double> mean_heading  = Flock::computeMeanHeading();
    // /* rotate velocity vector by small angle in direction 
    // of local mean heading */
    // // compute angle
    // double theta = computeAngleBetweenTwoVectors(boid.Velocity(), mean_heading)


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
            std::cout << "  Updating boid " << boid.getID() << std::endl;
            Flock::evolveAgent(boid);
            Flock::boidInfo(boid);
        }
        n++;
    }
    
}