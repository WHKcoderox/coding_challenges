#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

typedef vector<int> vi;

ifstream infile("input.txt");

// simulating lanternfish population
int main() {
  string line;
  int di, numDays = 256, birthtime = 7, newbirthtime = birthtime + 2;
  long daysToBirth[newbirthtime] = { 0 };
  while (getline(infile, line, ',')) {
      istringstream days (line);
      days >> di;
      daysToBirth[di]++;
  }
  long n, birthed = 0;
  for (int d = 0; d < numDays; d++) {
    for (int i = 0; i < newbirthtime; i++) {
      n = daysToBirth[i];
      daysToBirth[i] = 0;
      if (i == 0) {
        birthed = n;
      } else {
        daysToBirth[i - 1] += n;
      }
    }
    daysToBirth[birthtime - 1] += birthed;
    daysToBirth[newbirthtime - 1] = birthed;
  }
  long result = 0;
  for (int i = 0; i < newbirthtime; i++) {
    result += daysToBirth[i];
  }
  cout << result << endl;
}