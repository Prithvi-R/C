#include <stdio.h>
#include <stdlib.h>

typedef struct heap_t *Heap;
struct heap_t
{
    int size, length;
    int *A;
};

void swap(int *a, int *b)
{
    int tem = *a;
    *a = *b;
    *b = tem;
}

/********************************************************
    || A || B|C || D|E |F |G || H|I | J|K | L | M| N|O ||
    ||15 ||11|14|| 9|10|13|7 || 8 4 | 2 5 | 12  6| 3 1 ||
********************************************************/
int parent(int i)
{
    return i / 2;
}

int left(int i)
{
    return 2 * i;
}

int right(int i)
{
    return 2 * i + 1;
}

void maxHeapify(Heap heap, int i)
{
    int l = left(i);
    int r = right(i);

    int largest = i;
    if (l < heap->size && heap->A[l] > heap->A[r] && heap->A[l] > heap->A[largest]) // left > right > i
        largest = l;
    if (l < heap->size && heap->A[r] > heap->A[largest])                            // right > left / i 
        largest = r;

    if (largest != i)
    {
        swap(&heap->A[i], &heap->A[largest]);
        maxHeapify(heap, largest);
    }
}

void buildMaxHeap(Heap heap)
{
    heap->size = heap->length;
    for (int i = (heap->length / 2); i > 0; i--)
        maxHeapify(heap, i);
}

void heapsort(Heap heap)
{
    int i = (heap->size);
    for (; i > 2; i--)                                                              //last 1 is smallest already
    {
        swap(&heap->A[1], &heap->A[heap->size]);
        heap->size -= 1;
        maxHeapify(heap, 1);
    }
}

int main()
{
    Heap heap = (Heap)calloc(1, sizeof(struct heap_t));
    int n, i = 0;
    printf("Enter the size of heap: ");
    scanf("%d", &n);
    heap->length = n;
    heap->A = calloc(n + 1, sizeof(int));                                            // one to strt the index from 1
    heap->A[0] = -1;                                                                 // garbage value at index 0
    printf("Enter the values: ");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &heap->A[i]);
    }

    buildMaxHeap(heap);
    printf("\n[heap-sort@heap ~]$ ");
    for (i = 1; i <= n; i++)
    {
        printf("%d ", heap->A[i]);
    }

    heapsort(heap);
    printf("\n[heap-sort@sort ~]$ ");
    for (i = 1; i <= n; i++)
    {
        printf("%d ", heap->A[i]);
    }
    return 0;
}