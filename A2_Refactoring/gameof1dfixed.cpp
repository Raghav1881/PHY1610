// gameof1dfixed.cpp

#include <iostream>
#include <memory>

// Make three functions, one that first fills cell array,
// one that updates cells, and one that outputs

const bool alive = true;
const bool dead = false;

auto initialize_board(int num_cells, int num_steps, double target_alive_fraction)
{
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
    return cell;
}

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

    auto cell = initialize_board(num_cells, num_steps, target_alive_fraction); 
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