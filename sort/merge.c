#include <stdio.h>

void merge(int a[], int l, int mid, int h)
{
    int n1 = mid - l+1;
    int n2 = h - mid;
    int a1[n1], a2[n2], i, j, n = h + 1, k = l;
    for (i = 0; i < n1; i++)
    {
        a1[i] = a[l + i];
    }
   // a1[i] = 500;
    for (i = 0; i < n2; i++)
    {
        a2[i] = a[mid + 1 + i];
    }
    // a2[i] = 500;
    i = 0;
    j = 0;
    while (i < n1 && j < n2)
    {
        if (a1[i] <= a2[j])
        {
            a[k] = a1[i];
            i++;
        }
        else
        {
            a[k] = a2[j];
            j++;
        }
        k++;
    }
    while (i< n1){
        a[k]=a1[i];
        i++;
        k++;
    }
   while (j< n2){
        a[k]=a2[j];
        j++;
        k++;
    }

}

void mergesort(int a[], int l, int h)
{
    if (l < h)
    {
        int mid = (l + (h-1)) / 2;
        mergesort(a, l, mid);
        mergesort(a, mid + 1, h);
        merge(a, l, mid, h);
    }
}

int main()
{
    int a[] = {1, 10, 2, 20, 4, 6, 3};
    int n = 6;
    mergesort(a, 0, n);
    for (int i = 0; i <=n; i++)
    {
        printf("%d ", a[i]);
    }
}