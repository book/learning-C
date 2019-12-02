#include "aoc.h"

int main( int argc, char **argv ) {
    int puzzle = 1;
    FILE *file;
    parse_options( argc, argv, 2, &puzzle, &file );

    // read the program in
    int *program = malloc( 1024 * sizeof( int ) );
    int pc = 0;
    int Intcode;
    int res;
    while ( ( res = fscanf( file, "%i", &Intcode ) ) != EOF ) {
        program[pc++] = Intcode;
        res = fscanf( file, "," );
    }

    // run the program
    pc = 0;
    // restore gravity assist
    program[1] = 12;
    program[2] = 2;

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
            printf( "%i\n", program[0] );
            exit( 0 );
            break;
        default:
            fprintf( stderr, "Unknown opcode: %i\n", program[pc] );
            exit( EXIT_FAILURE );
        }
    }
}
