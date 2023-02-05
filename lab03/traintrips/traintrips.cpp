#include <iostream>
#include <stdio.h>
#include <limits.h>
using namespace std;

#define NMAX 1000
#define QMAX 100000
#define DMIN 10000

int N, Q, dmin, d[NMAX], dist[DMIN+1], seen[DMIN];

int closest() {
    int current = DMIN;
    for (int i = 0; i < dmin; i++)
      if (!seen[i] && dist[i] < dist[current]) current = i;
    return current;
}

void Dijkstra() {
  dist[0] = 0;
  dist[DMIN] = INT_MAX;
  for (int i = 1; i < dmin; i++) dist[i] = INT_MAX;

  for (int count = 0; count < dmin-1; count++) {
    int current = closest();
    seen[current] = true;
    for (int n = 0; n < N; n++) {
      int neighbour = (current + d[n])%dmin;
      dist[neighbour] = min(dist[neighbour], dist[current] + d[n]);
    }
  }
}

int main(int argc, char *argv[]) {
  scanf("%d %d", &N, &Q);

  dmin = 10001;
  for (int i = 0; i < N; i++) {
    scanf("%d", &d[i]);
    dmin = min(dmin, d[i]);
  }

  Dijkstra();

  for (int i = 0; i < Q; i++) {
    int q;
    scanf("%d", &q);
    if (dist[q%dmin] <= q) printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}
