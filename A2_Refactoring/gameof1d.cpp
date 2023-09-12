// gameof1d.cpp
//
// This code is part of assignment 2 of the 2023 Winter PHY1610 course.
//
// It computes the evolution of a one-dimensional variant of Conway's Game of
// Life, as conceived by Jonathan K. Millen and published in BYTE magazine in
// December, 1978.
//
// This system is a linear set of cells that are either "alive" or "dead".
//
// Time in this system progresses in discrete steps.
//
// The state of each cell at the next time step depends on its present
// state and that of its neighbors, in the following way:
//
//   - First, count the number of alive neighbors at most 2 cells away
//   - An alive cell stays alive if that count is 2 or 4, else it dies
//   - A dead cell becomes alive if that count is 2 or 3, else it stays dead.
//
// Since the first two and the last two cells would not have enough
// neighbours to apply this rule, we use cells on the other side as
// neighbours, i.e., we use 'periodic boundary conditions'.
//
// The initial state of this system is constructed with a given
// fraction of alive cells which are (nearly) equally spaced among
// dead cells. 
//
// The code computes the time evolution for 120 steps, and for each
// step, prints out a line with a representation of the state and
// fraction of alive cells.
//
// Ramses van Zon, 2023, University of Toronto

#include <iostream>
#include <memory>

// We use bool to store the state of each cell, but define the
// following to match the nomenclature of the system
const bool alive = true;
const bool dead = false;

// Determine next state of a single cell based on the state of all the cells
bool next_cell_state(const std::unique_ptr<bool[]>& cell_state,
                     int cell_index, int num_cells)
{
    // count neighbours around cell_index
    // the modulus operator (%) enforces periodic boundary conditions
    int alive_neighbours = 0;   
    for (int j = 1; j <= 2; j++) {
        if (cell_state[(cell_index+j+num_cells)%num_cells] == alive)
            alive_neighbours++;
        if (cell_state[(cell_index-j+num_cells)%num_cells] == alive)
            alive_neighbours++;
    }   
    // Use model rules for birth and survival.        
    if (cell_state[cell_index] == alive
        and
        (alive_neighbours==2 or alive_neighbours==4)) {
        return alive;
    } else if (cell_state[cell_index] == dead
               and
               (alive_neighbours==2 or alive_neighbours==3)) {
        return alive;
    } else {
        return dead;
    }
}

int main(int argc, char* argv[])
{
    // Set simulation parameters
    int num_cells = 70;
    int num_steps = 120;
    double target_alive_fraction = 0.35; 

    // Simulation creation
    auto cell = std::make_unique<bool[]>(num_cells);

    // Fill cells for the first time step such that the fraction of
    // alive cells is approximately target_alive_fraction.
    double fill = 0.0;
    for (int i = 0; i < num_cells; i++) {
        fill += target_alive_fraction;
        if (fill >= 1.0) {
            cell[i] = alive;
            fill -= 1.0;
        } else {
            cell[i] = dead;
        }
    }

    // Output 
    double alive_fraction = 0.0;
    for (int i = 0; i < num_cells; i++) {
        if (cell[i] == alive) {
            alive_fraction += 1;
        }
    }
    alive_fraction /= num_cells;
    std::cout << 0 << "\t";
    for (int i = 0; i < num_cells; i++) {
        std::cout << ((cell[i]==alive)?'I':'-');
    }
    std::cout << " " << alive_fraction;
    std::cout << "\n";
    
    // Evolution loop
    for (int t = 0; t < num_steps; t++) {
        
        // Update cells
        auto newcell = std::make_unique<bool[]>(num_cells);
        for (int i = 0; i < num_cells; i++) {
            newcell[i] = next_cell_state(cell,i,num_cells);
        }
        std::swap(cell, newcell);

        // Output
        alive_fraction = 0.0;
        for (int i = 0; i < num_cells; i++) {
            alive_fraction += cell[i];
        }
        alive_fraction /= num_cells;
        std::cout << t+1 << "\t"; 
        for (int i = 0; i < num_cells; i++) {
            std::cout << ((cell[i]==alive)?'I':'-');
        }           
        std::cout << " " << alive_fraction;
        std::cout << "\n";

    }
}
/*

Study the code, make sure you understand what's going on.

We are going to reorganize ('refactor') this code to be more modular.
We'll see in the next few lectures why this is a good idea, but
generally, the aim is to have separate functionalities be implemented
in separate functions.

As a first step in this modularization process.

  - Extract the part of the code that first fills the cell array, put
    it in a separate function that then gets called from the main
    function, so that the program still produce the same output (check
    that).

 - Also put the "Update cells" in a function.

 - And do the same the "Output" sections (this one should reduce the
   amount of code duplication).

 - Add functionality to the code so that num_cells, num_steps, and
   target_alive_fraction can be specified as command line arguments.

*/
