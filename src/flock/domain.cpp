#include <iostream>

#include "domain.h"

// Default velocities chosen so that it takes at least ten time units to cross domain  
Domain::Domain() 
        : _sMin({0, 0}), _sMax({1, 1}), _vMin({-.1,-.1}), _vMax({.1, .1}) 
{};

Domain::Domain(std::vector<double> sMin, std::vector<double> sMax, 
               std::vector<double> vMin, std::vector<double> vMax)
        : _sMin(sMin), _sMax(sMax), _vMin(vMin), _vMax(vMax)
{};

// Set and get functions 
void Domain::setSpace(std::vector<double> sMin, std::vector<double> sMax)
{
    // Set if sensible
    if (sMin < sMax)
    {
        _sMin = sMin;
        _sMax = sMax;
    }
}

void Domain::setVelocity(std::vector<double> vMin, std::vector<double> vMax)
{
    // Set if sensible
    if (vMin < vMax)
    {
        _vMin = vMin;
        _vMax = vMax;
    }
}

std::pair<std::vector<double>, std::vector<double>>
Domain::getSpace()
{
    return std::make_pair(_sMin, _sMax);
}

std::pair<std::vector<double>, std::vector<double>>
Domain::getVelocity()
{
    return std::make_pair(_vMin, _vMax);
}