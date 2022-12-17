#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <bitset>

#define NUM_OCTOPUS 10

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bitset<NUM_OCTOPUS>> vbs;

ifstream infile ("input.txt");

void resetVbs(vbs &vec) {
  for (int i = 0; i < vec.size(); i++) {
    vec[i].reset();
  }
}

// increments every energy level by 1 within rectangle bound. upper bound is exclusive.
void energise(vvi &eLevels, int x_min, int x_max, int y_min, int y_max) {
  for (int i = y_min; i < y_max; i++) {
    for (int j = x_min; j < x_max; j++) {
      eLevels[i][j]++;
    }
  }
}

// flashes and returns flash count
int flash(vvi &eLevels, vbs &hasFlashed) {
  int result = 0;
  for (int i = 0; i < NUM_OCTOPUS; i++) {
    for (int j = 0; j < NUM_OCTOPUS; j++) {
      if (eLevels[i][j] > 9 && !hasFlashed[i][j]) {
        hasFlashed[i].flip(j);
        energise(
          eLevels, 
          max(j-1,0), 
          min(j+2, NUM_OCTOPUS), 
          max(i-1,0), 
          min(i+2, NUM_OCTOPUS));
        result++;
      }
    }
  }
  return result;
}

void printElevels(vvi &eLevels) {
  for (auto v : eLevels) {
    for (auto i : v) {
      cout << i << " ";
    } cout << endl;
  }
  cout << "------------------------\n";
}

int simulateFlashes(vvi &eLevels, int steps, bool part2 = false) {
  int result = 0;
  int prev = 0;
  vbs hasFlashed(eLevels.size());
  int j, k;
  int numFlashes;
  int i = 0;
  while(part2 || i < steps) {
    resetVbs(hasFlashed);
    // increase energy levels by 1
    energise(eLevels, 0, NUM_OCTOPUS, 0, NUM_OCTOPUS);
    // keep flashing
    prev = result;
    do {
      numFlashes = flash(eLevels, hasFlashed);
      result += numFlashes;
    } while (numFlashes > 0);
    if (part2 && result - prev == NUM_OCTOPUS * NUM_OCTOPUS) {
      return i + 1;
    }
    // de-energise flashed octopii.
    for (int j = 0; j < NUM_OCTOPUS; j++) {
      for (int k = 0; k < NUM_OCTOPUS; k++) {
        if (hasFlashed[j][k]) eLevels[j][k] = 0;
      }
    }
    cout << "STEP " << i + 1 << ":\n";
    printElevels(eLevels);
    i++;
  }
  return result;
}

int main() {
  string line;
  vvi energyLevels;
  char c;
  while(getline(infile, line)) {
    vi energies;
    istringstream iss (line);
    while (iss >> c) energies.push_back(c - '0');
    energyLevels.push_back(energies);
  }
  cout << "Total number of flashes is: " << simulateFlashes(energyLevels, 100) << endl;
  cout << "Number of steps is: " << simulateFlashes(energyLevels, 0, true) + 100 << endl;
}