#ifndef STACK_H
#define STACK_H

//stack basic functional

typedef struct stack_t
{
    int32_t* items;
    int32_t size;
} stack_t;


stack_t* stack_init()
{
    stack_t *stack = (stack_t*)malloc(sizeof(stack_t));
    if (stack == NULL)
    {
        error_print(ALLOCATE);
        return NULL;
    }
    stack->items = NULL;
    //stack->items = malloc(1000000 * sizeof(int32_t));
    stack->size = 0;
    return stack;
}

int stack_empty(stack_t *stack)
{
    return (stack->size == 0) ? 1 : 0;
}

void stack_push(stack_t *stack, int32_t val)
{
    stack->size++;
    stack->items = realloc(stack->items, stack->size * sizeof(int32_t));
    if (stack->items == NULL)
    {
        error_print(ALLOCATE);
        exit(1);
    }
    stack->items[stack->size - 1] = val;
}

void stack_pop(stack_t *stack)
{
    if (!stack_empty(stack))
    {
        stack->size--;
        //stack->items = realloc(stack->items, stack->size * sizeof(int32_t));
    }
}

int32_t stack_front(stack_t *stack)
{
    if (!stack_empty(stack))
        return stack->items[stack->size - 1];
    //TODO: return something 
}

void debug_stack(stack_t *stack)
{
    printf("----DEBUG_STACK----\n");
    printf("Size: %d\n", stack->size);
    printf("Front: %d\n", stack_front(stack));
    printf("Is empty: %d\n", stack_empty(stack));
    printf("Stack: [");
    int i;
    for (i = 0; i < stack->size; ++i)
        printf("%d ", stack->items[i]);
    printf("]\n----DEBUG_STACK----\n");
}

#endif