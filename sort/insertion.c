#include <stdio.h>

int main()
{
    int a[] = {1, 10, 2, 0, 4, 6, 3};
    int n = 7;
    int i, j,key;
    for (i = 0; i < n-1; i++)
    {
        for(int j=i+1;j>0;j--){
            if(a[j-1]>=a[j]){
                int temp=a[j-1];
                a[j-1]=a[j];
                a[j]=temp;
            }else{
                break;
            }
        }
    }
    for ( i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}