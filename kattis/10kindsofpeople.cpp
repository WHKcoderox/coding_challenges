// https://open.kattis.com/problems/10kindsofpeople

#include <stdio.h>

#include <iostream>


int r, c;

int getRoot(int r1, int c1, int *parent) {
  int temp1, temp2;

  while (parent[r1 * c + c1] != r1 * c + c1) {
    temp1 = parent[r1 * c + c1] / c;
    temp2 = parent[r1 * c + c1] % c;
    // flatten
    parent[r1 * c + c1] = parent[temp1 * c + temp2];
    r1 = temp1;
    c1 = temp2;
  }

  return r1 * c + c1;
}

bool sameParent(int r1, int c1, int r2, int c2, int *parent) {
  return getRoot(r1, c1, parent) == getRoot(r2, c2, parent);
}

void merge(int r1, int c1, int r2, int c2, int *parent) {
  parent[getRoot(r1, c1, parent)] = parent[getRoot(r2, c2, parent)];
}

int main() {
  scanf("%d %d", &r, &c);

  bool zone[r][c];
  int parent[r][c];

  char input[c + 1];
  for (int i = 0; i < r; i++) {
    scanf("%s", input);
    for (int j = 0; j < c; j++) {
      zone[i][j] = input[j] == '1';
      parent[i][j] = i * c + j;
      if (i > 0) {
        if (zone[i][j] == zone[i - 1][j]) {
          merge(i - 1, j, i, j, (int *)parent);
        }
      }
      if (j > 0) {
        if (zone[i][j] == zone[i][j - 1]) {
          merge(i, j - 1, i, j, (int *)parent);
        }
      }
    }
  }

  int n, r1, c1, r2, c2;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
    r1--;
    r2--;
    c1--;
    c2--;
    if (sameParent(r1, c1, r2, c2, (int *)parent)) {
      if (zone[r1][c1]) {
        printf("decimal\n");
      } else {
        printf("binary\n");
      }
    } else {
      printf("neither\n");
    }
  }
}