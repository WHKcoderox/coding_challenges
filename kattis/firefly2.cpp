// https://open.kattis.com/problems/firefly
// done with augmented bst

#include <stdio.h>

using namespace std;

// obstacles tracks the number of intervals pos falls into, 
// given that all intervals start from 0
void insertObstacle(int pos, int *obstacles, int lb, int rb) {
  if (lb > rb) return;
  int m = (lb + rb) / 2;
  if (m <= pos) {
    // add obstacle and check if inserting to any nodes to the right
    obstacles[m]++;

    if (m < pos && m < rb) {
      insertObstacle(pos, obstacles, m + 1, rb);
    }
  } else {
    // check if inserting to any nodes in the left
    insertObstacle(pos, obstacles, lb, m - 1);
  }
}

int queryObstacle(int pos, int *obstacles, int lb, int rb) {
  int mid = (lb + rb) / 2;
  if (pos == mid) {
    return obstacles[mid];
  } else if (pos > mid) {
    return queryObstacle(pos, obstacles, mid + 1, rb);
  } else {
    // pos < mid, check left nodes for additional obstacles
    return obstacles[mid] + queryObstacle(pos, obstacles, lb, mid - 1);
  }
}

int main() {
  int N, H;

  scanf("%d %d", &N, &H);

  int o, topObs[H] = {0}, botObs[H] = {0};
  bool top = false;
  for (int i = 0; i < N; i++) {
    scanf("%d", &o);
    if (top) {
      insertObstacle(--o, topObs, 0, H-1);
    } else {
      insertObstacle(--o, botObs, 0, H-1);
    }
    top = !top;
  }

  int smallest = -1, count = 1, curr;

  for (int i = 0; i < H; i++) {
    curr = queryObstacle(i, botObs, 0, H-1) + queryObstacle(H - i - 1, topObs, 0, H-1);
    if (smallest >= 0) {
      if (curr == smallest) count++;
      else if (curr < smallest) {
        count = 1;
        smallest = curr;
      }
    } else {
      smallest = curr;
    }
  }

  printf("%d %d\n", smallest, count);
}