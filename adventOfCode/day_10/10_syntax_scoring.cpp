#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <stack>
#include <algorithm>

#define NUM_BRACKETS 4

using namespace std;

typedef vector<int> vi;
typedef vector<string> vs;
typedef stack<char> sc;

ifstream infile ("input.txt");

pair<char, int> scoreTable[] = {
  make_pair(')', 3),
  make_pair(']', 57),
  make_pair('}', 1197),
  make_pair('>', 25137)
};

pair<char, char> bracketPairs[] = {
  make_pair('(', ')'),
  make_pair('[', ']'),
  make_pair('{', '}'),
  make_pair('<', '>')
};

int getScore(char c, pair<char, int>* table, int si) {
  pair<char, int> ci;
  for (int i = 0; i < si; i++) {
    ci = table[i];
    if (c == ci.first) return ci.second;
  }
  return -1;
}

bool matchBrackets(char c1, char c2) {
  for (auto cc : bracketPairs) {
    if (cc.first == c1) {
      if (cc.second == c2) return true;
      return false;
    }
  }
  return false;
}

int isCorrupted(string line) {
  // assume corrupted lines only due to current line
  int result;
  sc chunkStack;
  for (auto c : line) {
    result = getScore(c, scoreTable, NUM_BRACKETS);
    if (result > 0) {
      if (chunkStack.empty() || !matchBrackets(chunkStack.top(), c)) {
        // illegal
        return result;
      } else {
        chunkStack.pop();
      }
    } else {
      // opening bracket
      chunkStack.push(c);
    }
  }
  return -1;
}

vs filterCode(vs &code) {
  vs result;
  for (auto line : code) {
    if (isCorrupted(line) < 0) result.push_back(line);
  }
  return result;
}

pair<char, int> scoreTable2[] = {
  make_pair(')', 1),
  make_pair(']', 2),
  make_pair('}', 3),
  make_pair('>', 4)
};

// pre: there exists a matching
char getMatching(char c) {
  for (auto cc : bracketPairs) {
    if (c == cc.first) return cc.second;
    if (c == cc.second) return cc.first;
  }
}

long part2(vs &code) {
  vs filtered = filterCode(code);
  long score;
  int temp;
  char c;
  vector<long> scores;
  for (auto line : filtered) {
    score = 0;
    sc chunkStack;
    // either closes the current open bracket, or is an open bracket.
    for (auto c : line) {
      if (!chunkStack.empty() && getMatching(c) == chunkStack.top()) 
        chunkStack.pop();
      else chunkStack.push(c);
    }
    while(!chunkStack.empty()) {
      c = chunkStack.top();
      chunkStack.pop();
      score *= 5;
      score += getScore(getMatching(c), scoreTable2, NUM_BRACKETS);
    }
    scores.push_back(score);
  }
  sort(scores.begin(), scores.end());
  return scores[scores.size() / 2];
}

long part1(vs &code) {
  long result = 0;
  long score;
  for (auto line : code) {
    score = isCorrupted(line);
    if (score > 0) result += score;
  }
  return result;
}

int main() {
  string line;
  vs code;
  while(getline(infile, line)) {
    code.push_back(line);
  }
  cout << "Total syntax error score is: " << part1(code) << endl;
  cout << "Final autocomplete score is: " << part2(code) << endl;
}