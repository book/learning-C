#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>

struct hashtable;

/* using a very BASIC hash function */
struct hashtable *hashtable_create( void );

void hashtable_destroy( struct hashtable **ht );

int hashtable_size( struct hashtable *ht );

void *hashtable_store( struct hashtable *ht, const char *key, size_t key_len, void *value );

void *hashtable_fetch( struct hashtable *ht, const char *key, size_t key_len );

int hashtable_exists( struct hashtable *ht, const char *key, size_t key_len );

void *hashtable_delete( struct hashtable *ht, const char *key, size_t key_len );

/*
 * TODO
 * - iteration (internal, external)
 * - clear
 * - better hashing
 */
#endif /* HASHTABLE_H */
