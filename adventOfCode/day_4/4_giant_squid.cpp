#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

ifstream infile("input.txt");

bool winningBoard(vvi &board) {
    bool cont1, cont2;
    for (int i = 0; i < board.size(); i++) {
        cont1 = cont2 = false;
        for (int j = 0; j < board[i].size(); j++) {
            cont1 |= (board[i][j] != -1);
            cont2 |= (board[j][i] != -1);
            if (cont1 && cont2) break;
        }
        if (!(cont1 && cont2)) return true;
    }
    return false;
}

int sumUnmarked(vvi &board) {
    int score = 0;
    for (int i = 0; i < 5; i++) 
        for (int j = 0; j < 5; j++)
            if (board[i][j] != -1) score += board[i][j];
    return score;
}

int boardScore(vi &numSeq, vvvi &boards) {
    int score = 0, i, j, k, l, curr;
    for (i = 0; i < numSeq.size(); i++) {
        curr = numSeq[i];
        for (j = 0; j < boards.size(); j++) {
            for (k = 0; k < 5; k++) {
                for (l = 0; l < 5; l++) {
                    if (boards[j][k][l] == curr) {
                        boards[j][k][l] = -1;
                        if (winningBoard(boards[j])) {
                            return sumUnmarked(boards[j]) * curr;
                        }
                    }
                }
            }
        }
    }
    return score;
}

int boardScore2(vi &numSeq, vvvi &boards) {
    int score = 0, i, j, k, l, m, curr, lastPlayed;
    unordered_set<int> wonBoards;
    vi lastWon;
    while (wonBoards.size() < boards.size()) {
        lastWon.clear();
        for (i = 0; i < numSeq.size(); i++) {
            curr = numSeq[i];
            for (j = 0; j < boards.size(); j++) {
                if (wonBoards.find(j) != wonBoards.end()) continue;
                for (k = 0; k < 5; k++) {
                    for (l = 0; l < 5; l++) {
                        if (boards[j][k][l] == curr) {
                            boards[j][k][l] = -1;
                            if (winningBoard(boards[j])) {
                                wonBoards.insert(j);
                                lastPlayed = curr;
                                lastWon.push_back(j);
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < lastWon.size(); i++) {
        cout << sumUnmarked(boards[lastWon[i]]) * lastPlayed << endl;
    }
    score = sumUnmarked(boards[lastWon[i-1]]) * lastPlayed;
    return score;
}

int main() {
    string line, token;
    size_t pos = 0;
    int i, j, n;
    bool firstLine = true;
    vi numberSeq;
    vvvi boards;
    while (getline(infile, line)) {
        if (line.length() != 0) {
            if (firstLine) {
                // first line contains number sequence
                istringstream numberStream(line);
                while (getline(numberStream, token, ',')) {
                    numberSeq.push_back(stoi(token));
                }
                firstLine = false;
            } else {
                istringstream row(line);
                for (i = 0; i < 5; i++){
                    row >> n;
                    boards.back()[j][i] += n;
                }
                j++;
            }
        } else {
            // create board
            j = 0;
            vvi board;
            boards.push_back(board);
            for (i = 0; i < 5; i++) {
                vi row = {0, 0, 0, 0, 0};
                boards.back().push_back(row);
            }
        }
    }

    cout << boardScore2(numberSeq, boards) << endl;
    return 0;
}