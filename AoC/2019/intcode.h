#include <string.h>
#define PARAMS 3

int decode( int *mode, int input ) {
    int exponent = 100;
    for ( int i = 0; i < PARAMS; i++ ) {
        mode[i] = input % ( 10 * exponent ) / exponent;
        exponent *= 10;
    }
    return input % 100;
}

// the Intcode computer
void run( int *program, int input ) {
    int pc = 0;
    int opcode;
    int mode[PARAMS];
    while ( 1 ) {
        opcode = decode( mode, program[pc] );
        switch ( opcode ) {
        case 1:
            program[program[pc + 3]] =
                ( mode[0] ? program[pc + 1] : program[program[pc + 1]] )
                + ( mode[1] ? program[pc + 2] : program[program[pc + 2]] );
            pc += 4;
            break;
        case 2:
            program[program[pc + 3]] =
                ( mode[0] ? program[pc + 1] : program[program[pc + 1]] )
                * ( mode[1] ? program[pc + 2] : program[program[pc + 2]] );
            pc += 4;
            break;
        case 3:
            program[program[pc + 1]] = input;
            pc += 2;
            break;
        case 4:
            printf( "%i\n", mode[0] ? program[pc + 1] : program[program[pc + 1]] );
            pc += 2;
            break;
        case 99:
            return;
        default:
            fprintf( stderr, "Unknown opcode: %i\n", program[pc] );
            exit( EXIT_FAILURE );
        }
    }
}
