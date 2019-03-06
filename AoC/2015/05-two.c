#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <regex.h>


int main( int argc, char **argv ) {
    const char *filename = (argc > 1) ? argv[1] : "05-input";
    FILE *file = fopen( filename, "r" );
    if ( !file ) {
        perror( filename );
        exit( 1 );
    }

    /* compile the regular expressions */
    char *re_text[] = {
        "\\([a-z][a-z]\\).*\\1",
        "\\([a-z]\\).\\1",
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
    char *line = malloc( 1024 );
    int nice = 0;

    while ( !feof( file ) ) {
        fscanf( file, "%s\n", line );
        if ( !regexec( &regexp[0], line, 0, 0, 0 )
             && !regexec( &regexp[1], line, 0, 0, 0 ) ) {
            nice++;
        }
    }
    printf( "%d\n", nice );

    exit( 0 );
}
