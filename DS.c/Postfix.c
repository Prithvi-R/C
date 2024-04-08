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

int pop(Stack stack, Type *key)
{
    if (!stack || isEmpty(stack))
        return 0;
    stack->size--;
    *key = stack->data[stack->size];
    stack->front--;
    // stack->rear--;
    return 1;
}

int peek(Stack stack, Type *key)
{
    if (!stack || isEmpty(stack))
        return 0;
    *(key) = stack->data[stack->size - 1];
    return 1;
}
int precedence(Type op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

Type *convert(Type arr[], int n)
{
    Stack stack = createStack(n);
    Type *postfix = (Type *)calloc(n , sizeof(Type));
    int postfixIndex = 0;
    Type k;
    for (int i = 0; i < n; i++)
    {
        Type ch = arr[i];

        if (isalnum(ch))
        {
            postfix[postfixIndex++] = ch;
        }
        else if (ch == '(')
        {
            push(stack, ch);
        }
        else if (ch == ')')
        {
            while (!isEmpty(stack) && stack->data[stack->front] != '(')
            {
                pop(stack, &postfix[postfixIndex++]);
            }
            pop(stack, &k); //Discard '('
        }
        else
        {
            while (!isEmpty(stack)&&stack->data[stack->front]!='(' && precedence(stack->data[stack->front]) >= precedence(ch))//Operator encountered
            {
                pop(stack, &postfix[postfixIndex++]);
            }
            push(stack, ch);
        }
    }
    while (!isEmpty(stack))
    {
        pop(stack, &postfix[postfixIndex++]);
    }

    printf("Postfix expression: ");
    for (int i = 0; i < postfixIndex; i++)
    {
        printf("%c", postfix[i]);
    }
    printf("\n");
    return postfix;
}


int main()
{
    Type *arr = NULL;
    printf("Enter the infix expression: ");
    arr = (Type *)calloc(100 , sizeof(Type)); 
    scanf(" %[^\n]s", arr);
    int n = strlen(arr);
    arr = convert(arr, n);
    printf("Postfix expression: %s\n", arr);
    free(arr); 
    return 0;
}
