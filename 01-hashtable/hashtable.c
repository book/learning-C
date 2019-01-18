#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

/* hashtable implementation */
#define HASHTABLE_NUM_BUCKETS 16

struct hashtable_entry {
    char *key;
    char *value;
    struct hashtable_entry *next_entry;
};

struct hashtable {
    struct hashtable_entry buckets[HASHTABLE_NUM_BUCKETS];
};

void hashtable_destroy( struct hashtable **ht ) {
    free( *ht );
    *ht = NULL;
}

struct hashtable *hashtable_create( void ) {
    struct hashtable *ht = malloc( sizeof( struct hashtable ) );
    return ht;
}

int hashtable_size( struct hashtable *ht ) {
    assert( ht != NULL );
    return 0;
}

void *hashtable_store( struct hashtable *ht, const char *key, size_t key_len, void *value ) {
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
    fails += ok( hashtable_size(ht) == 0, "hashtable is empty" );

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
