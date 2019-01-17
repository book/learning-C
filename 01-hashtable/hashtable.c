#include <stdio.h>
#include <stdlib.h>

struct hashtable {
    int count;
};

struct hashtable* create_hashtable (void) {
    struct hashtable *ht = malloc( sizeof( struct hashtable ) );
    return ht;
}

int main( int argc, char **argv) { }

/* - create a hashtable */
  struct hashtable *ht;
  ht = create_hashtable();

  if( !ht ) { exit(1); }

/*
 * - check it's empty
 * - add something
 * - get it back
 * - delete it
 * - check it's gone
 * - destroy the hashtable
 */
