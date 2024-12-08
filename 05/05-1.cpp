#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <array>
#include <set>

using namespace std;

vector<int> split(string& line, char splitter) {
    vector<int> vec;
    stringstream iss(line);
    string s;
    while (getline(iss, s, splitter)) {
        vec.push_back(stoi(s));
    }
    return vec;
}

// returns 0 if not correctly-ordered
int verifyUpdate(vector<int>& update, map<int, vector<int>>& rules) {
    set<int> printed;
    for (int n : update) {
        if (auto search = rules.find(n); search != rules.end()) {
            for (int x : search->second) {
                if (printed.count(x) != 0) {
                    return 0;
                }
            }
        }
        printed.insert(n);
    }
    return update[update.size()/2];
}

int main()
{
    ifstream inputFile ("input");
    if (!inputFile) {
        cerr << "Missing input";
        exit(1);
    }

    string line;
    map<int, vector<int>> rules = {};

    while (getline(inputFile, line)) {
        if (line.length() == 0) break;
        vector<int> vec = split(line, '|');
        if (auto search = rules.find(vec[0]); search != rules.end()) {
            search->second.push_back(vec[1]);
        } else {
            rules[vec[0]] = vector(1, vec[1]);
        }
    }

    int sum = 0;

    while (getline(inputFile, line)) {
        vector<int> update = split(line, ',');
        sum += verifyUpdate(update, rules);
    }

    inputFile.close();

    cout << sum << endl;
}