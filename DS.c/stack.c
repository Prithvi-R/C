#include <stdio.h>
#include <stdlib.h>

typedef int Type;
struct truct_t
{
    int front, rear;
    unsigned int capacity, size;
    Type *data;
};
typedef struct truct_t *Stack;

Stack createStack(Stack stack, int capacity)
{
    stack->capacity = capacity;
    stack->size = 0;
    stack->front = 0;
    stack->rear = stack->front - 1;
    stack->data = calloc(capacity, sizeof(Type));
    return stack;
}

int isFull(Stack stack)
{
    return (stack->capacity == stack->size);
}
int isEmpty(Stack stack)
{
    return (!stack->size);
}

int push(Stack stack, Type data, int capacity)
{
    if (stack->size == stack->capacity)
        return 0;
    stack->front++;
    stack->rear++;
    stack->data[stack->size] = data;
    stack->size++;
    return 1;
}
int pull(Stack stack, Type *pdata)
{
    if (stack->size == 0)
        return 0;
    stack->size--;
    stack->front--;
    stack->rear--;
    *pdata = stack->data[stack->size];
    return 1;
}

int peek(Stack stack, Type *pdata)
{
    if (stack->size == 0)
        return 0;
    *pdata = stack->data[stack->size - 1];
    return 1;
}

int main()
{
    int n, status;
    Type data;
    Type *d;
    printf("Enter capacity for Stack: ");
    scanf("%d", &n);

    Stack stack = (Stack)calloc(1, sizeof(struct truct_t));
    stack = createStack(stack, n);

    

    int choice;
    scanf("%d", &choice);
    while (1)
    {
        {
        printf("1 : Push:\n");
        printf("2 : Pull:\n");
        printf("3 : isFull:\n");
        printf("4 : isEmpty:\n");
        printf("5 : Peek:\n");
        }
        switch (choice)
        {
        case 1:
        {
            printf("Enter data: ");
            scanf("%d", &data);
            status = push(stack, data, n);
            printf("Status:%d Data:%d\n", status, data);
            break;
        }
        case 2:
        {
            status = pull(stack, d);
            printf("Status:%d Data:%d\n", status, *d);
            break;
        }
        case 3:
        {
            printf("isFull:%d\n", isFull(stack));
            break;
        }
        case 4:
        {
            printf("isEmpty:%d\n", isEmpty(stack));
            break;
        }
        case 5:
        {
            status = peek(stack, d);
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