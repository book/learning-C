#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

/* hashtable implementation */
#define HASHTABLE_NUM_BUCKETS 16

struct hashtable_entry {
    const char *key;
    size_t key_len;
    void *value;
    struct hashtable_entry *next_entry;
};

struct hashtable {
    struct hashtable_entry *buckets[HASHTABLE_NUM_BUCKETS];
};

/* using a very BASIC hash function */
static int hashtable_index_for( const char *key, int key_len ) {
    return key_len ? key[0] % HASHTABLE_NUM_BUCKETS : 0;
}

static struct hashtable_entry * hashtable_entry_for( struct hashtable *ht, const char *key, size_t key_len ) {
    int i = hashtable_index_for( key, key_len );
    struct hashtable_entry *entry = ht->buckets[i];
    if( entry == NULL ) {
        return ht->buckets[i] = calloc( 1, sizeof( struct hashtable_entry ) );
    }
    return entry;
}

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

void *hashtable_store( struct hashtable *ht, const char *key, size_t key_len,
                       void *value ) {
    struct hashtable_entry *entry = hashtable_entry_for( ht, key, key_len );
    entry->key = key;
    entry->key_len = key_len;
    return entry->value = value;
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
