#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

bool checkDir(vector<string>& lines, string& xmas, string::iterator xmas_it, int i, int j, array<int, 2> dir) {
    while (++xmas_it != xmas.end()) {
        i += dir[0]; j += dir[1];
        // cout << "i: " << i 
        //      << "| j: " << j
        //      << "| it: " << xmas_it - xmas.begin()
        //      << endl;
        if (i < 0 || j < 0 || i >= lines.size() || j >= lines[i].length()) {
            return false;
        }
        if (lines[i][j] != *xmas_it) {
            return false;
        }
    }
    return true;
}

int main()
{
    ifstream inputFile ("input");
    if (!inputFile) {
        cerr << "Missing input";
        exit(1);
    }
    string line, xmas = "XMAS";
    int sum = 0;
    vector<string> lines;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    string::iterator xmas_it = xmas.begin();
    for (int i = 0; i < lines.size(); i++) {
        line = lines[i];
        for (int j = 0; j < line.length(); j++) {
            if (line[j] == *xmas_it) {
                // cout << i << "|" << j << endl;
                sum += checkDir(lines, xmas, xmas_it, i, j, {0, 1})
                     + checkDir(lines, xmas, xmas_it, i, j, {0, -1})
                     + checkDir(lines, xmas, xmas_it, i, j, {1, 0})
                     + checkDir(lines, xmas, xmas_it, i, j, {-1, 0})
                     + checkDir(lines, xmas, xmas_it, i, j, {1, 1})
                     + checkDir(lines, xmas, xmas_it, i, j, {-1, 1})
                     + checkDir(lines, xmas, xmas_it, i, j, {1, -1})
                     + checkDir(lines, xmas, xmas_it, i, j, {-1, -1});
                // cout << sum << endl;
            }
        }
    }

    inputFile.close();

    cout << sum << endl;
}