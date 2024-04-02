#include <stdio.h>
#include <stdlib.h> 

#define V 4

void addEdge(int arr[][V], int i, int j){
    arr[i][j] = 1;
    arr[j][i] = 1;
}

void printAdjMatrix(int arr[][V])
{
    int i, j;
    printf("   ");
    for (i = 0; i < V; i++)
    {
        printf("%d ", i);
    }
    printf("\n   ");
    for (i = 0; i < V; i++)
    {
        printf("_ ");
    }
    printf("\n");
    for (i = 0; i < V; i++)
    {

        printf("%d |", i);
        for (j = 0; j < V; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

unsigned int getbit(unsigned char *p, unsigned int i)
{
    // Corrected the mask shifting operation
    return ((*(p + (i / 8))) & (1 << (i % 8))) ? 1 : 0;
}

void setbit(unsigned char *pbit, int index)
{
    // Corrected the setting of the bit at the specified index
    pbit[index / 8] |= (1 << (index % 8));
}

int main(){
    {
        int adjMatrix[V][V] = {0};
        addEdge(adjMatrix, 0, 1);
        addEdge(adjMatrix, 0, 2);
        addEdge(adjMatrix, 1, 2);
        addEdge(adjMatrix, 2, 0);
        addEdge(adjMatrix, 2, 3);
        printf("\nPrint using Matrix-Sized 2D-array:\n\n");

        printAdjMatrix(adjMatrix);
    }

    unsigned char *bit = (unsigned char *)calloc(1, V * V / 8);

    int aij[V * V] = {0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0};

    for (int i = 0; i < V * V; i++){
        if (aij[i] == 1){
            setbit(bit, i);
        }
    }

    printf("\nPrint using Bit-Sized array:");
    for (int i = 0; i < V * V; i++){
        if(!(i%V))
            printf("\n");
        printf("%d ", getbit(bit, i));
    }
    free(bit);
    return 0;
}
