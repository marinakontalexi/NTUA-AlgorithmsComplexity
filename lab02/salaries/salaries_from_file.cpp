#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;

#define BSIZE 1<<15

int N, K, p[200000], lis_arr[200000], lds_arr[200000];
vector<stack<int>> lis;
vector<int> lds;

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong() {
	long d = 0L, x = 0L;
	char c;

	while (1)  {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	}
	return -1;
}

int bisearch_lis(int start, int end, int x) {
  while(true) {
    int mid = (start + end)/2;
    if (end - start <= 1) return (x <= lis[start].top()? start:end);
    if (x <= lis[mid].top()) end = mid;
    else start = mid;
  }
}

int bisearch_lds(int start, int end, int x) {
  while(true) {
    int mid = (start + end)/2;
    if (end - start <= 1) return (x <= -1*lds[start]? start:end);
    if (x <= -1*lds[mid]) end = mid;
    else start = mid;
  }
}

void LIS() {
  int s = 1;
  stack<int> a;
  a.push(p[0]);
  lis.push_back(a);
  lis_arr[0] = 1;
  for (int i = 1; i < N; i++) {
    int m = bisearch_lis(0, s, p[i]);
    if (m < s) lis[m].push(p[i]);
    else {
      stack<int> a;
      a.push(p[i]);
      lis.push_back(a);
      s++;
    }
    lis_arr[i] = m;
  }
  return;
}

void LDS() {
  int s = 1;
  lds.push_back(p[N-1]);
  lds_arr[N-1] = 1;
  for (int i = N-2; i >= 0; i--) {
    int m = bisearch_lds(0, s, -1*p[i]);
    if (m < s) lds[m] = p[i];
    else {
      lds.push_back(p[i]);
      s++;
    }
    lds_arr[i] = m+1;
  }
  return;
}

int solve() {
  int ans = lds_arr[0], s = lis.size();
  for (int i = N-1; i > 0; i--) {
    lis[lis_arr[i]].pop();
    if (lis[lis_arr[i]].empty()) s--;
    //printf("%d current ans:%d\n lis_size: %d\n", i, ans, s);
    int m = bisearch_lis(0, s, p[i] + K);
		//printf("m is %d\n", m);
    ans = max(ans, m + lds_arr[i]);
  }
  return ans;
}

int main(int argc, char *argv[]) {
  FILE *f;
  if ((f = fopen(argv[1], "rt")) == nullptr)
    return 1;

  fscanf(f, "%d %d", &N, &K);
  for (int i = 0; i < N; i++) fscanf(f, "%d", &p[i]);

  LIS();
  LDS();
  /*for (int i = 0; i < lis.size(); i++) {
    while (!lis[i].empty()) {
      cout << lis[i].top() << " ";
      lis[i].pop();
    }
    cout << endl;
  }*/
  printf("%d\n", solve());
}
