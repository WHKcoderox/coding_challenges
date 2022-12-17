#include <fstream>
#include <iostream>
#include <string>

using namespace std;

ifstream infile("input.txt");

int getDepthAndPosition2() {
    string s;
    int a, dist = 0, depth = 0, aim = 0;
    while (infile >> s >> a) {
        if (s.compare("forward") == 0) {
            dist += a;
            depth += aim * a;
        } else if (s.compare("up") == 0) {
            aim -= a;
        } else {
            aim += a;
        }
    }
    return dist * depth;
}

int getDepthAndPosition() {
    string s;
    int a, dist = 0, depth = 0;
    while (infile >> s >> a) {
        if (s.compare("forward") == 0) {
            dist += a;
        } else if (s.compare("up") == 0) {
            depth -= a;
        } else {
            depth += a;
        }
    }
    return dist * depth;
}

int main() {
    // cout << getDepthAndPosition() << endl;
    cout << getDepthAndPosition2() << endl;
    return 0;
}