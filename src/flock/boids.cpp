
#include "boids.h"

int Boid::_numBoids = 0;

Boid::Boid(std::vector<double> pos, 
           std::vector<double> vel)
{ 
    _id = _numBoids++;
    _position = pos;
    _velocity = vel;
    _size = boidSize;
    _sensitivity = boidSensitivity;
    _perceptionRadius = boidPerceptionRadius;
    _bubbleRadius = boidBubbleRadius;
}

// Get functions
double Boid::Size()
{
    return _size;
}

double Boid::Sensitivity()
{
    return _sensitivity;
}

double Boid::perceptionRadius()
{
    return _perceptionRadius;
}

double Boid::bubbleRadius()
{
    return _bubbleRadius;
}

int Boid::NumBoids()
{
    return _numBoids;
}

std::vector<double> Boid::Position()
{
    return _position;
}

std::vector<double> Boid::Velocity()
{
    return _velocity;
}

// Set functions
void Boid::BoidCommonParameters(double bSize, double bSensitivity, double bPerceptionRad, double bBubbleRad);
{
    
}

void Boid::Position(std::vector<double>& p)
{
    // FIXME: Check if within domain? (here or in flock)
    _position = p;
}

void Boid::Velocity(std::vector<double>& v)
{
    // FIXME: Verify within bounds
    _velocity = v;
}