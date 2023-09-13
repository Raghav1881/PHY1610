#include <iostream>
#include <vector>

const bool alive = true;
const bool dead = false;

// Function to initialize the cell board with a target alive fraction
std::vector<bool> initializeBoard(int numCells, double targetAliveFraction) {
    std::vector<bool> cell(numCells, dead);
    int numAlive = static_cast<int>(numCells * targetAliveFraction);

    for (int i = 0; i < numAlive; i++) {
        cell[i] = alive;
    }

    return cell;
}

// Function to count the number of alive neighbors for a cell
int countAliveNeighbors(const std::vector<bool>& cell, int cellIndex) {
    int numAlive = 0;
    int numCells = cell.size();

    for (int offset : {-1, 1}) {
        int neighborIndex = (cellIndex + offset + numCells) % numCells;
        if (cell[neighborIndex] == alive) {
            numAlive++;
        }
    }

    return numAlive;
}

// Function to update the cell board based on Game of Life rules
std::vector<bool> updateCells(const std::vector<bool>& cell) {
    int numCells = cell.size();
    std::vector<bool> newCell(numCells);

    for (int i = 0; i < numCells; i++) {
        int aliveNeighbors = countAliveNeighbors(cell, i);

        if (cell[i] == alive && (aliveNeighbors == 2 || aliveNeighbors == 4)) {
            newCell[i] = alive;
        } else if (cell[i] == dead && (aliveNeighbors == 2 || aliveNeighbors == 3)) {
            newCell[i] = alive;
        }
    }

    return newCell;
}

// Function to output the cell board state along with a step number
void output(const std::vector<bool>& cell, int step) {
    int numCells = cell.size();
    double aliveFraction = 0.0;

    for (int i = 0; i < numCells; i++) {
        if (cell[i] == alive) {
            aliveFraction += 1;
            std::cout << 'I';
        } else {
            std::cout << '-';
        }
    }

    aliveFraction /= numCells;
    std::cout << " " << aliveFraction << "\n";
}

int main() {
    int numCells, numSteps;
    double targetAliveFraction;

    // Set simulation parameters by user input
    std::cout << "Provide number of cells, number of steps, and target alive fraction: ";
    std::cin >> numCells >> numSteps >> targetAliveFraction;

    std::vector<bool> cell = initializeBoard(numCells, targetAliveFraction);

    // Output initial state
    output(cell, 0);

    // Evolution loop
    for (int t = 1; t <= numSteps; t++) {
        cell = updateCells(cell);
        output(cell, t);
    }

    return 0;
}