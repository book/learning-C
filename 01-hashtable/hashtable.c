#include "hashtable.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct hashtable_entry {
    const char *key;
    size_t key_len;
    void *value;
    struct hashtable_entry *prev_entry;
    struct hashtable_entry *next_entry;
};

struct hashtable {
    size_t num_buckets;
    size_t num_items;
    struct hashtable_entry **buckets;
    hashtable_hash_function hash_function;
};

/* default hash function (very basic) */
unsigned int hash_code_default( const char *key, size_t key_len ) {
    return key_len ? key[0] : 0;
}

/* some private functions */
static void hashtable_resize( struct hashtable *ht, size_t num_buckets ) {
    struct hashtable_entry **buckets = calloc( num_buckets, sizeof( struct hashtable_entry * ));
    if (!buckets) {
        exit(EXIT_FAILURE);
    }

    /* visit the hashtable and copy the entries over */
    for ( size_t i = 0; i < ht->num_buckets; i++ ) {
        struct hashtable_entry *entry = ht->buckets[i];
        while( entry ) {

            unsigned int hash_code = ht->hash_function( entry->key, entry->key_len );
            size_t j = hash_code % num_buckets;

            struct hashtable_entry *new_entry = calloc( 1, sizeof( struct hashtable_entry ) );
            if (!new_entry) {
                exit(EXIT_FAILURE);
            }
            new_entry->key = entry->key;
            new_entry->key_len = entry->key_len;
            new_entry->value = entry->value;
            new_entry->next_entry = buckets[j];
            buckets[j] = new_entry;
            if (new_entry->next_entry) {
                new_entry->next_entry->prev_entry = new_entry;
            }

            /* drop the old entry and move on */
            struct hashtable_entry *goner = entry;
            entry = entry->next_entry;
            free( goner );
        }
    }
    free( ht->buckets );

    /* replace */
    ht->num_buckets = num_buckets;
    ht->buckets = buckets;
}

static size_t hashtable_index_for( struct hashtable *ht, const char *key, size_t key_len ) {
    return ht->hash_function( key, key_len ) % ht->num_buckets;
}

static struct hashtable_entry *hashtable_entry_for(
    struct hashtable *ht, const char *key, size_t key_len, bool create )
{
    size_t i = hashtable_index_for( ht, key, key_len );
    struct hashtable_entry *entry = ht->buckets[i];
    while ( entry != NULL ) {
        if ( entry->key_len == key_len
             && memcmp( entry->key, key, key_len ) == 0 )
            break;
        entry = entry->next_entry;
    }
    if ( !entry && create ) {
        entry = calloc( 1, sizeof( struct hashtable_entry ) );
        if (! entry) {
            exit(EXIT_FAILURE);
        }
        entry->next_entry = ht->buckets[i];
        entry->key = calloc( 1, key_len + 1 );
        if (! entry->key ) {
            exit(EXIT_FAILURE);
        }
        memcpy( (char *)entry->key, key, key_len);
	*(char*)(entry->key + key_len)='\0';
        entry->key_len = key_len;
        ht->buckets[i] = entry;
        ht->num_items++;
        if (entry->next_entry) {
            entry->next_entry->prev_entry = entry;
        }
    }
    return entry;
}

/* public interface */
struct hashtable *hashtable_create( hashtable_hash_function hash_function ) {

    struct hashtable *ht = malloc( sizeof( struct hashtable ) );
    if (!ht) {
        exit(EXIT_FAILURE);
    }
    ht->num_buckets = 16;
    ht->num_items = 0;
    ht->hash_function = hash_function ? hash_function : hash_code_default;
    ht->buckets = calloc( ht->num_buckets, sizeof( struct hashtable_entry * ));
    if (! ht->buckets) {
        exit(EXIT_FAILURE);
    }
    return ht;
}

void hashtable_destroy( struct hashtable **ht ) {
    for ( size_t i = 0; i < (*ht)->num_buckets; i++ ) {
        struct hashtable_entry *entry = (*ht)->buckets[i];
        while( entry ) {
            struct hashtable_entry *goner = entry;
            entry = entry->next_entry;
            free( (void *)goner->key );
            free( goner );
        }
    }
    free( (*ht)->buckets );
    free( *ht );
    *ht = NULL;
}

size_t hashtable_size( struct hashtable *ht ) {
    return ht->num_items;
}

void *hashtable_store( struct hashtable *ht, const char *key, size_t key_len,
                       void *value ) {
    if ( ht->num_items > ht->num_buckets * .8 ) {
        hashtable_resize( ht, 2 * ht->num_buckets );
    }
    struct hashtable_entry *entry =
        hashtable_entry_for( ht, key, key_len, true );
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
    if ( !entry )
        return NULL;
    if ( entry->prev_entry ) {
        entry->prev_entry->next_entry = entry->next_entry;
    }
    /* if there's no previous entry, then the entry to delete was the first */
    /* find our bucket, and point it to its successor, if any */
    else {
        size_t i = hashtable_index_for( ht, key, key_len );
        ht->buckets[i] = entry->next_entry;
        if ( ht->buckets[i] ) {
            ht->buckets[i]->prev_entry = NULL;
        }
    }

    void *value = entry->value;
    ht->num_items--;
    free( (char*) entry->key );
    free( entry );
    return value;
}
