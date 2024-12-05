#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream inputFile ("input");
    if (!inputFile) {
        cerr << "Missing input";
        exit(1);
    }

    long sum = 0;
    string line;
    string mul_instruct = "mul(x,x)";
    while (getline(inputFile, line)) {
        int x = 0, prod = 1;
        string::iterator it = line.begin(), i = mul_instruct.begin();
        while (it != line.end()) {
            cout << "sum: " << sum << "| c: " << *it << "| i: " << i - mul_instruct.begin() << "| x: " << x << "| prod: " << prod << endl;
            if (*i == 'x') {
                if (isdigit(*it)) {
                    x = 10 * x + (*it - '0');
                    it++;
                    continue;
                } else if (x != 0) {
                    prod *= x;
                    x = 0;
                    i++;
                    continue;
                }
            } else if (*it == *i) {
                i++; it++;
                if (i == mul_instruct.end()) {
                    sum += prod;
                    i = mul_instruct.begin(), x = 0, prod = 1;
                }
                continue;
            } else if (i != mul_instruct.begin()) {
                i = mul_instruct.begin(), x = 0, prod = 1;
                continue;
            }
            i = mul_instruct.begin(), x = 0, prod = 1;
            it++;
        }
    }
    inputFile.close();

    cout << sum << endl;
}