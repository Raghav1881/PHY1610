#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "parameters.h"
#include "inputvalidation.h"
#include "fileoperations.h"

int main(int argc, char* argv[])
{
    // Check command line argument
    if (argc != 2) {
        std::cerr << "Error: wave1d needs one parameter file argument.\n";
        return 1;
    }
    if (not std::filesystem::exists(argv[1])) {
        std::cerr << "Error: parameter file '" << argv[1] << "' not found.\n";
        return 2;
    }

    // Read the values from the parameter file specified on the command line
    Parameters param;
    std::ifstream infile(argv[1]);
    infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        infile >> param.c;
        infile >> param.tau;
        infile >> param.x1;
        infile >> param.x2;
        infile >> param.runtime;
        infile >> param.dx;
        infile >> param.outtime;
        infile >> param.outfilename;
        infile.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "Error while reading file '" << argv[1] << "'.\n";
        return 3;
    }

    // Check input validity
    if (!validateInput(param)) {
        std::cerr << "Parameter value error in file '" << argv[1] << "'\n";
        return 4;
    }

    // Derived parameters
    param.ngrid = static_cast<size_t>((param.x2 - param.x1) / param.dx);
    param.dt = 0.5 * param.dx / param.c;
    param.nsteps = static_cast<size_t>(param.runtime / param.dt);
    param.nper = static_cast<size_t>(param.outtime / param.dt);

    // Open output file
    std::ofstream fout(param.outfilename);

    // Output parameters to file
    outputParametersToFile(param, fout);

    // Define and allocate arrays
    auto rho_prev = std::make_unique<double[]>(param.ngrid);
    auto rho = std::make_unique<double[]>(param.ngrid);
    auto rho_next = std::make_unique<double[]>(param.ngrid);
    auto x = std::make_unique<double[]>(param.ngrid);

    // Initialize array of x values
    for (size_t i = 0; i < param.ngrid; i++) {
        x[i] = param.x1 + (static_cast<double>(i) * (param.x2 - param.x1)) / static_cast<double>(param.ngrid - 1);
    }

    // Initialize wave with a triangle shape
    initializeWave(x.get(), rho.get(), rho_prev.get(), param);

    // Output initial wave to file
    fout << "\n#t = " << 0.0 << "\n";
    for (size_t i = 0; i < param.ngrid; i++) {
        fout << x[i] << " " << rho[i] << "\n";
    }

    // Take timesteps
    takeTimeSteps(param, rho.get(), rho_prev.get(), rho_next.get(), x.get(), fout);

    // Close file
    fout.close();
    std::cout << "Results written to '" << param.outfilename << "'.\n";
}
