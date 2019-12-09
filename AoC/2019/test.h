#include <stdio.h>

int ok( int test, char *mesg ) {
    if ( !test ) {
        printf( "not " );
    }
    printf( "ok - %s\n", mesg );
    return test;
}
