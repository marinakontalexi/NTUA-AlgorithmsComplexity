#include <bits/stdc++.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int arr[20001],kappa[1000001];
int main(int argc, char *argv[]) {
    FILE *f;
    if ((f = fopen(argv[1], "rt")) == nullptr)
    return 1;

    int n,k,result=20001,left_sum,right_sum;
    fscanf(f, "%d %d", &n, &k);
    for (int i=1; i < n+1 ; i++){
        fscanf(f, "%d", &arr[i]);
    }
    for(int l=0; l<k+1; l++){
        kappa[l]=-1;
    }

    for (int y=1; y<n+1; y++){
        left_sum=0;
        right_sum=0;
        for(int i=y; i>0; i--){
            left_sum+=arr[i];
            if (left_sum>k) break;
            if (left_sum==k) result=min(result,y-i+1);
            else if (kappa[left_sum]==-1) kappa[left_sum]=y-i+1;
            else kappa[left_sum]= min(kappa[left_sum],y-i+1);
        }
        for (int j=y+1; j<n; j++){
            right_sum+=arr[j];
            if (right_sum>k) break;
            if(right_sum==k) result= min(result,j-y);
            else if (kappa[k-right_sum]!=-1) result = min(j-y+kappa[k-right_sum],result);
        }

    }
    if (result ==20001) cout << -1 <<endl;
    else cout << result << endl;
    return 0;
}
