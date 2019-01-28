#include "hashtable.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

/* hashtable implementation */
#define HASHTABLE_NUM_BUCKETS 16

struct hashtable_entry {
    const char *key;
    size_t key_len;
    void *value;
    struct hashtable_entry *prev_entry;
    struct hashtable_entry *next_entry;
};

struct hashtable {
    struct hashtable_entry **buckets;
};

/* using a very BASIC hash function */
static int hashtable_index_for( const char *key, int key_len ) {
    return key_len ? key[0] % HASHTABLE_NUM_BUCKETS : 0;
}

static struct hashtable_entry *hashtable_entry_for(
    struct hashtable *ht, const char *key, size_t key_len, bool create )
{
    int i = hashtable_index_for( key, key_len );
    struct hashtable_entry *entry = ht->buckets[i];
    while ( entry != NULL ) {
        if ( entry->key_len == key_len
             && memcmp( entry->key, key, key_len ) == 0 )
            break;
        entry = entry->next_entry;
    }
    if ( !entry && create ) {
        entry = calloc( 1, sizeof( struct hashtable_entry ) );
        entry->next_entry = ht->buckets[i];
        ht->buckets[i] = entry;
        if (entry->next_entry) {
            entry->next_entry->prev_entry = entry;
        }
    }
    return entry;
}

void hashtable_destroy( struct hashtable **ht ) {
    for ( int i = 0; i < HASHTABLE_NUM_BUCKETS; i++ ) {
        struct hashtable_entry *entry = (*ht)->buckets[i];
        while( entry ) {
            struct hashtable_entry *goner = entry;
            entry = entry->next_entry;
            free( goner );
        }
    }
    free( (*ht)->buckets );
    free( *ht );
    *ht = NULL;
}

struct hashtable *hashtable_create( void ) {
    struct hashtable *ht = malloc( sizeof( struct hashtable ) );
    ht->buckets = calloc( HASHTABLE_NUM_BUCKETS, sizeof( struct hashtable_entry * ));
    return ht;
}

int hashtable_size( struct hashtable *ht ) {
    int size = 0;
    for ( int i = 0; i < HASHTABLE_NUM_BUCKETS; i++ ) {
        struct hashtable_entry *entry = ht->buckets[i];
        while( entry ) {
	    size++;
            entry = entry->next_entry;
        }
    }
    return size;
}

void *hashtable_store( struct hashtable *ht, const char *key, size_t key_len,
                       void *value ) {
    struct hashtable_entry *entry =
        hashtable_entry_for( ht, key, key_len, true );
    entry->key = key;
    entry->key_len = key_len;
    return entry->value = value;
}

void *hashtable_fetch( struct hashtable *ht, const char *key, size_t key_len ) {
    struct hashtable_entry *entry =
        hashtable_entry_for( ht, key, key_len, false );
    return entry ? entry->value : NULL;
}

int hashtable_exists( struct hashtable *ht, const char *key, size_t key_len );
void *hashtable_delete( struct hashtable *ht, const char *key, size_t key_len ) {
    struct hashtable_entry *entry =
        hashtable_entry_for( ht, key, key_len, false );
    if ( !entry ) return NULL;
    if ( entry->prev_entry )
       entry->prev_entry->next_entry = entry->next_entry;
    void *value = entry->value;
    free( entry );
    return value;
}

