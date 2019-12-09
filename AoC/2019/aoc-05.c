#include <string.h>

#include "aoc.h"
#include "stack.h"
#include "intcode.h"
#define size 1024

int main( int argc, char **argv ) {
    int puzzle = 1;
    FILE *file;
    parse_options( argc, argv, 5, &puzzle, &file );

    // read the program in memory
    int *source = malloc( size * sizeof( int ) );
    int pc = 0;
    int Intcode;
    int res;
    while ( ( res = fscanf( file, "%i", &Intcode ) ) != EOF ) {
        source[pc++] = Intcode;
        res = fscanf( file, "," );
    }

    // run the program
    int *program = malloc( size * sizeof( int ) );
    memcpy( program, source, size );

    struct stack *input = create_stack(  );
    if ( puzzle == 1 ) {
        push_stack( input, 1 );
        run( program, input );
    }
    exit( 0 );
}
