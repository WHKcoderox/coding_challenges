#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

ifstream infile("input.txt");

// pre: current tile is unvisited
int ffill(int x, int y, vvi &heightmap, vvb &visited, int y_bound, int x_bound) {
  int result = 1;
  visited[y][x] = true;
  if (y > 0 && heightmap[y-1][x] != 9 && !visited[y-1][x]) {
    result += ffill(x, y-1, heightmap, visited, y_bound, x_bound);
  }
  if (x > 0 && heightmap[y][x-1] != 9 && !visited[y][x-1]) {
    result += ffill(x-1, y, heightmap, visited, y_bound, x_bound);
  }
  if (y < y_bound && heightmap[y+1][x] != 9 && !visited[y+1][x]) {
    result += ffill(x, y+1, heightmap, visited, y_bound, x_bound);
  }
  if (x < x_bound && heightmap[y][x+1] != 9 && !visited[y][x+1]) {
    result += ffill(x+1, y, heightmap, visited, y_bound, x_bound);
  }
  return result;
}

long part2(vvi &heightmap) {
  // perform floodfills
  vvb visited;
  int y_bound = heightmap.size();
  int x_bound = heightmap[0].size();
  vi basinSizes;
  for (int i = 0; i < y_bound; i++) {
    visited.push_back(vb (x_bound, false));
  }
  for (int i = 0; i < y_bound; i++) {
    for (int j = 0; j < x_bound; j++) {
      if (!visited[i][j] && heightmap[i][j] != 9) {
        basinSizes.push_back(ffill(j, i, heightmap, visited, y_bound - 1, x_bound - 1));
      }
    }
  }
  sort(basinSizes.begin(), basinSizes.end(), greater<int>());
  // assume >3 basins
  return (long) basinSizes[0] * basinSizes[1] * basinSizes[2];
}

// assumes nonempty heightmap
long part1(vvi &heightmap) {
  long result = 0;
  int y_bound = heightmap.size();
  int x_bound = heightmap[0].size();
  int curr;
  for (int i = 0; i < y_bound; i++) {
    for (int j = 0; j < x_bound; j++) {
      curr = heightmap[i][j];
      if (
        (i > 0 && curr >= heightmap[i-1][j]) ||
        (j > 0 && curr >= heightmap[i][j-1]) ||
        (j < x_bound - 1 && curr >= heightmap[i][j+1]) ||
        (i < y_bound - 1 && curr >= heightmap[i+1][j])) {
        continue;
      }
      // low point, calculate risk level(=height + 1) and add to result
      result += curr + 1;
    }
  }
  return result;
}

int main() {
  string line;
  char c;
  vvi heightmap;
  while (getline(infile, line)) {
    vi heights;
    istringstream iss (line);
    while(iss >> c) {
      heights.push_back(c - '0');
    }
    heightmap.push_back(heights);
  }
  cout << "Sum of risk of low points = " << part1(heightmap) << endl;
  cout << "Product of largest 3 basins = " << part2(heightmap) << endl;
}