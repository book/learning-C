#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>

void parse_options( int argc, char **argv, int day, int *puzzle, FILE **file ) {

    // parse command-line
    int opt;

    while ( ( opt = getopt( argc, argv, "12" ) ) != -1 ) {
        switch ( opt ) {
        case '1':
            *puzzle = 1;
            break;
        case '2':
            *puzzle = 2;
            break;
        default:               /* '?' */
            fprintf( stderr, "Usage: %s [-1|-2] [file]\n", argv[0] );
            exit( EXIT_FAILURE );
        }
    }

    // open the file
    char *filename;
    if ( optind < argc ) {
	 filename = argv[optind];
    }
    else {
	filename = malloc( 13 );
        sprintf( filename, "aoc-%02d.input", day );
    }

    *file = fopen( filename, "r" );
    if ( !file ) {
        perror( filename );
        exit( 1 );
    }
}
