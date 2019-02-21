#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#define max(a,b) a > b ? a : b

#define chunk 1024

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
    int k = max( abs( x ), abs( y ) );
    if ( abs( x ) > abs( y ) ) {
        if ( x >= 0 ) {
            return ( 2 * k - 1 ) * ( 2 * k - 1 ) + x + y - 1;
        }
        else {
            return ( 2 * k ) * ( 2 * k + 1 ) + x - y;
        }
    }
    else {
        if ( y > 0 ) {
            return ( 2 * k - 1 ) * ( 2 * k ) - x + y;
        }
        else {
            return ( 2 * k ) * ( 2 * k + 1 ) + x - y;
        }
    }
}

int main( int argc, char **argv ) {
    argc = argc;
    char c;
    FILE *file = fopen( argv[1], "r" );
    if ( !file ) {
        perror( argv[1] );
        exit( 1 );
    }

    int x = 0, y = 0;
    int size = chunk;           /* to force the first space allocation */
    int *space = malloc( chunk * sizeof( int ) );

    space[0]++;                 /* gift in the first house */

    while ( ( c = fgetc( file ) ) != EOF ) {
        switch ( c ) {
        case '>':
            x++;
            break;
        case '<':
            x--;
            break;
        case '^':
            y++;
            break;
        case 'v':
            y--;
            break;
        default:
            continue;
        }

        int i = spiral( x, y );

        /* expand the memory space if needed */
        while ( i > size + 1 ) {
            int *new_space = realloc( space, ( size + chunk ) * sizeof( int ) );
            if ( new_space ) {
                space = new_space;
                for ( int j = size; j < size + chunk; j++ ) {
                    space[j] = 0;
                }
            }
            else {
                perror( NULL );
                exit( 1 );
            }
            size += chunk;
        }
        space[i]++;
    }

    int minimum_one = 0;
    for ( int j = 0; j < size; j++ ) {
        if ( space[j] > 0 )
            minimum_one++;

    }
    printf( "%d\n", minimum_one );
    exit( 0 );
}
