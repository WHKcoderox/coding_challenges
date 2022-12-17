#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<long> vl;

ifstream infile("input.txt");

long differences(vl &posArr, long pos) {
  long result = 0;
  for (int i = 0; i < posArr.size(); i++) {
    result += abs(posArr[i] - pos);
  }
  return result;
}

long apDifferences(vl &posArr, long pos) {
  long result = 0, t;
  for (int i = 0; i < posArr.size(); i++) {
    t = abs(posArr[i] - pos);
    result += t * (t + 1) / 2;
  }
  return result;
}

long alignPos(vl &posArr, long l, long r, long(* diffFn)(vl &, long)) {
  // binary search the optimal alignment
  long m = posArr[(l + r) / 2];
  // long m = diffFn(posArr, 0) / posArr.size();
  long midDiff;
  while (l < r) {
    midDiff = diffFn(posArr, m);
    if (midDiff > diffFn(posArr, m - 1)) { 
      r = m;
      m = (l + r) / 2;
    }
    else if (midDiff > diffFn(posArr, m + 1)) { 
      l = m;
      m = (l + r) / 2;
    }
    else break;
  }
  return m;
}

int main() {
  string line;
  long pi, maxPos = 0;
  vl posArr;
  while(getline(infile, line, ',')) {
    istringstream iss (line);
    iss >> pi;
    posArr.push_back(pi);
    maxPos = max(maxPos, pi);
  }
  sort(posArr.begin(), posArr.end());
  cout << apDifferences(posArr, alignPos(posArr, 0, maxPos, apDifferences)) << endl;
}