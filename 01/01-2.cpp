#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <stdint.h>
#include <map>

using namespace std;

int main()
{
    ifstream inputFile ("input");
    if (!inputFile) {
        cerr << "Missing input";
        exit(1);
    }

    vector<int> list1, list2;
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        int num1, num2;
        iss >> num1 >> num2;
        list1.push_back(num1);
        list2.push_back(num2);
    }
    inputFile.close();

    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    assert(list1.size() == list2.size());

    map<int, int> map2;

    for (auto num : list2) {
        map2[num] += 1;
    }

    long sum = 0;
    for (auto num : list1) {
        sum += num * map2[num];
    }
    cout << sum << endl;
}
