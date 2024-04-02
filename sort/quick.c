#include <stdio.h>
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int a[],int l,int h)
{
    int pivot=a[h-1];
    int i=l;
    int j=i-1;
    for(;i<h-1;i++){
        if(a[i]<=pivot){
            j++;
            swap(&a[i],&a[j]);
        }
    }
    swap(&a[j+1],&a[h-1]);
    return j+1;
}

void quicksort(int a[], int low, int high)
{
    if (low < high)
    {
        int part = partition(a,low,high);
        quicksort(a, low, part);
        quicksort(a, part+1, high);
    }
}

int main()
{
    int a[] = {1, 10, 2, 20, 4, 6, 3};
    int n = 6;
    quicksort(a, 0, n+1);
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
}