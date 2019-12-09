#include <stdio.h>
#include "stack.h"
#include "test.h"

int main( void ) {
    struct stack *pile = create_stack(  );
    ok( pile != NULL, "created a stack" );
    ok( pile->size == 1, "size" );
    push_stack( pile, 123 );
    ok( pile->items[pile->top] == 123, "push" );
    push_stack( pile, 456 );
    ok( pile->size == 2, "size" );
    ok( pile->items[pile->top] == 456, "push" );
    ok( pile->items[pile->top - 1] == 123, "push" );
    push_stack( pile, 789 );
    ok( pile->items[pile->top] == 789, "push" );
    ok( pile->top == 2, "top" );
    ok( pile->size == 4, "size" );
    ok( pop_stack( pile ) == 789, "pop" );
    ok( pile->top == 1, "top" );
    ok( pop_stack( pile ) == 456, "pop" );
    ok( pile->top == 0, "top" );
    ok( pop_stack( pile ) == 123, "pop" );
    ok( pile->top == -1, "top" );
}
