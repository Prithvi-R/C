#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char Type;
typedef struct stack_t *Stack;

struct stack_t
{
    int front;
    Type *data;
    unsigned int capacity, size;
};

Stack createStack(int capacity)
{
    Stack stack = (Stack)malloc(sizeof(struct stack_t));
    stack->capacity = capacity;
    stack->front = 0;
    // stack->rear = stack->front - 1;
    stack->size = 0;
    stack->data = (Type *)malloc(capacity * sizeof(Type));
    return stack;
}

int isFull(Stack stack)
{
    return (stack->size == stack->capacity);
}
int isEmpty(Stack stack)
{
    return (!stack->size);
}

int push(Stack stack, Type value)
{
    if (!stack || isFull(stack))
        return 0;
    stack->front++;
    // stack->rear++;
    stack->data[stack->size] = value;
    stack->size++;
    return 1;
}

int pop(Stack stack, int *key)
{
    if (!stack || isEmpty(stack))
        return 0;
    stack->size--;
    *key = stack->data[stack->size];
    stack->front--;
    // stack->rear--;
    return 1;
}

int peek(Stack stack, int *key)
{
    if (!stack || isEmpty(stack))
        return 0;
    *(key) = stack->data[stack->size - 1];
    return 1;
}

int precedence(char op) {
    switch (op) {
        case '^':
            return 3;
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '%':
            return a % b;
        case '^': {
            int result = 1;
            for (int i = 0; i < b; i++) {
                result *= a;
            }
            return result;
        }
        default:
            return 0;
    }
}

int ans(Stack stack, char arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (isdigit(arr[i])) {
            push(stack, arr[i] - '0');
        } else if (arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/' || arr[i] == '%' || arr[i] == '^') {
            int a;pop(stack,&a);
            int b;pop(stack,&b);
            int result = applyOperation(a, b, arr[i]);
            push(stack, result);
        }
    }
    int m;peek(stack,&m);
    return m;
}

int main() {
    char *arr = NULL;
    printf("Enter the Prefix expression: ");
    arr = (char *)calloc(100 , sizeof(char)); 
    scanf(" %[^\n]s", arr);

    int n = strlen(arr);
    Stack stack = createStack(n);
    printf("Result: %d\n", ans(stack, arr, n));
    free(arr); 
    return 0;
}
