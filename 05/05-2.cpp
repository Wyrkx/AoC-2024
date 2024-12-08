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
int correctUpdate(vector<int>& update, map<int, vector<int>>& rules) {
    map<int, vector<int>::iterator> printed;
    bool ordered = true;
    for (auto it = update.begin(); it != update.end(); it++) {
        int n = *it;
        auto end_it = it;
        if (auto rules_find = rules.find(n); rules_find != rules.end()) {
            for (int x : rules_find->second) {
                if (auto printed_find = printed.find(x); printed_find != printed.end()) {
                    ordered = false;
                    *printed_find->second = n;
                    end_it = printed_find->second;
                    *it = x;
                    printed[x] = it;
                    break;
                }
            }
        }
        printed[n] = end_it;
    }
    return ordered ? update[update.size()/2] : 0;
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
        if (correctUpdate(update, rules) == 0) {
            while (correctUpdate(update, rules) == 0);
            sum += correctUpdate(update, rules);
        }
    }

    inputFile.close();

    cout << sum << endl;
}