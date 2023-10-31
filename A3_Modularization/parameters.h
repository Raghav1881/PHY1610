#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

class Parameters {
public:
    double  c;              // wave speed
    double  tau;            // damping time
    double  x1;             // leftmost x value
    double  x2;             // rightmost x value
    double  runtime;        // how long should the simulation try to compute?
    double  dx;             // spatial grid size
    double  outtime;        // how often should a snapshot of the wave be written out?
    std::string outfilename; // name of the file with the output data

    // the remainder are to be derived from the above ones:
    size_t  ngrid;          // number of x points
    double  dt;             // time step size
    size_t  nsteps;         // number of steps of that size to reach runtime
    size_t  nper;           // how many steps between snapshots
};

#endif // PARAMETERS_H
