#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool checkMul(string::iterator& it, string& mul_instruct, string::iterator& mul_it, int& x, int& prod, long& sum) {
    if (*mul_it == 'x') {
        if (isdigit(*it)) {
            x = 10 * x + (*it - '0');
            it++;
            return true;
        } else if (x != 0) {
            prod *= x;
            x = 0;
            mul_it++;
            return true;
        }
    } else if (*it == *mul_it) {
        mul_it++; it++;
        if (mul_it == mul_instruct.end()) {
            sum += prod;
            mul_it = mul_instruct.begin(), x = 0, prod = 1;
        }
        return true;
    } else if (mul_it != mul_instruct.begin()) {
        mul_it = mul_instruct.begin();
        x = 0, prod = 1;
        return true;
    }
    return false;
}

bool checkDo(string::iterator& it, string& do_instruct, string::iterator& do_it, bool& enabled) {
    if (*do_it == *it) {
        it++; do_it++;
        if (do_it == do_instruct.end()) {
            enabled = true;
            do_it = do_instruct.begin();
        }
        return true;
    } else if (do_it != do_instruct.begin()) {
        do_it = do_instruct.begin();
        return true;
    }
    return false;
}

bool checkDont(string::iterator& it, string& dont_instruct, string::iterator& dont_it, bool& enabled) {
    if (*dont_it == *it) {
        it++; dont_it++;
        if (dont_it == dont_instruct.end()) {
            enabled = false;
            dont_it = dont_instruct.begin();
        }
        return true;
    } else if (dont_it != dont_instruct.begin()) {
        dont_it = dont_instruct.begin();
        return true;
    }
    return false;
}

int main()
{
    ifstream inputFile ("input");
    if (!inputFile) {
        cerr << "Missing input";
        exit(1);
    }

    long sum = 0;
    string line;
    string mul_instruct = "mul(x,x)", do_instruct = "do()", dont_instruct = "don't()";
    bool enabled = true;
    while (getline(inputFile, line)) {
        int x = 0, prod = 1;
        string::iterator it = line.begin(), mul_it = mul_instruct.begin(), do_it = do_instruct.begin(), dont_it = dont_instruct.begin();
        while (it != line.end()) {
            cout << "sum: " << sum 
                 << "| enabled: " << enabled 
                 << "| c: " << *it 
                 << "| it: " << it - line.begin()
                 << "| mul_it: " << mul_it - mul_instruct.begin() 
                 << "| do_it: " << do_it - do_instruct.begin()
                 << "| dont_it: " << dont_it - dont_instruct.begin()
                 << "| x: " << x 
                 << "| prod: " << prod 
                 << endl;
            if (enabled) {
                if (checkMul(it, mul_instruct, mul_it, x, prod, sum)) continue;
                else if (checkDont(it, dont_instruct, dont_it, enabled)) continue;
            } else {
                if (checkDo(it, do_instruct, do_it, enabled)) continue;
            }
            it++;
        }
    }
    inputFile.close();

    cout << sum << endl;
}