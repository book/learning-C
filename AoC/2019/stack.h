#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

struct stack {
    int size;
    int top;
    int *items;
};

struct stack *create_stack(  );

int pop_stack( struct stack *pile );

int push_stack( struct stack *pile, int item );

int clear_stack( struct stack *pile );

#endif /* STACK_H */
