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
    int total = 0;
    int dim[3];
    const char *filename = (argc > 1) ? argv[1] : "02-input";
    FILE *file = fopen( filename, "r" );
    if ( !file ) {
        perror( filename );
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
