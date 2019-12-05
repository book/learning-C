#include "aoc.h"
#include <sys/types.h>
#include <regex.h>
int main( int argc, char **argv ) {
    int puzzle = 1;
    FILE *file;
    parse_options( argc, argv, 4, &puzzle, &file );

    /* compile the regular expressions */
    char *re_text[] = {
        "\\([0-9]\\)\\1",       // Two adjacent digits are the same( like 22 in 122345 ).
        "^0*1*2*3*4*5*6*7*8*9*$"        // Going from left to right, the digits never decrease;
    };
    regex_t regexp[2];
    for ( int i = 0; i < 2; i++ ) {
        int re_error = regcomp( &regexp[i], re_text[i], REG_NOSUB );
        if ( re_error ) {
            int errbuf_size = regerror( re_error, &regexp[i], NULL, 0 );
            char *errbuf = malloc( errbuf_size );
            regerror( re_error, &regexp[i], errbuf, errbuf_size );
            printf( "%s in %s\n", errbuf, re_text[i] );
            exit( 1 );
        }
    }

    /* read the file */
    int from, to;
    fscanf( file, "%i-%i\n", &from, &to );

    int valid = 0;
    for ( int i = from; i <= to; i++ ) {
        char *password;
        password = malloc( 7 * sizeof( char ) );
        sprintf( password, "%i", i );
        if ( !regexec( &regexp[0], password, 0, 0, 0 )
             && !regexec( &regexp[1], password, 0, 0, 0 ) )
            valid++;
    }
    printf( "%i\n", valid );
    exit( 0 );
}
