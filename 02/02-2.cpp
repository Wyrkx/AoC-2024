#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

// Returns false even if removing 1st or 2nd element makes it safe
bool isSafe(vector<int>& report, bool damp, vector<int>::iterator begin)
{
    int prev = *(begin++), curr, order = 0;

    for (vector<int>::iterator i = begin; i != report.end(); i++) {
        int curr = *i;
        int diff = curr - prev;

        if (diff == 0) {
            if (!damp) {
                damp = true;
                continue;
            } else {
                order = 0;
                break;
            }
        }

        if (order == 0) {
            order = diff;
        } else if (diff*order < 0) {
            if (!damp) {
                damp = true;
                continue;
            } else {
                order = 0;
                break;
            }
        }

        if (abs(diff) > 3) {
            if (!damp) {
                damp = true;
                continue;
            } else {
                order = 0;
                break;
            }
        }
        prev = curr;
    }
    return order != 0;
}

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
        vector<int> report;
        int level;
        while (iss >> level) {
            report.push_back(level);
        }
        
        if (!isSafe(report, false, report.begin())) {
            // without 1st element
            if (!isSafe(report, true, report.begin()+1)) {
                // without 2nd element
                vector<int> report2(report);
                report2.erase(report2.begin()+1);
                if (!isSafe(report2, true, report2.begin())) {
                    continue;
                }
            }
        }
        sum++;
    }
    inputFile.close();

    cout << sum << endl;
}