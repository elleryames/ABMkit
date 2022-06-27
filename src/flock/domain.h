/* DOMAIN_H
    A class that encapsulates information about the spatial and velocity bounds of flocking agents. 
*/

#include <vector>

class Domain
{
friend class Flock;

public:
    // Default constructor initializes 2D unit square domain. 
    Domain();
    Domain(std::vector<double> sMin, std::vector<double> sMax, 
           std::vector<double> vMin, std::vector<double> vMax);

    // Set and get functions 
    void setSpace(std::vector<double> sMin, std::vector<double> sMax);
    void setVelocity(std::vector<double> vMin, std::vector<double> vMax);
    std::pair<std::vector<double>, std::vector<double>>
    getSpace();
    std::pair<std::vector<double>, std::vector<double>>
    getVelocity();


private:
    // Diagonal corners of rectangle in velocity space.
    std::vector<double> _vMin; 
    std::vector<double> _vMax;
    // Diagonally opposed points of rectangular domain. 
    std::vector<double> _sMin;
    std::vector<double> _sMax; 
};