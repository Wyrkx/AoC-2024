#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <stdint.h>

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

    long sum = 0;
    for (int i = 0; i < list1.size(); i++) {
        sum += abs(list1[i] - list2[i]);
    }

    cout << sum << endl;
}
