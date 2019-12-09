#include "stack.h"

void dump_array( int count, int *args, char *mesg );

int unroll_args( int *program, int pc, int *args );

void run( int *program, struct stack *input );
