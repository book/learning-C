#include <stdio.h>
#include <stdlib.h>
#include <gcrypt.h>

#define input "bgvyzdsv"

void print_md5_hex( gcry_md_hd_t md5 ) {
    unsigned int len = gcry_md_get_algo_dlen( GCRY_MD_MD5 );    /* digest length */
    unsigned char *hash = gcry_md_read( md5, GCRY_MD_MD5 );     /* get the result */
    for ( unsigned int i = 0; i < len; i++ ) {
        printf( "%02x", hash[i] );      /* print the result */
    }
    printf( "\n" );
}

int main( void ) {
    char *value = malloc( 28 );
    int i = 1;

    while ( 1 ) {
        sprintf( value, "%s%d", input, i );
        gcry_md_hd_t md5;
        gcry_md_open( &md5, GCRY_MD_MD5, GCRY_MD_FLAG_SECURE ); /* initialise the hash context */
        gcry_md_write( md5, value, strlen( value ) );   /* hash some text */

        unsigned char *hash = gcry_md_read( md5, GCRY_MD_MD5 ); /* get the result */
        if ( hash[0] == 0 && hash[1] == 0 && ( hash[2] & 0xf0 ) == 0 ) {
            printf( "%d\n", i );
            gcry_md_close( md5 );
            break;
        }
        gcry_md_close( md5 );
        i++;
    }
    exit( 0 );
}
