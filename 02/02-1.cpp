#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

int main()
{
    ifstream inputFile ("input.txt");
    if (!inputFile) {
        cerr << "Missing input";
        exit(1);
    }

    int sum = 0;
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        int prev, curr, order = 0;
        iss >> prev;
        while (iss >> curr) {
            int diff = curr - prev;

            if (diff == 0) {
                order = 0;
                break;
            }
            if (order == 0) {
                order = diff;
            } else if (diff*order < 0) {
                order = 0;
                break;
            }

            if (abs(diff) > 3) {
                order = 0;
                break;
            }
            prev = curr;
        }
        if (order != 0) sum++;
    }
    inputFile.close();

    cout << sum << endl;
}