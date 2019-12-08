#include <string.h>
#define MAX_ARGS 4

void set_args( int *program, int *args, int pc, int count ) {
    int exponent = 100;
    args[0] = program[pc];
    for ( int i = 1; i < count; i++ ) {
        int mode = program[pc] % ( 10 * exponent ) / exponent;
        args[i] = mode ? program[pc + i]        // immediate mode
            : program[program[pc + i]]; // position mode
        exponent *= 10;
    }
}

// the Intcode computer
void run( int *program, int *input ) {
    int args[MAX_ARGS];         // opcode, arg1, arg2, etc
    int pc = 0;
    while ( 1 ) {
        int opcode = program[pc] % 100;
        switch ( opcode ) {
        case 1:                // add
            set_args( program, args, pc, 4 );
            program[program[pc + 3]] = args[1] + args[2];
            pc += 4;
            break;
        case 2:                // mul
            set_args( program, args, pc, 4 );
            program[program[pc + 3]] = args[1] * args[2];
            pc += 4;
            break;
        case 3:                // read input
            if ( input[0] < 1 ) {
                fprintf( stderr, "Input undeflow: %i\n", opcode );
                exit( EXIT_FAILURE );
            }
            set_args( program, args, pc, 2 );
            program[program[pc + 1]] = input[input[0]--];
            pc += 2;
            break;
        case 4:                // write output
            set_args( program, args, pc, 2 );
            printf( "%i\n", args[1] );
            pc += 2;
            break;
        case 99:
            return;
        default:
            fprintf( stderr, "Unknown opcode: %i at %i\n", opcode, pc );
            exit( EXIT_FAILURE );
        }
    }
}
