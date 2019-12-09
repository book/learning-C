#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

struct stack *create_stack(  ) {
    struct stack *pile = malloc( sizeof( struct stack ) );
    pile->top = -1;
    pile->size = 1;
    pile->items = malloc( sizeof( int ) );
    return pile;
}

int pop_stack( struct stack *pile ) {
    if ( pile->top < 0 ) {
        fprintf( stderr, "Stack underflow\n" );
        exit( EXIT_FAILURE );
    }
    return pile->items[pile->top--];
}

int push_stack( struct stack *pile, int item ) {
    if ( pile->top >= pile->size - 1 ) {
        int *new_items = realloc( pile->items, pile->size * 2 * sizeof( int ) );
        if ( new_items ) {
            pile->size *= 2;
            pile->items = new_items;
        }
        else {
            fprintf( stderr, "Can't extend stack from %i to %i\n", pile->size,
                     pile->size * 2 );
            exit( EXIT_FAILURE );
        }
    }
    pile->items[++pile->top] = item;
    return pile->top;
}

int clear_stack( struct stack *pile ) {
    return pile->top = -1;
}
