#include "aoc.h"
#include <sys/types.h>
#include <regex.h>

int main( int argc, char **argv ) {
    int puzzle = 1;
    FILE *file;
    parse_options( argc, argv, 4, &puzzle, &file );

    /* compile the regular expressions */
    char *re_text[] = {
        "^0*1*2*3*4*5*6*7*8*9*$",       // Going from left to right, the digits never decrease;
        "\\(\\([0-9]\\)\\2\\2*\\)"      // Two adjacent digits are the same( like 22 in 122345 ).
    };
    regex_t regexp[2];
    for ( int i = 0; i < 2; i++ ) {
        int re_error = regcomp( &regexp[i], re_text[i], 0 );
        if ( re_error ) {
            int errbuf_size = regerror( re_error, &regexp[i], NULL, 0 );
            char *errbuf = malloc( errbuf_size );
            regerror( re_error, &regexp[i], errbuf, errbuf_size );
            printf( "%s in %s\n", errbuf, re_text[i] );
            exit( 1 );
        }
    }

    /* read the input */
    int from, to;
    fscanf( file, "%i-%i\n", &from, &to );

    /* test all passwords in the range */
    int valid = 0;
    for ( int i = from; i <= to; i++ ) {
        char *password;
        password = malloc( 7 * sizeof( char ) );
        sprintf( password, "%i", i );

        regmatch_t pmatch[3];
        if ( !regexec( &regexp[0], password, 3, pmatch, 0 ) ) {
            if ( !regexec( &regexp[1], password, 3, pmatch, 0 ) ) {
                if ( puzzle == 1 ) {
                    valid++;
                }
                else {
                    // at least one the multiples must be a pair
                    char *substr = password;
                    while ( !regexec( &regexp[1], substr, 3, pmatch, 0 ) ) {
                        if ( pmatch[1].rm_eo - pmatch[1].rm_so == 2 ) {
                            valid++;
			    break;
                        }
                        substr = &substr[pmatch[1].rm_eo];
                    }
                }
            }
        }
    }
    printf( "%i\n", valid );
    exit( 0 );
}
