#include <stdio.h>
int search(int k, int arr[], int start, int end)
{
    if(start<=end){
        int m = (start + end) / 2;
        if (k == arr[m]){
            return m;
        }
        if (k > arr[m]){
            return search(k, arr, m + 1, end);
        }
        if(k<arr[m])
            return search(k, arr, start, m - 1);
    }
    return -1;
}
int main(){
    int arr[10]={1,2,3,4,5,6,7,8,9,10},k;
    k=search(9,arr,0,10);
    printf("%d",k);
}