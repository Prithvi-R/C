#include <stdio.h>
#include <stdlib.h>
typedef int Type;

struct truct_t
{
    int front, rear;
    unsigned int capacity, size;
    Type *data;
};
typedef struct truct_t *Queue;

Queue createQueue(Queue queue, int capacity)
{
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = 0;
    queue->data = calloc(capacity, sizeof(Type));
    return queue;
}

int isFull(Queue queue)
{
    return (queue->capacity == queue->size);
}
int isEmpty(Queue queue)
{
    return (!queue->size);
}

int enqueue(Queue queue, Type data, int capacity)
{
    if (queue->size == queue->capacity)
        return 0;
    queue->front = queue->front % capacity;
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % capacity;
    queue->size++;
    return 1;
}
int dequeue(Queue queue, Type *pdata)
{
    if (queue->size == 0)
        return 0;
    *pdata = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return 1;
}
void print(Queue queue)
{
    for (int i = 0; i < queue->capacity; i++)
    {
        printf("%d ", queue->data[(queue->front + i) % queue->capacity]);
        printf("\n");
    }
}

int peekFront(Queue queue, Type *pdata)
{
    if (queue->size == 0)
        return 0;
    *pdata = queue->data[queue->front];
    return 1;
}
int peekBack(Queue queue, Type *pdata)
{
    if (queue->size == 0)
        return 0;
    int q = queue->rear;
    if (!queue->rear)
        q = queue->capacity;
    *pdata = queue->data[(q - 1) % queue->capacity];
    return 1;
}

int main()
{
    int n, status;
    Type data;
    Type *d;
    printf("Enter capacity for Queue: ");
    scanf("%d", &n);

    Queue queue = (Queue)calloc(1, sizeof(struct truct_t));
    queue = createQueue(queue, n);
    {
        printf("1 : enqueue:\n");
        printf("2 : dequeue:\n");
        printf("3 : isFull:\n");
        printf("4 : isEmpty:\n");
        printf("5 : PeekFront:\n");
        printf("6 : PeekBack:\n");
    }

    int choice;
    scanf("%d", &choice);
    while (1)
    {
        switch (choice)
        {
            {
                printf("1 : enqueue:\n");
                printf("2 : dequeue:\n");
                printf("3 : isFull:\n");
                printf("4 : isEmpty:\n");
                printf("5 : PeekFront:\n");
                printf("6 : PeekBack:\n");
            }
        case 1:
        {
            printf("Enter data: ");
            scanf("%d", &data);
            status = enqueue(queue, data, n);
            printf("Status:%d Data:%d\n", status, data);
            break;
        }
        case 2:
        {
            status = dequeue(queue, d);
            printf("Status:%d Data:%d\n", status, *d);
            break;
        }
        case 3:
        {
            print(queue);
            printf("isFull:%d\n", isFull(queue));
            break;
        }
        case 4:
        {
            print(queue);
            printf("isEmpty:%d\n", isEmpty(queue));
            break;
        }
        case 5:
        {
            status = peekFront(queue, d);
            printf("Status:%d Data:%d\n", status, *d);
            break;
        }
        case 6:
        {

            status = peekBack(queue, d);
            printf("Status:%d Data:%d\n", status, *d);
            break;
        }
        default:

            printf("diein");
            return 1;
        }
        scanf("%d", &choice);
    }

    return 0;
}