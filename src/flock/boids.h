/* BOIDS
    An agent class
*/ 

#ifndef BOIDS_H
#define BOIDS_H

#include <vector>

#include "agents.h"


class Boid : public Agent
{
private:
    static int _numBoids;
    static double _size;
    static double _sensitivity;
    static double _perceptionRadius;
    static double _bubbleRadius;
    // double _perceptionLength; // Radius of sphere percieved by boid
    std::vector<double> _position;
    std::vector<double> _velocity;

public:
    Boid(std::vector<double> position, 
         std::vector<double> velocity);

    // get functions
    double Size();
    int NumBoids();
    double Sensitivity();
    double perceptionRadius();
    double bubbleRadius();
    std::vector<double> Position();
    std::vector<double> Velocity();

    // set functions
    void Position(std::vector<double>& p);
    void Velocity(std::vector<double>& v);
    void setBoidProperties(double bSize, double bSensitivity, double bPerceptionRad, double bBubbleRad);
};

#endif