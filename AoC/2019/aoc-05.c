#include "aoc.h"
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
    if ( puzzle == 1 ) {
        run( program, 1 );
    }
}
