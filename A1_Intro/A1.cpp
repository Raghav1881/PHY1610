// Created a program to calculate the time taken for a ball 
// to fall from a height h  and the height of a ball after n
// bounces.
//
// Raghav Sharma, University of Toronto 2023

#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>
using namespace std;

// Function to calculate the time taken for a ball to fall from a height h
float bouncy_time(float h)
{
    float t = sqrt(2 * h / 9.81);
    return t;
}

// Function to calculate the height of a ball after n bounces
void bouncy_height(float h_avg, int n, ofstream& outfile)
{
    int i;
    std::unique_ptr<float[]> h(new float[n]);
    std::unique_ptr<float[]> t(new float[n]);
    
    // Initialize for loop to calculate ball heights and corresponding
    // times for each bounce
    for (i = 0; i < n; i++)
    {
        h[i] = h_avg * i / (2 * n);
        t[i] = bouncy_time(h[i]);
    }
    
    for (i = 0; i < n; i++)
    {
        outfile << "Bouncy Height: " << h[i] << "m, Bouncy Time: " << t[i] << "s" << endl;
    }
}

int main() 
{
    // Prompt user for input
    int n_in;
    float h_in;
    cout << "Give me number of balls and average height: ";
    cin >> n_in >> h_in;

    // Specify the relative path for the file
    string filename = "bouncy_output.txt";
    ofstream outfile(filename);

    // Create file if it does not exist
    if (!outfile)
    {
        cerr << "Error: Unable to open the file " << filename << " in the current directory." << endl;
        return 1;
    }

    bouncy_height(h_in, n_in, outfile);

    outfile.close();

    cout << "Output written to " << filename << endl;

    return 0;
}
