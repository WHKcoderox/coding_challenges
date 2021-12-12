#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <utility>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef unordered_set<string> uss;
typedef unordered_map<string, pair<vs, bool>> umsvsb;
typedef unordered_map<string, int> umsi;
typedef vector<pair<string, uss>> vpsuss;
typedef vector<pair<string, umsi>> vpsumsi;

ifstream infile("input.txt");

int countDFS2(umsvsb &caveMap) {
    int path_count = 0, currIndex = 0;
    vpsumsi toVisit = { make_pair<string, umsi>("start", {}) };
    umsi visited; bool cont;
    pair<string, umsi> curr;
    while (toVisit.size() > 0) {
        cont = false;
        curr = toVisit.back();
        toVisit.pop_back();
        if (curr.first.compare("end") == 0) {
            path_count++;
            // cout << "ended path #" << path_count << endl;
            continue;
        }
        if (caveMap[curr.first].second && curr.second.find(curr.first) != curr.second.end()) {
            if (curr.first.compare("start") == 0) continue;
            for (auto& it: curr.second) {
                if (it.first[0] >= 'a' && it.second == 2) {cont = true; break;}
            }
        }
        if (cont) continue;
        visited = curr.second;
        // cout << curr.first << ", " << visited.size() << " visited, going to:" << endl;
        if (visited.find(curr.first) != visited.end()) {
            visited[curr.first]++;
        } else visited[curr.first] = 1;
        for (auto s : caveMap[curr.first].first) {
            toVisit.push_back(make_pair(s, visited));
            // cout << s << " ";
        } // cout << endl;
    }
    return path_count;
}

int countDFS(umsvsb &caveMap) {
    int path_count = 0, currIndex;
    vpsuss toVisit = { make_pair<string, uss>("start", {}) };
    uss visited;
    pair<string, uss> curr;
    while (toVisit.size() > 0) {
        curr = toVisit.back();
        toVisit.pop_back();
        if (curr.first.compare("end") == 0) {
            path_count++;
            continue;
        }
        if (curr.second.find(curr.first) != curr.second.end() && caveMap[curr.first].second) continue;
        visited = curr.second;
        visited.insert(curr.first);
        for (auto s : caveMap[curr.first].first) {
            toVisit.push_back(make_pair(s, visited));
        }
    }
    return path_count;
}

int main() {
    string line, c1, c2;
    char* cLine, *cc1, *cc2;
    umsvsb caveMap;
    while (getline(infile, line)) {
        c1 = line.substr(0, line.find("-"));
        c2 = line.substr(line.find("-") + 1);
        // cout << (c1[0] >= 'a') << " " << (c2[0] >= 'a') << endl;
        if (caveMap.find(c1) == caveMap.end()) {
            caveMap[c1] = make_pair<vs, bool>({ c2 }, c1[0] >= 'a');
        } else {
            caveMap[c1].first.push_back(c2);
        }
        if (caveMap.find(c2) == caveMap.end()) {
            caveMap[c2] = make_pair<vs, bool>({ c1 }, c2[0] >= 'a');
        } else {
            caveMap[c2].first.push_back(c1);
        }
    }
    cout << countDFS2(caveMap) << endl;
    return 0;
}