#include <string.h>
#define size 1024

// the Intcode computer

void run( int *program ) {
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
            return;
        default:
            fprintf( stderr, "Unknown opcode: %i\n", program[pc] );
            exit( EXIT_FAILURE );
        }
    }
}
