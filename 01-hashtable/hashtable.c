#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

/* hashtable implementation */
struct hashtable {
    int count;

};

void hashtable_destroy( struct hashtable **ht ) {
    free( *ht );
    *ht = NULL;
}

struct hashtable *hashtable_create( void ) {
    struct hashtable *ht = malloc( sizeof( struct hashtable ) );
    ht->count = 0;
    return ht;
}

void *hashtable_store( struct hashtable *ht, const char *key, size_t key_len,
                       void *value ) {
    assert( ht != NULL );
    assert( key != NULL );
    assert( key_len <= INT_MAX );
    return value;
}

void *hashtable_fetch( struct hashtable *ht, const char *key, size_t key_len );
int hashtable_exists( struct hashtable *ht, const char *key, size_t key_len );
void *hashtable_delete( struct hashtable *ht, const char *key, size_t key_len );

/* basic test function */
int ok( int test, char *mesg ) {
    printf( "%sok - %s\n", test ? "" : "not ", mesg );
    return !test;
}

/* test script */
int main( void ) {
    int fails = 0;

/* - create a hashtable */
    struct hashtable *ht;
    ht = hashtable_create(  );
    fails += ok( ht != NULL, "hashtable created" );
    if ( !ht ) {
        goto BAILOUT;
    }

/* - check it's empty */
    fails += ok( ht->count == 0, "hashtable is empty" );

/* - add something */
    const char *key = "foo";
    const char *value = "bar";
    ok( value == hashtable_store( ht, key, strlen( key ), ( void * ) value ),
        "Stored value 'bar' in key 'foo'" );
/*
 * - get it back
 * - delete it
 * - check it's gone
 */

    /* - destroy the hashtable */
    hashtable_destroy( &ht );
    fails += ok( ht == NULL, "hashtable freed" );

  BAILOUT:
    exit( ! !fails );
}
