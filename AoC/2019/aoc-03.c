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

struct cell {
    int position;               // spiral coordinate
    int distance;               // distance from origin
    int steps;                  // number of steps to get there
};

struct ribbon {
    int size;                   // number of available cell slots
    int steps;                  // number of actual cells
    struct cell **cells;
};

int cmp_cells( const void *a, const void *b ) {
    struct cell A = *( struct cell * )a;
    struct cell B = *( struct cell * )b;
    printf( "cmp [ %i %i %i ] [ %i %i %i ]\n",
         A.position, A.distance, A.steps,
         B.position, B.distance, B.steps );
    return A.position < B.position ? -1
         : A.position > B.position ?  1
	 :                            0;
            //( ( struct cell * ) a )->position, ( ( struct cell * ) a )->distance, ( ( struct cell * ) a )->steps,
            //( ( struct cell * ) b )->position, ( ( struct cell * ) b )->distance, ( ( struct cell * ) b )->steps );
    //return ( ( struct cell * ) a )->position <
    //    ( ( struct cell * ) b )->position ? -1 : ( ( struct cell * ) a )->
    //    position > ( ( struct cell * ) b )->position ? 1 : 0;
}

void extend_wire( struct ribbon *strip, int x, int y, int steps ) {
    if ( steps > strip->size - 1 ) {
        int new_size = strip->size + chunk;
        struct cell **new_cells =
            realloc( strip->cells, new_size * sizeof( struct cell * ) );
        if ( new_cells ) {
            strip->size = new_size;
            strip->cells = new_cells;
        }
    }

    // add the newly visited cell at the end
    strip->steps = steps;
    strip->cells[steps] = malloc( sizeof( struct cell ) );
    strip->cells[steps]->position = spiral( x, y );
    strip->cells[steps]->distance = abs( x ) + abs( y );
    strip->cells[steps]->steps = steps;
}

int main( int argc, char **argv ) {
    int puzzle = 1;
    FILE *file;
    parse_options( argc, argv, 3, &puzzle, &file );

    // initialize the ribbon / strip / wire
    struct ribbon strip[2];
    for ( int j = 0; j <= 1; j++ ) {
        strip[j].cells = malloc( chunk * sizeof( struct cell * ) );
        strip[j].size = chunk;  // keep track of the strip size
        strip[j].steps = 0;     // start at the origin
        strip[j].cells[0] = malloc( sizeof( struct cell ) );    // origin
        strip[j].cells[0]->distance = 0;        // origin at distance 0
        strip[j].cells[0]->steps = 0;   // origin at step 0
    }

    // load the wire paths
    int i = 0;
    int x, y;
    int total_steps;
    char dir;
    x = y = 0;
    total_steps = 0;
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
                extend_wire( &strip[i], x, ++y, ++total_steps );
            }
            break;
        case 'D':
            for ( int j = 0; j < steps; j++ ) {
                extend_wire( &strip[i], x, --y, ++total_steps );
            }
            break;
        case 'R':
            for ( int j = 0; j < steps; j++ ) {
                extend_wire( &strip[i], ++x, y, ++total_steps );
            }
            break;
        case 'L':
            for ( int j = 0; j < steps; j++ ) {
                extend_wire( &strip[i], --x, y, ++total_steps );
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
            total_steps = 0;
            i++;
            break;
        default:
            fprintf( stderr, "Unknown direction: %c\n", dir );
            exit( EXIT_FAILURE );
        }
    }

    printf( "done reading\n");

    // dump
    for ( i = 0; i <= 1 ; i ++ ) {
    printf( "size = %i, steps = %i\n", strip[0].size, strip[0].steps );
    for ( int j = 0; j <= strip[i].steps ; j++ ) {
	printf( "[ %i %i %i ] ", strip[i].cells[j]->position, strip[i].cells[j]->distance, strip[i].cells[j]->steps );
    }
    printf( "\n");
    }

    // sort the cells by spiral coordinates
    for ( i = 0; i <= 1; i++ ) {
        //qsort( strip[i].cells[1], strip[i].steps , sizeof( struct cell *), &cmp_cells );
        qsort( strip[i].cells[1], 3 , sizeof( struct cell *), &cmp_cells );
	printf("--\n");
    }
    printf( "done sorting\n");

    // no need to go further than the length of the smallest wire
    int limit = strip[0].steps < strip[1].steps ? strip[0].steps : strip[1].steps;

    // find the closest intersection
    int min = limit;            // sentinel
    int j = i = 1;              // start position on both wires
    while ( i < limit && j < limit ) {
	// intersection
	if ( strip[0].cells[i]->position == strip[1].cells[j]->position ) {
            if ( puzzle == 1 && strip[0].cells[i]->distance < min ) {
                min = strip[0].cells[i]->distance;
	    }
	    else {
		    // TODO
	    }
	    i++;
	}
	else  if ( strip[0].cells[i]->position < strip[1].cells[j]->position ) {
	    i++;
	}
	else {
	    j++;
	}
    }
    printf( "%i\n", min );

    exit( 0 );
}
