#include "aoc.h"
#include <math.h>

int main( int argc, char **argv ) {
    int puzzle = 1;
    FILE *file;
    parse_options( argc, argv, 1, &puzzle, &file );

    // read the next line
    int res;
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
