/* AGENTS 
    An abstract class for the creation of agents. 
*/

#ifndef AGENTS_H
#define AGENTS_H

#include <string>

class Agents
{
private:
    int _id;
    string _agent_type;
    
public:
    // Constructor and destructor
    Agents(int id, string agent_type) : _id(id), _agent_type(agent_type) {};
    ~Agents();

    // run: interaction between agent and other agents.
    // pure virtual method, must be overwritten by derived classes for specific agents. 
    virtual void run() = 0;
};


#endif