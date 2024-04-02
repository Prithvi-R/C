#include <stdio.h>
int search(int k, int arr[], int end)
{
    for(int i=0;i<end;i++){
        if(arr[i]==k)
            return i;
    }
    return -1;
}
int main(){
    int arr[10]={1,2,3,4,5,6,7,8,9,10},k;
    k=search(8,arr,10);
    printf("%d",k);
}