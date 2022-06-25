
#include "boids.h"

int Boid::_numBoids = 0;

Boid::Boid(std::vector<double> pos, 
           std::vector<double> vel, 
           double boidSize)
{ 
    _id = _numBoids++;
    _position = pos;
    _velocity = vel;
    _size = boidSize;
}

double Boid::getSize()
{
    return _size;
}

std::vector<double> Boid::getPosition()
{
    return _position;
}

std::vector<double> Boid::getVelocity()
{
    return _velocity;
}

int Boid::getNumBoids()
{
    return _numBoids;
}