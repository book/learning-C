#include "aoc.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>

#define chunk 16

/* Convert from x,y coordinates to ones in a number spiral
 *
 *     16 15 14 13 12          (0, 0) -> 0
 *     17  4  3  2 11          (1, 1) -> 2
 *     18  5  0  1 10         ( 2,-1) -> 9
 *     19  6  7  8  9         (-2, 2) -> 16
 *     20 21 22 23 24         (-1,-2) -> 21
 *
 * This will let us store data mapping to a grid into a flat structure,
 * that can grow as needed.
 */
int spiral( int x, int y ) {
    int k = abs( x ) + abs( y ) + abs( abs( x ) - abs( y ) );
    if ( abs( x ) > abs( y ) ) {
        if ( x >= 0 ) {
            return ( k - 1 ) * ( k - 1 ) + x + y - 1;
        }
        else {
            return k * ( k + 1 ) + x - y;
        }
    }
    else {
        if ( y > 0 ) {
            return ( k - 1 ) * k - x + y;
        }
        else {
            return k * ( k + 1 ) + x - y;
        }
    }
}

void update_panel( int **panel_ptr, int x, int y ) {
    int *panel = *panel_ptr;
    int pos = spiral( x, y );
    while ( pos > panel[0] ) {
        int new_size = ( 1 + pos / chunk ) * chunk + 1;
        int *new_panel = realloc( panel, new_size * sizeof( int ) );
        if ( new_panel ) {
            *panel_ptr = panel = new_panel;
            for ( int j = panel[0] + 1; j <= new_size; j++ ) {
                panel[j] = 0;
            }
            panel[0] = new_size - 1;
        }
        else {
            perror( NULL );
            exit( 1 );
        }
    }
    panel[pos + 1] = abs( x ) + abs( y );
}

int main( int argc, char **argv ) {
    int puzzle = 1;
    FILE *file;
    parse_options( argc, argv, 3, &puzzle, &file );

    // load the wire paths
    int **panel;
    panel = malloc( 2 * sizeof( int * ) );
    panel[0] = malloc( 2 * sizeof( int ) );
    panel[1] = malloc( 2 * sizeof( int ) );
    panel[0][0] = panel[1][0] = 1;      // keep track of the panel size
    panel[0][1] = panel[1][1] = 0;      // origin is at distance 0

    int i = 0;
    int x, y;
    char dir;
    x = y = 0;
    while ( ( dir = fgetc( file ) ) != EOF ) {
        int steps;
        int res = fscanf( file, "%i", &steps );
        if ( res == EOF ) {
            fprintf( stderr, "Unexpected EOF" );
            exit( EXIT_FAILURE );
        }
        switch ( dir ) {
        case 'U':
            for ( int j = 0; j < steps; j++ ) {
                update_panel( &panel[i], x, ++y );
            }
            break;
        case 'D':
            for ( int j = 0; j < steps; j++ ) {
                update_panel( &panel[i], x, --y );
            }
            break;
        case 'R':
            for ( int j = 0; j < steps; j++ ) {
                update_panel( &panel[i], ++x, y );
            }
            break;
        case 'L':
            for ( int j = 0; j < steps; j++ ) {
                update_panel( &panel[i], --x, y );
            }
            break;
        default:
            fprintf( stderr, "Unknown direction: %c\n", dir );
            exit( EXIT_FAILURE );
        }
        char sep = fgetc( file );
        if ( sep == EOF ) {
            fprintf( stderr, "Unexpected EOF" );
            exit( EXIT_FAILURE );
        }
        switch ( sep ) {
        case ',':
            break;
        case '\n':
            x = y = 0;          // start at origin on next panel
            i++;
            break;
        default:
            fprintf( stderr, "Unknown direction: %c\n", dir );
            exit( EXIT_FAILURE );
        }
    }

    // no need to go further than the smallest panel
    int limit = panel[0][0] < panel[1][0] ? panel[0][0] : panel[1][0];

    // find the smallest crossing
    int min = limit;            // sentinel
    for ( int j = 2; j <= limit; j++ ) {
        if ( panel[0][j] != 0 && panel[0][j] == panel[1][j]
             && panel[0][j] < min ) {
            min = panel[0][j];
        }
    }

    printf( "%i\n", min );
    exit( 0 );
}
