/* BOIDS
    An agent class
*/ 

#include <vector>

#include "agents.h"


class Boid : public Agent
{
private:
    static int _numBoids;
    double _size;
    std::vector<double> _position;
    std::vector<double> _velocity;

public:
    Boid(std::vector<double> position, 
         std::vector<double> velocity, 
         double size);

    double getSize();
    std::vector<double> getPosition();
    std::vector<double> getVelocity();
    int getNumBoids();
};
