
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
            for (int i = 0; i < v1.size(); i++)
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
double vectorNorm(const std::vector<double>& v)
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

bool isNearby(std::vector<double>& pos, Boid& boid)
{
    // get boids position
    std::vector<double> obPosition = boid.Position();

    // compute displacement from given position pos
    std::transform(pos.begin(), pos.end(), 
    obPosition.begin(), pos.begin(), std::minus<>{});

    // test if within perception radius 
    // Note: perceptionRadius is static. 
    return vectorNorm(pos) < boid.perceptionRadius();
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
        // if oboid is nearby
        if (isNearby(bp, oboid))
        {
            std::vector<double> obPosition = oboid.Position();
            std::transform(locMean.begin(), locMean.end(), obPosition.begin(), locMean.begin(), std::plus<>{});
            numNearbyBoids++;
        }
    }
    return locMean;
}

std::vector<double> Flock::computeLocalMeanHeading(Boid& boid)
{
    //
    // get current boids position
    std::vector<double> bp = boid.Position();
    // initialize local mean position and number of nearby boids.
    std::vector<double> locMean(bp.size(), 0);
    int numNearbyBoids = 0;
    // loop thru boids, update local mean position if nearby
    for (auto oboid : *_boids)
    {
        // Test if oboid is nearby to current boid
        if (isNearby(bp, oboid))
        {
            std::vector<double> obVelocity = oboid.Velocity();
            std::transform(locMean.begin(), locMean.end(), obVelocity.begin(), locMean.begin(), std::plus<>{});
            numNearbyBoids++;
        }
    }
    return locMean;
}

void Flock::flockCohesion(Boid& boid)
{ 
    // compute mean position of nearby boids
    std::vector<double> meanPosition = Flock::computeLocalMeanPosition(boid);

    // if any agents were in perceptionRadius of boid, 
    // then perform a cohesion update
    double mpNorm = vectorNorm(meanPosition);
    if (mpNorm > 0)
    {
        std::vector<double> cohesionVelocity (meanPosition.size(), 0);
        std::vector<double> bVelocity = boid.Velocity();

        double vMax = vectorNorm(Flock::_phaseSpace->_vMax); // max boid speed
        double bs = boid.Sensitivity(); // control how sensitive boid is

        // cohesionVel = bs * vMax * meanPosition
        // The boid cannot accelerate more than a fraction bs 
        // of the maximum boid speed.
        std::transform(meanPosition.begin(), meanPosition.end(),
            cohesionVelocity.begin(), 
            [bs, vMax, mpNorm](double mp){ return bs * vMax * mp / mpNorm; });

        // update velocity
        std::transform(bVelocity.begin(), bVelocity.end(), 
        cohesionVelocity.begin(), bVelocity.begin(), std::plus<>{});
        boid.Velocity(bVelocity);
    }
}

void Flock::flockAlignment(Boid& boid)
{
    std::vector<double> meanVelocity = Flock::computeLocalMeanHeading(boid);

    double mvNorm = vectorNorm(meanVelocity);
    if (mvNorm > 0)
    {
        std::vector<double> alignmentVelocity (meanVelocity.size(), 0);
        std::vector<double> bVelocity = boid.Velocity();

        double vMax = vectorNorm(Flock::_phaseSpace->_vMax); // max boid speed
        double bs = boid.Sensitivity(); // control how sensitive boid is

        // alignmentVel = bs * vMax * meanVelocity
        //      The boid cannot accelerate more than a fraction bs 
        //      of the maximum boid speed.
        std::transform(meanVelocity.begin(), meanVelocity.end(),
            alignmentVelocity.begin(), 
            [bs, vMax, mvNorm](double mv){ return bs * vMax * mv / mvNorm; });

        // update velocity
        std::transform(bVelocity.begin(), bVelocity.end(), 
        alignmentVelocity.begin(), bVelocity.begin(), std::plus<>{});
        boid.Velocity(bVelocity);
    }
}

void Flock::maintainSeparation(Boid& boid)
{
    // Based on pseudocode from Conrad Parker
    // https://vergenet.net/~conrad/boids/pseudocode.html

    std::vector<double> bPosition = boid.Position();
    std::vector<double> bVelocity = boid.Velocity();
    std::vector<double> displacements (bPosition.size(), 0);

    //
    for (auto oboid : *_boids)
    {
        // if oboid is nearby to current boid
        if( isNearby(bPosition, oboid) )
        {
            // compute displacement from given position pos
            //     displacement = bPosition - obPosition
            std::vector<double> obPosition = oboid.Position();
            std::transform(bPosition.begin(), bPosition.end(), 
            obPosition.begin(), bPosition.begin(), std::minus<>{});

            // subtract from displacements vector
            std::transform(displacements.begin(), displacements.end(), 
            bPosition.begin(), displacements.begin(), std::minus<>{});
        
        }
    }

    // update velocity
    std::transform(bVelocity.begin(), bVelocity.end(), 
    displacements.begin(), bVelocity.begin(), std::plus<>{});
    boid.Velocity(bVelocity);
}

void Flock::updatePosition(Boid& boid)
{
    std::vector<double> bPosition = boid.Position();
    std::vector<double> bVelocity = boid.Velocity();
    std::vector<double> newPosition (bPosition.size(), 0);
    // pnew = p + v dt, where dt = 1.
    std::transform(bPosition.begin(), bPosition.end(), bVelocity.begin(), newPosition.begin(), std::plus<>{});
    boid.Position(newPosition);
}


void Flock::evolveAgent(Agent& aboid)
{
    // recast agent as boid
    Boid& boid = dynamic_cast<Boid&>(aboid);

    //  update velocity
    // step 1. flock cohesion (move towards local center)
    Flock::flockCohesion(boid);
    // step 2: velocity aligns with other boids
    Flock::flockAlignment(boid);
    // step 3: maintain separation (steer to avoid other boids)
    Flock::maintainSeparation(boid);

    // update position 
    Flock::updatePosition(boid);
}

void Flock::runModel()
{
    // Evolve boids in some fashion until termination criteria is reached.
    int n = 0;

    while (n < _maxRunSteps)
    {
        std::cout << "n = " << n << std::endl;
        for (Boid& boid : *_boids)
        {
            std::cout << "  Updating boid " << boid.getID() << std::endl;
            Flock::evolveAgent(boid);
            Flock::boidInfo(boid);
        }
        n++;

    }
    
}