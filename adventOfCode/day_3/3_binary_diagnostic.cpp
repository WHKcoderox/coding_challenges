#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<string> vs;

ifstream infile("input.txt");

int binStringToInt(string s) {
    int result = 0;
    for (int i = 0; i < s.length(); i++) {
        result <<= 1;
        if (s[i] == '1') result += 1;
    }
    return result;
}

int roundUpDiv(int x, int y) { //pre: x != 0 and y != 0
    return 1 + (x - 1) / y;
}

string getStringByBitCriterion(vs &binaries, vi &indices, bool common) {
    int i = 0, counts, j;
    char keepDigit;
    while (indices.size() > 1) {
        counts = 0;
        for (j = indices.size() - 1; j >= 0; --j) {
            if (binaries[indices[j]][i] == '1') {
                counts++;
            }
        }
        if (common) {
            keepDigit = (counts >= roundUpDiv(indices.size(), 2))? '1' : '0';
        } else {
            keepDigit = (counts < roundUpDiv(indices.size(), 2))? '1' : '0';
        }
        for (j = indices.size() - 1; j >= 0; --j) {
            if (binaries[indices[j]][i] != keepDigit) {
                indices.erase(indices.begin() + j);
            }
        }
        i++;
    }
    return binaries[indices[0]];
}

int generatorScrubbingRating() {
    string gen, scrub, s;
    vs binaries;
    vi indices1, indices2;
    int i, j;
    while(infile >> s) binaries.push_back(s);
    for (i = 0; i < binaries.size(); i++) {
        indices1.push_back(i);
        indices2.push_back(i);
    }
    gen = getStringByBitCriterion(binaries, indices1, true);
    scrub = getStringByBitCriterion(binaries, indices2, false);
    return binStringToInt(gen) * binStringToInt(scrub);
}

int gammaEpsilon() {
    int gamma = 0, epsilon = 0, i, rows = 0;
    vi counts;
    bool firstRun = true;
    string input;
    while(infile >> input) {
        for(i = 0; i < input.length(); i++) {
            if (firstRun) counts.push_back(0);
            if (input[i] == '1') counts[i] += 1;
        }
        rows++;
        firstRun = false;
    }
    for(i = 0; i < counts.size(); i++) {
        gamma <<= 1;
        epsilon <<= 1;
        if (counts[i] > rows / 2) {
            gamma += 1;
        } else {
            epsilon += 1;
        }
    }
    return gamma * epsilon;
}

int main() {
    cout << generatorScrubbingRating() << endl;
    // cout << gammaEpsilon() << endl;
    return 0;
}