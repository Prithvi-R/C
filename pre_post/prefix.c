#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char Type;
typedef struct stack_t *Stack;

struct stack_t
{
    int top;
    Type *data;
    unsigned int capacity, size;
};

Stack createStack(int capacity)
{
    Stack stack = (Stack)malloc(sizeof(struct stack_t));
    stack->capacity = capacity;
    stack->top = -1;
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
    return (stack->top == -1);
}

int push(Stack stack, Type value)
{
    if (!stack || isFull(stack))
        return 0;
    stack->top++;
    stack->data[stack->top] = value;
    stack->size++;
    return 1;
}

int pop(Stack stack, Type *key)
{
    if (!stack || isEmpty(stack))
        return 0;
    *key = stack->data[stack->top];
    stack->top--;
    stack->size--;
    return 1;
}

int peek(Stack stack, Type *key)
{
    if (!stack || isEmpty(stack))
        return 0;
    *key = stack->data[stack->top];
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
    Type *prefix = (Type *)calloc(n, sizeof(Type));
    int prefixIndex = 0;
    Type k;
    // Reverse the input array to convert to prefix
    for (int i = n - 1; i >= 0; i--)
    {
        Type ch = arr[i];

        if (isalnum(ch))
        {
            prefix[prefixIndex++] = ch;
        }
        else if (ch == ')')
        {
            push(stack, ch);
        }
        else if (ch == '(')
        {
            while (!isEmpty(stack) && peek(stack, &k) != 0 && k != ')')
            {
                pop(stack, &prefix[prefixIndex++]);
            }
            // Pop '('
            pop(stack, &k);
        }
        else
        {
            while (!isEmpty(stack) && peek(stack, &k) != 0 && k != ')' && precedence(k) >= precedence(ch))
            {
                pop(stack, &prefix[prefixIndex++]);
            }
            push(stack, ch);
        }
    }
    // Pop remaining operators from the stack
    while (!isEmpty(stack))
    {
        pop(stack, &prefix[prefixIndex++]);
    }

    // Reverse the prefix expression
    for (int i = 0; i < prefixIndex / 2; i++)
    {
        Type temp = prefix[i];
        prefix[i] = prefix[prefixIndex - i - 1];
        prefix[prefixIndex - i - 1] = temp;
    }

    printf("Prefix expression: ");
    for (int i = 0; i < prefixIndex; i++)
    {
        printf("%c", prefix[i]);
    }
    printf("\n");
    return prefix;
}

int main()
{
    Type *arr = NULL;
    printf("Enter the infix expression: ");
    arr = (Type *)calloc(100, sizeof(Type));
    scanf(" %[^\n]s", arr);
    int n = strlen(arr);
    Type *prefix = convert(arr, n);
    printf("Prefix expression: %s\n", prefix);
    free(arr);
    free(prefix);
    return 0;
}
