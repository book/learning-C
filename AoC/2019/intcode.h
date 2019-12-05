#include <string.h>
#define size 1024

// the Intcode computer

int *run( int *source, int val1, int val2 ) {
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
            return program;
        default:
            fprintf( stderr, "Unknown opcode: %i\n", program[pc] );
            exit( EXIT_FAILURE );
        }
    }
}
