#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <bitset>

using namespace std;

typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef unordered_set<int> usi;
typedef bitset<7> b7;

ifstream infile("input.txt");

// 7 line segments, represented as:
//  0000
// 1    2
// 1    2
// 1    2
// 1    2
//  3333
// 4    5
// 4    5
// 4    5
// 4    5
//  6666
#define ALL_SEGMENTS (1 << 7) - 1

b7 signalToBitset(string s) {
  b7 result;
  for (auto c : s) {
    result[c - 'a'].flip();
  }
  return result;
}

int segmentToPos(b7 seg) {
  int i = 0;
  while(!seg.test(i++)) {}
  return i - 1;
}

vi decoder(vs &uc) {
  // we know which digits are 1, 4, 7, 8.
  b7 code1 (ALL_SEGMENTS), code4 (ALL_SEGMENTS), code7 (ALL_SEGMENTS), 
  code8 (ALL_SEGMENTS), code235 (ALL_SEGMENTS), code069 (ALL_SEGMENTS);
  // 2 segments -> 1, 3 segs -> 7, 4 segs -> 4,...
  b7* codeptrArr[] = { &code1, &code7, &code4, &code235, &code069, &code8};
  for (auto c : uc) {
    *codeptrArr[c.size() - 2] &= signalToBitset(c);
  }
  // solve for s0 by taking 7 XOR 1
  b7 s0 = code7 ^ code1;
  // solve for s2 by taking (7 AND (0 AND 6 AND 9)) XOR 7
  b7 s2 = (code7 & code069) ^ code7;
  // solve for s5 by taking 1 XOR s2
  b7 s5 = code1 ^ s2;
  // solve for s3 by taking (2 AND 3 AND 5) AND 4
  b7 s3 = code235 & code4;
  // solve for s6 by taking (2 AND 3 AND 5) XOR (s0 OR s3)
  b7 s6 = code235 ^ (s0 | s3);
  // solve for s1 by taking 4 XOR (1 OR s3)
  b7 s1 = code4 ^ (code1 | s3);
  // solve for s4 by taking (4 XOR 8) XOR (s0 OR s6)
  b7 s4 = (code4 ^ code8) ^ (s0 | s6);
  vi result;
  vector<b7> segmentList ( {s0, s1, s2, s3, s4, s5, s6} );
  for (auto s : segmentList) {
    result.push_back(segmentToPos(s));
  }
  return result;
}

long part2 (vvs &ucs, vvs &fds) {
  vi decodedSegments;
  long result = 0;
  int currNum, currDigit;
  b7 currSignal;
  for (int i = 0; i < ucs.size(); i++) {
    decodedSegments = decoder(ucs[i]);
    currNum = 0;
    for (auto ds : fds[i]) {
      currSignal = signalToBitset(ds);
      switch(ds.size()) {
        case 2:
          currDigit = 1;
          break;
        case 3:
          currDigit = 7;
          break;
        case 4:
          currDigit = 4;
          break;
        case 5:
          if (currSignal.test(decodedSegments[4])) {
            currDigit = 2;
          } else if (currSignal.test(decodedSegments[1])) {
            currDigit = 5;
          } else {
            currDigit = 3;
          }
          break;
        case 6:
          if (currSignal.test(decodedSegments[3])) {
            if (currSignal.test(decodedSegments[4])) {
            currDigit = 6;
            } else {
              currDigit = 9;
            }
          } else {
            currDigit = 0;
          }
          break;
        case 7:
          currDigit = 8;
      }
      currNum *= 10;
      currNum += currDigit;
    }
    result += currNum;
  }
  return result;
}

usi numSegs1478 ( {2, 4, 3, 7} );
int count1478 (vs &fd) {
  int result = 0;
  for (int i = 0; i < fd.size(); i++) {
    if (numSegs1478.find(fd[i].size()) != numSegs1478.end()) {
      result++;
    }
  }
  return result;
}

long part1 (vvs &fds) {
  long result = 0;
  for (int i = 0; i < fds.size(); i++) {
    result += count1478(fds[i]);
  }
  return result;
}

int main() {
  string line; char* cLine;
  vvs uniqueCodes;
  vvs fourDigits;
  string s;
  int i, j = 0;
  while(getline(infile, line)) {
    istringstream iss (line);
    vs uc;
    vs fd;
    uniqueCodes.push_back(uc);
    fourDigits.push_back(fd);
    i = 0;
    while (iss >> s) {
      if (i < 10) {
        uniqueCodes[j].push_back(s);
      }  else if (i > 10) {
        fourDigits[j].push_back(s);
      }
      i++;
    }
    j++;
  }
  cout << "The number of 1, 4, 7 and 8 digits are: " << part1(fourDigits) << endl;
  cout << "The sum of decoded numbers are: " << part2(uniqueCodes, fourDigits) << endl;
}