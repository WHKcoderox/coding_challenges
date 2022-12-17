#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <unordered_set>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

ifstream infile("input.txt");

int countOverlap1(vvi &coordinates) {
    int graph[1000][1000] = { 0 }, x1, x2, y1, y2;
    unordered_set<int> overlaps;
    for (int i = 0; i < coordinates.size(); i++){
        x1 = coordinates[i][0];
        x2 = coordinates[i][2];
        y1 = coordinates[i][1];
        y2 = coordinates[i][3];
        
        if (x1 == x2 || y1 == y2) {
            // only consider hori/vert lines
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            for (int j = x1; j <= x2; j++) {
                for (int k = y1; k <= y2; k++) {
                    graph[k][j]++;
                    if (graph[k][j] > 1) {
                        overlaps.insert(k * 1000 + j);
                    }
                }
            }
        }
    }
    return overlaps.size();
}

int countOverlap2(vvi &coordinates) {
    int graph[1000][1000] = { 0 }, x1, x2, y1, y2;
    unordered_set<int> overlaps;
    for (int i = 0; i < coordinates.size(); i++){
        x1 = coordinates[i][0];
        x2 = coordinates[i][2];
        y1 = coordinates[i][1];
        y2 = coordinates[i][3];
        
        int t1, t2;
        bool lastOne = false;
        t1 = (x1 > x2)? -1 : 1;
        t2 = (y1 > y2)? -1 : 1;
        // printf("(%d, %d), (%d, %d)\n", x1, y1, x2, y2);
        while (x1 != x2 || y1 != y2 || !lastOne) {
            graph[y1][x1]++;
            if (x1 == x2 && y1 == y2) lastOne = true;
            // cout << y1 << " " << x1 << endl;
            if (graph[y1][x1] > 1) {
                overlaps.insert(y1 * 1000 + x1);
            }
            if (x1 != x2) x1 += t1;
            if (y1 != y2) y1 += t2;
        }
    }
    return overlaps.size();
}

int main() {
    string line; char* cLine;
    int x1, x2, y1, y2;
    vvi coordinates;
    while (getline(infile, line)) {
        cLine = &line[0];
        sscanf(cLine, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
        vi lineCoord = {x1, y1, x2, y2};
        coordinates.push_back(lineCoord);
    }
    cout << countOverlap2(coordinates) << endl;
    return 0;
}