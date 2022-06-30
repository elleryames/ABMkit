
#include "boids.h"

// Initialize number of boid agents
int Boid::_numBoids = 0;

// set static member variable defaults
double Boid::_size = 0.1;
double Boid::_sensitivity = 0.1;
double Boid::_perceptionRadius = 0.5;
double Boid::_bubbleRadius = 0.2;

Boid::Boid(std::vector<double> pos, 
           std::vector<double> vel)
{ 
    _id = _numBoids++;
    _position = pos;
    _velocity = vel;
}

void Boid::setBoidProperties(double boidSize, double boidSensitivity, double boidPerceptionRadius, double boidBubbleRadius)
{
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
void Boid::Position(const std::vector<double>& p)
{
    // FIXME: Check if within domain? (here or in flock)
    Boid::_position = p;
}

void Boid::Velocity(const std::vector<double>& v)
{
    // FIXME: Verify within bounds
    Boid::_velocity = v;
}