#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <memory>
#include "Parameters.h"

void takeTimeSteps(const Parameters& param);
void outputParametersToFile(const Parameters& param);
std::unique_ptr<double[]> initializeArrays(const Parameters& param);
void initializeWave(double* x, double* rho, double* rho_prev, const Parameters& param);

#endif // FILEOPERATIONS_H
