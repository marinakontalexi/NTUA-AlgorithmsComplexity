#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

#define NMAX 3000
#define MMAX 100000
#define QMAX 100000
int N, M, Q, bottleneck[NMAX][NMAX+1], U[NMAX], size[NMAX];
bool seen[NMAX];
vector<int> edges[MMAX];
vector<pair<int,int>> mst[NMAX], TBV;

void addEdge(int a, int b, int d) {
  mst[a].push_back({b, d});
  mst[b].push_back({a, d});
}

bool mycomp(vector<int> a, vector<int> b) {
  return a[2] < b[2];
}

int find(int &x) {
  if (U[x] != x) U[x] = find(U[x]);
  return U[x];
}

void Union(int &x, int &y) {
  int px = find(x), py = find(y);
  if (px == py) return;
  if (size[px] < size[py]) {
    U[px] = py;
    size[py] += size[px];
  }
  else {
    U[py] = px;
    size[px] += size[py];
  }
}

void constructMST(){
  int counter = 0;
  sort(edges, edges + M, mycomp);
  // for (int i = 0; i < M; i++) {
  //   cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << endl;
  // }
  for (int i = 0; i < N; i++) U[i] = i + 1 - (size[i] = 1);
  for (int i = 0; i < M; i++) {
    int a = edges[i][0], b = edges[i][1], d = edges[i][2];
    if (find(a) != find(b)) {
      Union(a, b);
      addEdge(a, b, d);
      counter++;
    }
    if (counter == N - 1) break;
  }
  // vector<pair<int,int>>::iterator ptr;
  // cout << "MST:\n";
  // for (int i = 0; i < NMAX; i++) {
  //   for (ptr = mst[i].begin(); ptr < mst[i].end(); ptr++) {
  //     cout << "edge: " << i << " " << (*ptr).first << " " << (*ptr).second;
  //     cout << endl;
  //   }
  // }
}

void BFS(int start) {
  vector<pair<int,int>>::iterator ptr;
  for (int i = 0; i < N; i++) seen[i] = false;
  TBV.push_back({start, 0});
  while (!TBV.empty()) {
    pair<int, int> n = TBV.back();
    TBV.pop_back();
    int a = n.first, current = n.second;
    seen[a] = true;
    for (ptr = mst[a].begin(); ptr < mst[a].end(); ptr++){
      int b = (*ptr).first, d = (*ptr).second;
      //cout << "a: " << a << " b: " << b << " d: " << d;
      if (!seen[b]) {
        //cout << "upd\n";
        TBV.push_back({b, max(current, d)});
        bottleneck[start][b] = max(current, d);
      }
    }
  }
  bottleneck[start][NMAX] == 0;
}

int main() {
  scanf("%d %d", &N, &M);
  for (int i = 0; i < M; i++){
    int a, b, d;
    scanf("%d %d %d", &a, &b, &d);
    edges[i].push_back(a-1);
    edges[i].push_back(b-1);
    edges[i].push_back(d);
  }

  constructMST();

  for (int i = 0; i < N; i++) bottleneck[i][NMAX] = -1;
  scanf("%d", &Q);
  for (int i = 0; i < Q; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    if (bottleneck[a-1][NMAX] == -1) {
      BFS(a-1);
    }
    printf("%d\n", bottleneck[a-1][b-1]);
  }
}
