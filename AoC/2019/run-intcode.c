#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "intcode.h"
#define size 1024

int main( int argc, char **argv ) {

    // read the program form stdin in memory
    int *source = malloc( size * sizeof( int ) );
    int pc = 0;
    int Intcode;
    int res;
    while ( ( res = fscanf( stdin, "%i", &Intcode ) ) != EOF ) {
        source[pc++] = Intcode;
        res = fscanf( stdin, "," );
    }

    // get the input from the command-line
    struct stack *input = create_stack(  );
    for ( int i = 1; i < argc ; i++ ) {
	int item;
	sscanf( argv[i], "%i", &item );
        push_stack( input, item );
    }

    // run the program
    int *program = malloc( size * sizeof( int ) );
    memcpy( program, source, size );
    run( program, input );

    exit( 0 );
}

