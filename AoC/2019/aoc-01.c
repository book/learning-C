#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

int main( int argc, char **argv ) {
    int puzzle = 1;
    int total = 0;
    int res;

    // parse command-line
    int opt;

    while ( ( opt = getopt( argc, argv, "12" ) ) != -1 ) {
        switch ( opt ) {
        case '1':
            puzzle = 1;
            break;
        case '2':
            puzzle = 2;
            break;
        default:               /* '?' */
            fprintf( stderr, "Usage: %s [-1|-2] [file]\n", argv[0] );
            exit( EXIT_FAILURE );
        }
    }

    // open the file
    const char *filename = ( optind < argc ) ? argv[optind] : "aoc-01.input";
    FILE *file = fopen( filename, "r" );
    if ( !file ) {
        perror( filename );
        exit( 1 );
    }

    // read the next line
    int module, total_fuel;
    while ( ( res = fscanf( file, "%i", &module ) ) != EOF ) {

        int fuel;
        total_fuel += fuel = floor( module / 3 ) - 2;

        if ( puzzle == 2 ) {
            int extra = fuel;
            while ( extra > 8 ) {
                extra = floor( extra / 3 ) - 2;
                total_fuel += extra;
            }
        }
    }

    printf( "%i\n", total_fuel );
    exit( 0 );
}
