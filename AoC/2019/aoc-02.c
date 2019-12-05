#include "aoc.h"
#include "intcode.h"
#include <string.h>
#define size 1024

int main( int argc, char **argv ) {
    int puzzle = 1;
    FILE *file;
    parse_options( argc, argv, 2, &puzzle, &file );

    // read the program in memory
    int *program = malloc( size * sizeof( int ) );
    int pc = 0;
    int Intcode;
    int res;
    while ( ( res = fscanf( file, "%i", &Intcode ) ) != EOF ) {
        program[pc++] = Intcode;
        res = fscanf( file, "," );
    }

    // run the program
    if ( puzzle == 1 ) {
        int *state = run( program, 12, 2 );
        printf( "%i\n", state[0] );
    }
    else {
        int noun = 0;
        while ( 1 ) {
            int verb = 0;
            while ( verb <= noun ) {
                int *state = run( program, noun, verb );
                if ( state[0] == 19690720 ) {
                    printf( "%i\n", 100 * noun + verb );
                    exit( 0 );
                }
                verb++;
            }
            noun++;
        }
    }
}
