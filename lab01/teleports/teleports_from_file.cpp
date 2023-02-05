#include <iostream>
using namespace std;

int E[1000001][3], U[1000001], size[1000001], Morty[1000001];
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[][3], int low, int high) {
    int pivot = arr[high][2];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j][2] < pivot) {
            i++;
            swap(&arr[i][0], &arr[j][0]);
            swap(&arr[i][1], &arr[j][1]);
            swap(&arr[i][2], &arr[j][2]);
        }
    }
    swap(&arr[i + 1][0], &arr[high][0]);
    swap(&arr[i + 1][1], &arr[high][1]);
    swap(&arr[i + 1][2], &arr[high][2]);
    return (i + 1);
}

void quickSort(int arr[][3], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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

int main(int argc, char *argv[]) {
  FILE *f;
  if ((f = fopen(argv[1], "rt")) == nullptr)
    return 1;

  int N, M;
  fscanf(f, "%d %d", &N, &M);

  for (int i = 1; i < N+1; i++) U[i] = i + 1 -(size[i] = 1);

  for (int i = 1; i < N+1; i++) {
    fscanf(f, "%d", &Morty[i]);
  }
  for (int i = 1; i < M+1; i++) {
    fscanf(f, "%d %d %d", &E[i][0], &E[i][1], &E[i][2]);
  }

  if (N <= 100000) quickSort(E, 1, M);

  int i, j = 1;
  bool flag = true;
  for (i = M; i > 0; i--) {
    Union(E[i][0], E[i][1]);
    for (int k = j; k < N+1; k++)
      if (find(k) != find(Morty[k])) {
        j = k;
        flag = false;
        break;
      }
      if (flag) break;
      flag = true;
  }
  printf("%d\n", E[i][2]);
}
