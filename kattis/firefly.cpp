// https://open.kattis.com/problems/firefly

#include <bits/stdc++.h>

using namespace std;

struct node {
  int left;
  int right;
  int obstacles;
  node *lchild;
  node *rchild;
} root;

void insertObstacle(int left, int right, node *n) {
  // printf("inserting %d %d into %d %d\n", left, right, n->left, n->right);
  if (n->left == left && n->right == right) {
    n->obstacles++;
  } else {
    int mid = (n->left + n->right) / 2;
    if (left <= mid) {
      insertObstacle(left, min(mid, right), n->lchild);
    }
    if (right > mid) {
      insertObstacle(max(mid + 1, left), right, n->rchild);
    }
  }
}

int numObstacles(int pos) {
  node curr = root;
  int sum = root.obstacles, mid;
  while(curr.left != curr.right) {
    mid = (curr.left + curr.right) / 2;

    if (pos <= mid) {
      sum += curr.lchild->obstacles;
      curr = *curr.lchild;
    } else {
      sum += curr.rchild->obstacles;
      curr = *curr.rchild;
    }
  }
  return sum;
}

void buildTree(node *n) {
  n->obstacles = 0;

  if (n->left < n->right) {
    // not a leaf node
    int mid = (n->left + n->right) / 2;

    n->lchild = (node *) malloc(sizeof (node));
    n->lchild->left = n->left;
    n->lchild->right = mid;
    buildTree(n->lchild);

    n->rchild = (node *) malloc(sizeof (node));
    n->rchild->left = mid + 1;
    n->rchild->right = n->right;
    buildTree(n->rchild);
  } else {
    // leaf node
    n->lchild = NULL;
    n->rchild = NULL;
  }
}

int main() {
  int N, H;
  scanf("%d %d\n", &N, &H);
  root.left = 0;
  root.right = H - 1;
  buildTree(&root);

  int o;
  bool top = false;
  for (int i = 0; i < N; i++) {
    scanf("%d", &o);
    if (top) {
      insertObstacle(H - o, H - 1, &root);
    } else {
      insertObstacle(0, --o, &root);
    }

    top = !top;
  }

  int smallest = -1, count, curr;
  for (int i = 0; i < H; i++) {
    curr = numObstacles(i);
    if (smallest >= 0) {
      if (curr == smallest) count++;
      else if (curr < smallest) {
        count = 1;
        smallest = curr;
      }
    }
    else {
      count = 1;
      smallest = curr;
    }
  }

  printf("%d %d\n", smallest, count);
}