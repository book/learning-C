#include <string.h>
#define MAX_ARGS 4
#define MAX_OPS  9

// arg count, including opcode
int args_for_op[] = {
    0,                          //    - invalid
    4,                          //  1 - add
    4,                          //  2 - mul
    2,                          //  3 - input
    2,                          //  4 - output
    3,                          //  5 - jump-if-true
    3,                          //  6 - jump-if-false
    4,                          //  7 - less-than
    4,                          //  8 - equals
};

int unroll_args( int *program, int pc, int *args ) {
    int opcode = args[0] = program[pc] % 100;
    if ( opcode > MAX_OPS )
        return opcode;          // 99

    int exponent = 100;
    for ( int i = 1; i < args_for_op[opcode]; i++ ) {
        int mode = program[pc] % ( 10 * exponent ) / exponent;
        args[i] = mode ? program[pc + i]        // immediate mode
            : program[program[pc + i]]; // position mode
        exponent *= 10;
    }
    return opcode;
}

// the Intcode computer
void run( int *program, int *input ) {
    int args[MAX_ARGS];         // opcode, arg1, arg2, etc
    int pc = 0;
    while ( 1 ) {
        int opcode = unroll_args( program, pc, args );
        switch ( opcode ) {
        case 1:                // add
            program[program[pc + 3]] = args[1] + args[2];
            pc += args_for_op[opcode];
            break;
        case 2:                // mul
            program[program[pc + 3]] = args[1] * args[2];
            pc += args_for_op[opcode];
            break;
        case 3:                // read input
            if ( input[0] < 1 ) {
                fprintf( stderr, "Input undeflow: %i\n", opcode );
                exit( EXIT_FAILURE );
            }
            program[program[pc + 1]] = input[input[0]--];
            pc += args_for_op[opcode];
            break;
        case 4:                // write output
            printf( "%i\n", args[1] );
            pc += args_for_op[opcode];
            break;
            break;
        case 99:
            return;
        default:
            fprintf( stderr, "Unknown opcode: %i at %i\n", opcode, pc );
            exit( EXIT_FAILURE );
        }
    }
}
