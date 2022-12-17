#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

typedef vector<int> vi;
typedef long long int ll;


ifstream infile("input.txt");

int countIncrement() {
    bool notFirst = false;
    int a, prev, result = 0;
    while (infile >> a) {
        if (notFirst && a > prev) result++;
        prev = a; notFirst = true;
    }
    cout << result << endl;
    return result;
}

int countSumIncrement() {
    vi window;
    int a, result = 0;
    while (infile >> a) {
        if (window.size() == 3) {
            if (window.back() < a) result++;
            window.pop_back();
        }
        window.insert(window.begin(), a);
    }
    cout << result << endl;
    return result;
}

int main() {
    countSumIncrement();
    return 0;
}