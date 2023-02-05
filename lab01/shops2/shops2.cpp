#include <iostream>
using namespace std;

#define MAXN 20000
#define MAXK 1000000
int A[MAXN+1], best[MAXK+1];

int main(int argc, char *argv[]) {
  int N, K, ans = 20001, current;

  scanf("%d %d", &N, &K);
  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
    if (A[i] == K) {
      printf("%d\n", 1);
      return 0;
    }
  }

  for (int i = 0; i <= K; i++) best[i] = 200001;

  for (int i = 0; i < N; i++) {
    current = 0;
    for (int j = i; j >= 0; j--) {
      current += A[j];
      if (current > K) break;
      best[current] = min(i-j+1, best[current]);
    }
    current = 0;
    for (int j = i+1; j < N; j++) {
      current += A[j];
      if (current > K) break;
      if (best[K - current] > 0) ans = min(ans, best[K - current] + j - i);
    }
  }
  printf("%d\n", (ans == 20001? -1:ans));
  return 0;
}
