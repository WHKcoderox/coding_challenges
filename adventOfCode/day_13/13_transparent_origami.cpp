#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

ifstream infile ("input.txt");

bool comparePair(const ii &a, const ii &b) {
  if (a.first == b.first) return a.second < b.second;
  else return a.first < b.first;
}

int countDots (vii &coords) {
  vvb paper(2000, vb (2000, false));
  for (auto xy : coords) {
    paper[xy.second][xy.first] = true;
  }
  int result = 0;
  for (auto p : paper) {
    for (auto b : p) {
      if (b) result++; 
    }
  }
  return result;
}

void foldPaper(vii &coords, ii fold) {
  int x, y;
  int dir = fold.first;
  int f = fold.second;
  for (int i = 0; i < coords.size(); i++) {
    x = coords[i].first;
    y = coords[i].second;
    if (dir == 0 && y > f) {
      // upward fold
      coords[i] = make_pair(x, f - (y - f));
    } else if (dir == 1 && x > f) {
      // leftward fold
      coords[i] = make_pair(f - (x - f), y);
    }
  }
  sort(coords.begin(), coords.end(), comparePair);
  ii prev = make_pair(-1, -1);
  for (int i = coords.size() - 1; i >= 0; i--) {
    if (prev == coords[i]) {
      coords.erase(coords.begin() + i);
      continue;
    }
    prev = coords[i];
  }
}

int part1(vii &coords, ii fold) {
  foldPaper(coords, fold);
  return coords.size();
}

void printDots(vii &coords) {
  int x_bound = 0, y_bound = 0;
  for (auto xy : coords) {
    x_bound = max(x_bound, xy.first);
    y_bound = max(y_bound, xy.second);
  }
  // cout << "(xb, yb) = " << x_bound << ", " << y_bound << "\n";
  bool dots[++y_bound][++x_bound] = { false };
  for (auto xy : coords) {
    dots[xy.second][xy.first] = true;
  }
  for (int i = 0; i < y_bound; i++) {
    for (int j = 0; j < x_bound; j++) {
      if (dots[i][j]) cout << "X";
      else cout << " ";
      cout << " ";
    } cout << endl;
  }
  cout << "---------------\n"; 
}

void part2(vii &coords, vii &folds) {
  int i = 0;
  for (auto fold : folds) {
    foldPaper(coords, fold);
    printDots(coords);
    i++;
  }
}

int main() {
  string line;
  bool parseFolds = false;
  vii coords;
  vii folds;
  char c;
  int x, y, x_bound = 0, y_bound = 0;
  char* cLine;
  while(getline(infile, line)) {
    if (line.size() == 0) {
      parseFolds = true;
      continue;
    }
    cLine = &line[0];
    if (!parseFolds) {
      sscanf(cLine, "%d,%d", &x, &y);
      coords.push_back(make_pair(x, y));
      x_bound = max(x, x_bound);
      y_bound = max(y, y_bound);
    } else {
      sscanf(cLine, "fold along %c=%d", &c, &x);
      if (c == 'x') folds.push_back(make_pair(1, x));
      else folds.push_back(make_pair(0, x));
    }
  }
  // cout << "The number of dots visible after 1 fold is: " << part1(coords, folds[0]) << endl;
  part2(coords, folds);
}