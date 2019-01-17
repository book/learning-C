#include <stdio.h>
#include <stdlib.h>

struct hashtable {
    int count;
};

void destroy_hashtable( struct hashtable **ht ) {
    free(*ht);
    *ht = NULL;
}

/* hashtable implementation */
struct hashtable *create_hashtable(void)
{
    struct hashtable *ht = malloc(sizeof(struct hashtable));
    ht->count = 0;
    return ht;
}

int ok ( int test, char * mesg ) {
    printf( "%sok - %s\n", test ? "" : "not ", mesg );
    return !test;
}

/* test script */
int main(void)
{
     int fails = 0;

/* - create a hashtable */
    struct hashtable *ht;
    ht = create_hashtable();
    fails += ok(ht != NULL, "hashtable created" );
    if (!ht) { goto BAILOUT; }

/* - check it's empty */
    fails += ok( ht->count == 0, "hashtable is empty" );
/*
 * - add something
 * - get it back
 * - delete it
 * - check it's gone
 */

 /* - destroy the hashtable */
    destroy_hashtable( &ht );
    fails += ok( ht == NULL, "hashtable freed" );

BAILOUT:
    exit(!!fails);
}
