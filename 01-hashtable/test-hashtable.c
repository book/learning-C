#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "hashtable.h"

/* basic test function */
int global_tests = 0;
static int ok(int test, char *mesg ) {
    global_tests++;
    printf( "%sok %d - %s\n", test ? "" : "not ", global_tests, mesg );
    return !test;
}

/* test script */
int test_hash_with_function( hashtable_hash_function hash_function ) {
    int fails = 0;
    char mesg[128];

/* - create a hashtable */
    struct hashtable *ht;
    ht = hashtable_create( hash_function );
    fails += ok( ht != NULL, "hashtable created" );
    if ( !ht ) {
        goto BAILOUT;
    }

/* - check it's empty */
    fails += ok( hashtable_size(ht) == 0, "hashtable size == 0" );

/* - add something */
    const char *key = "foo";
    const char *value = "bar";
    const char *key2 = "foo2";
    const char *value2 = "bar2";

    fails += ok( NULL == hashtable_store( ht, key, strlen( key ), ( void * ) value ),
        "Stored value 'bar' in key 'foo'" );
    fails += ok( hashtable_size(ht) == 1, "hashtable size == 1" );

/* - get it back */
    fails += ok( value == hashtable_fetch( ht, key, strlen( key ) ), "Fetched value 'bar' from key 'foo'" );
    fails += ok( NULL == hashtable_fetch( ht, "quux", 4 ), "Nothing at 'quux'" );

    fails += ok( NULL == hashtable_store( ht, key2, strlen( key2 ), ( void * ) value2 ),
        "Stored value 'bar2' in key 'foo2'" );
    fails += ok( hashtable_size(ht) == 2, "hashtable size == 2" );
    fails += ok( value == hashtable_fetch( ht, key, strlen( key ) ), "Fetched value 'bar' from key 'foo'" );
    fails += ok( value2 == hashtable_fetch( ht, key2, strlen( key2 ) ), "Fetched value 'bar2' from key 'foo2'" );

/* - weird keys: NULL is considered equal to "" */
    fails += ok( NULL == hashtable_store( ht, NULL, 0, (void *) value ), "save with the NULL key" );
    fails += ok( hashtable_size(ht) == 3, "hashtable size == 3" );
    fails += ok( value == hashtable_fetch( ht, NULL, 0 ), "fetch with the NULL key" );
    fails += ok( value == hashtable_store( ht, "", 0, (void *) value2 ), "save with the empty key");
    fails += ok( hashtable_size(ht) == 3, "hashtable size == 3" );
    fails += ok( value2 == hashtable_fetch( ht, "", 0), "fetch with the empty key" );
    fails += ok( value2 == hashtable_fetch( ht, NULL, 0 ), "fetch with the NULL key" );

/* - delete it */
    fails += ok( value == hashtable_delete( ht, key, strlen(key) ), "delete entry 'foo'" );
    fails += ok( hashtable_size(ht) == 2, "hashtable size == 2" );

/* - check it's gone */
    fails += ok( hashtable_fetch( ht, key, strlen(key) ) == NULL, "entry 'foo' is really gone" );

/* add 100 items, forcing a few resizes */
    for ( int i = 0; i < 100; i++ ) {
	char key[4];
        sprintf( key, "%d", i );
	/* val will be freed when we remove the items from the hashtable */
	char * val = malloc( strlen(key) + 1 );
	sprintf( val, "%d", i );
        hashtable_store( ht, key, strlen(key), (void*) val );
    }
    fails += ok( hashtable_size(ht) == 102, "hashtable size == 102" );

/* check we can find some items */
    fails += ok( strcmp( hashtable_fetch( ht, "97", 0), "97"), "key 97 added" );
    fails += ok( hashtable_size(ht) == 102, "hashtable size == 102" );

/* check we can find all items */
    for ( int i = 99; i >= 0; i-- ) {
	char key[4];
        sprintf( key, "%d", i );
	char * expect = malloc( strlen(key) + 1 );
	sprintf( expect, "%d", i );
	char * actual = hashtable_fetch( ht, key, strlen(key) );
        sprintf( mesg, "fetched key %s", key );
        fails += ok( strcmp( actual, expect ) == 0, mesg );
	free( expect );

	char * actual2 = hashtable_delete( ht, key, strlen(key) );
        sprintf( mesg, "deleted key %s", key );
        fails += ok( actual == actual2, mesg );
	free( actual );
    }

    /* - hashtable is almost empty... */
    fails += ok( hashtable_size( ht ) == 2, "hashtable is almost empty" );
    char * item = hashtable_delete( ht, "foo2", 4 );
    fails += ok( strcmp( item, "bar2" ) == 0, "deleted key foo2" );
    item = hashtable_delete( ht, "", 0 );
    fails += ok( strcmp( item, "bar2" ) == 0, "deleted NULL/empty key" );

    /* - hashtable should be empty */
    fails += ok( hashtable_size( ht ) == 0, "hashtable is empty" );

    /* - destroy the hashtable */
    hashtable_destroy( &ht );
    fails += ok( ht == NULL, "hashtable freed" );

  BAILOUT:
    return fails;
}

unsigned int hash_function_0 ( const char *key, size_t key_len ) {
    (void)key;    /* pretend we're using the variables */
    (void)key_len;
    return UINT_MAX;
}

int main( void ) {
    int fails = 0;
    fails += test_hash_with_function( NULL );
    fails += test_hash_with_function( hash_function_0 );

/* - done testing */
    printf( "1..%d\n", global_tests );

    exit( ! !fails );
}
