#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main( int argc, char **argv ) {
    int floor = 0;
    char c;
    FILE *file = fopen( argv[1], "r" );
    if ( !file ) {
        perror( argv[1] );
        exit( 1 );
    }
    while ( ( c = fgetc( file ) ) != EOF ) {
        floor += c == '(' ? 1 : -1;
    }
    printf( "%d\n", floor );
    exit;
}
