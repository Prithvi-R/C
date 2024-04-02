#include <stdio.h>
// #include
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a[] = {1, 10, 2, 0, 4, 6, 3};
    int n = 7;
    int i, j;
    for (i = 0; i <= n; i++)
    {
        j=i-1;
        while (j && a[j] < a[j - 1])
        {
            swap(&a[j],&a[j-1]);
            j--;
        }
    }
    for ( i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}