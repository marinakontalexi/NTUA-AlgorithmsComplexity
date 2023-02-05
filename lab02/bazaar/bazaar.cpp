#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <map>
using namespace std;

#define NMAX 5000
#define MMAX 1500
int N, M, arr[9][2][MMAX+1], len[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}, val[9][MMAX+1][NMAX+1], item[3][NMAX+1];

void precalc(int idx) {
  for (int i = 1; i <= N; i++) val[idx][0][i] = INT_MAX;
  for (int i = 0; i <= len[idx]; i++) val[idx][i][0] = 0;
}

void calc(int idx) {
  for (int j = 1; j <= len[idx]; j++)
    for (int i = 1; i <= N; i++) {
      int temp = val[idx][j-1][max(0, i - arr[idx][0][j-1])];
      if (temp == INT_MAX) val[idx][j][i] = val[idx][j-1][i];
      else val[idx][j][i] = min(temp + arr[idx][1][j-1], val[idx][j-1][i]);
    }
}

int main(int argc, char *argv[]) {
  char random, opt1, opt2;
  int q, p, index, ans = INT_MAX;

  /*FILE *f;
  if ((f = fopen(argv[1], "rt")) == nullptr)
    return 1;*/

  scanf("%d %d", &N, &M);

  for (int i = 0; i < M; i++) {
    scanf("%c %c %c", &random, &opt1, &opt2);
    scanf("%d %d", &q, &p);
    index = (opt1 - '1')*3 + (opt2 - 'A');
    arr[index][0][len[index]] = q;
    arr[index][1][len[index]++] = p;
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int idx = i*3 + j;
      precalc(idx);
      calc(idx);
    }
    for (int j = 0; j <= N; j++)
      if (val[3*i][len[3*i]][j] >= INT_MAX - 1 || val[3*i+1][len[3*i+1]][j] >= INT_MAX - 1 || val[3*i+2][len[3*i+2]][j] >= INT_MAX - 1)
        item[i][j] = INT_MAX;
      else item[i][j] = val[3*i][len[3*i]][j] + val[3*i+1][len[3*i+1]][j] + val[3*i+2][len[3*i+2]][j];
  }

  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= N-i; j++) {
      if (item[0][i] == INT_MAX || item[1][j] == INT_MAX || item[2][N-i-j] == INT_MAX) continue;
      else ans = min(ans, item[0][i] + item[1][j] + item[2][N-i-j]);
    }
  }

  printf("%d\n", ans==INT_MAX? -1:ans);
}
