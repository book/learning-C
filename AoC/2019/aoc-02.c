#include "aoc.h"
#include <string.h>
#define size 1024

int run( int *source, int val1, int val2 ) {
    int *program = malloc( size * sizeof( int ) );
    memcpy( program, source, size );
    program[1] = val1;
    program[2] = val2;

    int pc = 0;
    while ( 1 ) {
        switch ( program[pc] ) {
        case 1:
            program[program[pc + 3]] =
                program[program[pc + 1]] + program[program[pc + 2]];
            pc += 4;
            break;
        case 2:
            program[program[pc + 3]] =
                program[program[pc + 1]] * program[program[pc + 2]];
            pc += 4;
            break;
        case 99:
            return program[0];
        default:
            fprintf( stderr, "Unknown opcode: %i\n", program[pc] );
            exit( EXIT_FAILURE );
        }
    }
}

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
        printf( "%i\n", run( program, 12, 2 ) );
    }
    else {
    }

}
