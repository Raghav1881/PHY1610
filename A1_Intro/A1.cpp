#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

float bouncy_time(float h)
{
    float t = sqrt(2 * h / 9.81);
    return t;
}

void bouncy_height(float h_avg, int n, ofstream& outfile)
{
    int i;
    float* h = new float[n];
    float* t = new float[n];
    
    for (i = 0; i < n; i++)
    {
        h[i] = h_avg * i / (2 * n);
        t[i] = bouncy_time(h[i]);
    }
    
    for (i = 0; i < n; i++)
    {
        outfile << "Bouncy Height: " << h[i] << "m, Bouncy Time: " << t[i] << "s" << endl;
    }
    
    delete[] h;
    delete[] t;
}

int main() 
{
    int n_in;
    float h_in;
    cout << "Give me number of balls and average height: ";
    cin >> n_in >> h_in;

    // Specify the relative path for the file
    string filename = "bouncy_output.txt";
    ofstream outfile(filename);

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
