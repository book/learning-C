#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

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
    const char *key2 = "foo2";
    const char *value2 = "bar2";

    fails += ok( value == hashtable_store( ht, key, strlen( key ), ( void * ) value ),
        "Stored value 'bar' in key 'foo'" );

/* - get it back */
    fails += ok( value == hashtable_fetch( ht, key, strlen( key ) ), "Fetched value 'bar' from key 'foo'" );
    fails += ok( NULL == hashtable_fetch( ht, "quux", 4 ), "Nothing at 'quux'" );

    fails += ok( value2 == hashtable_store( ht, key2, strlen( key2 ), ( void * ) value2 ),
        "Stored value 'bar2' in key 'foo2'" );
    fails += ok( value == hashtable_fetch( ht, key, strlen( key ) ), "Fetched value 'bar' from key 'foo'" );
    fails += ok( value2 == hashtable_fetch( ht, key2, strlen( key2 ) ), "Fetched value 'bar2' from key 'foo2'" );

/* - weird keys: NULL is considered equal to "" */
    fails += ok( value == hashtable_store( ht, NULL, 0, (void *) value ), "save with the NULL key" );
    fails += ok( value == hashtable_fetch( ht, NULL, 0 ), "fetch with the NULL key" );
    fails += ok( value2 == hashtable_store( ht, "", 0, (void *) value2 ), "save with the empty key");
    fails += ok( value2 == hashtable_fetch( ht, "", 0), "fetch with the empty key" );
    fails += ok( value2 == hashtable_fetch( ht, NULL, 0 ), "fetch with the NULL key" );

/* - delete it */
    fails += ok( value == hashtable_delete( ht, key, strlen(key) ), "delete entry 'foo'" );

/* - check it's gone */
    fails += ok( hashtable_fetch( ht, key, strlen(key) ) == NULL, "entry 'foo' is really gone" );

    /* - destroy the hashtable */
    hashtable_destroy( &ht );
    fails += ok( ht == NULL, "hashtable freed" );

  BAILOUT:
    exit( ! !fails );
}

