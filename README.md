# ABMkit

A toolkit for Agent Based Modeling. 

ABMkit currently provides:
- A flocking class `flock` that implements a version of cohesion, alignment, separation flocking inspired by Reynolds (http://www.red3d.com/cwr/boids/). 
This class is designed to work in arbitrary dimension, so that one can model flocking behavior in 2D, 3D, or abstract higher dimensions. 
- A demo application of this flocking class in 2D.  

Future plans:
- More sophisticated flocking behavior.
- OpenMP parallelization.
- HDF5 data managment.
- An implementation of lipids and related tools for modeling their formation of and movement within membranes.

## Code Structure

>
    ABMkit
    |
    |_src
    |    |_core
    |    |   |_agents.h
    |    |   |_model.h
    |    |
    |    |_flock
    |        |_boids.h
    |        |_boids.cpp
    |        |_flock.h
    |        |_flock.cpp
    |        |_domain.h
    |        |_domain.cpp
    |
    |_demo
        |_src
            |_main.cpp        


ABMkit consists of core abstract classes `agent` and `model` that provide basic functionality. The class `model` contains several pure virtual functions `setInitialData()`, `evolveAgents()`, and `runModel()` that are to be overwritten by derived classes. 

The class `boids` is derived from `agent` and the class `flock` is derived from `model`. The class `domain` is a helper class that stores information about the bounds in space and velocity.


## Building the code

Dependencies: None

Must compile with C++ version >= 14. 

The code is built with the help of CMake. To generate an executable that will run the demo (demo/src/main.cpp) do the following. 

Assuming you have cloned the master branch, from ABMkit/ run the commands

>   
    $ mkdir build && cd build
    $ cmake ..
    $ make

You can then run the demo executable by typing 
> 
    $ ./demo/flock

### Output
The program should print information about the "boids" (flocking agents) id, position, and velocity to cout. For example, 

> 
    Boid ID, position, velocity
      0 0.010920 0.267749 0.000111 0.053389 
      1 0.595867 0.226458 -0.042186 0.029451 
      2 0.708110 0.733700 0.006618 -0.056557 
      3 0.376599 0.621043 -0.023055 0.024368 
      4 0.019870 0.973123 -0.071032 0.050193 
      5 0.234122 0.023935 -0.020012 0.031699 
    Time step n = 0
      Updating boid 0
      0 0.011751 0.349409 0.000831 0.081661 
      Updating boid 1
      1 0.557803 0.271761 -0.038064 0.045303 
      Updating boid 2
      2 0.718345 0.694164 0.010234 -0.039536 
      Updating boid 3
      3 0.359121 0.669405 -0.017477 0.048362 
      Updating boid 4
      4 -0.051162 1.023315 -0.071032 0.050193 
      Updating boid 5
      5 0.214729 0.083909 -0.019393 0.059974 

## Udacity Cpp Nano degree
This project serves as a final project for the Udacity C++ Nano degree course, for which I chose to follow **Capstone Option 1**. 

### Elements of the rubric addressed. 

Referring to (https://review.udacity.com/#!/rubrics/2533/view), this project addresses the following points (numbered within each category): 

README:
1. A README with instructions is included
2. The README indicates that **Capstone Option 1** is chosen. 
3. The README indicates which points of the rubric are addressed. 

Compiling and Testing:
1. The submission compiles and runs following the instructions given above. 

Loops, Functions, I/O:
1. The project demonstrates an understanding of C++ control structures. See control structures in `flock.cpp` lines 19, 53, 72, 137, and 297. The file `flock.cpp` also demonstrates how the code divides tasks into many different functions. 

Object Oriented Programming:
1. The project is organized into classes: cf. `model.h`, `flock.h`, `agent.h`, `boids.h`, and `domain.h`, 
2. Class data members have appropriate access specifiers, see for example lines 15-42 in `boid.h`. 
3. Initialization lists are used, but not by all class members. See line 7 of `flock.cpp`, versus lines 8-18 of `boids.cpp`.
4. Most class member functions should be pretty clear. Of course, I antipate that improvements can be made. 
6. The classes `agent` -> `boid` and `model` -> `flock` use natural inheritance hierarchy. Override functions are specified. See for example `flock.h` lines 17 and 67-69.
7. The function Flock::boidInfo is overloaded, see `flock.h` lines 55-56.
8. Derived class functions override base class virtual functions. See `flock.h` lines 67-69.
9. I used templates as well, for example `generateRandomArray` and `printVector` starting on line 72 of `flock.h`. 

Memory Management:
1. At least two functions make use of pass-by-reference, for example Flock::printVector (line 53) and Flock::updatePosition (line 59) in `flock.h`.
6. A unique_ptr and a shared_ptr are used for data members within the Flock class. See lines 28 and 31 of `flock.h`.

Concurrency:
The project does not currently make use of concurrency. The goal is to parallelize for shared memory architectures using the OpenMP library. 




