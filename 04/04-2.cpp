#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

bool checkA(vector<string>& lines, int i, int j) {
    char c1 = lines[i+1][j+1], c2 = lines[i-1][j-1], c3 = lines[i+1][j-1], c4 = lines[i-1][j+1];
    return ((c1 == 'M' && c2 == 'S') || (c1 == 'S' && c2 == 'M')) && ((c3 == 'M' && c4 == 'S') || (c3 == 'S' && c4 == 'M'));
}

int main()
{
    ifstream inputFile ("input");
    if (!inputFile) {
        cerr << "Missing input";
        exit(1);
    }
    string line;
    int sum = 0;
    vector<string> lines;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    for (int i = 1; i < lines.size() - 1; i++) {
        line = lines[i];
        for (int j = 1; j < line.length() - 1; j++) {
            if (line[j] == 'A') {
                sum += checkA(lines, i, j);
            }
        }
    }

    inputFile.close();

    cout << sum << endl;
}