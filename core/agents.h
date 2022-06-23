/* AGENTS 
    An abstract class for the creation of agents. 
*/

#ifndef AGENTS_H
#define AGENTS_H

#include <string>

class Agent
{
protected:
    int _id;
    
public:
    int getID() { return _id; }

    // run: interaction between agent and other agents.
    // pure virtual method, must be overwritten by derived classes for specific agents. 
    // virtual void run() = 0;
};


#endif