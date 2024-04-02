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
    int sw = 0;
    for (int i = 0; i < n; i++)
    {
        while (!sw)
        {
            sw = 1;
            for (int j = 0; j < n - i - 1; j++)
            {
                if (a[j] > a[j + 1])
                {
                    swap(&a[j], &a[j + 1]);
                    sw = 0;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}