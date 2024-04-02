#include <stdio.h>

int main()
{
    int a[] = {1, 10, 2, 0, 4, 6, 3};
    int n = 7;
    int i, j,key;
    for (i = 0; i < n; i++)
    {
        key=a[i];
        j=i-1;
        while(j>=0 && a[j]>key){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
    for ( i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}