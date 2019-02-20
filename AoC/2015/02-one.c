#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int cmp( const void *A, const void *B ) {
    int a = *( const int * ) A;
    int b = *( const int * ) B;
    if ( a < b )
        return -1;
    if ( a == b )
        return 0;
    return 1;
}

int main( int argc, char **argv ) {
    argc = argc;
    int total = 0;
    int dim[3];
    FILE *file = fopen( argv[1], "r" );
    if ( !file ) {
        perror( argv[1] );
        exit( 1 );
    }

    while ( !feof( file ) ) {
        fscanf( file, "%dx%dx%d\n", &dim[0], &dim[1], &dim[2] );
        qsort( dim, 3, sizeof( int ), &cmp );
        total += 3 * dim[0] * dim[1]
            + 2 * dim[1] * dim[2]
            + 2 * dim[0] * dim[2];
    }
    printf( "%d\n", total );
    exit( 0 );
}
