#include "aoc.h"
#include "intcode.h"
#include <string.h>
#define size 1024

int main( int argc, char **argv ) {
    int puzzle = 1;
    FILE *file;
    parse_options( argc, argv, 2, &puzzle, &file );

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
    if ( puzzle == 1 ) {
        memcpy( program, source, size );
        program[1] = 12;
        program[2] = 2;
        run( program, 0 );
        printf( "%i\n", program[0] );
    }
    else {
        int noun = 0;
        while ( 1 ) {
            int verb = 0;
            while ( verb <= noun ) {
                memcpy( program, source, size );
                program[1] = noun;
                program[2] = verb;
                run( program, 0 );
                if ( program[0] == 19690720 ) {
                    printf( "%i\n", 100 * noun + verb );
                    exit( 0 );
                }
                verb++;
            }
            noun++;
        }
    }
}
