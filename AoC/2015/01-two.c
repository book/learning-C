#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main( int argc, char **argv ) {
    int floor = 0;
    int position = 1;
    char c;
    const char *filename = (argc > 1) ? argv[1] : "01-input";
    FILE *file = fopen( filename, "r" );
    if ( !file ) {
        perror( filename );
        exit( 1 );
    }
    while ( ( c = fgetc( file ) ) != EOF ) {
        floor += c == '(' ? 1 : -1;
        if ( floor == -1 )
            break;
        position++;
    }
    printf( "%d\n", position );
    exit(0);
}
