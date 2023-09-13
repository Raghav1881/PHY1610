#!/bin/bash

# Compile the C++ code
g++ -o gameoflife gameof1dfixed.cpp -std=c++14

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    
    # Run the compiled program
    ./gameoflife
    
    # Clean up the executable after running
    rm gameoflife
else
    echo "Compilation failed."
fi
