#include <stdio.h>
#include <stdlib.h>

struct hashtable {
    int count;
};

struct hashtable *create_hashtable(void)
{
    struct hashtable *ht = malloc(sizeof(struct hashtable));
    ht->count = 0;
    return ht;
}

int ok ( int test, char * mesg ) {
    printf( "%sok - %s\n", test ? "" : "not ", mesg );
    return !!test;
}

void destroy_hashtable( struct hashtable **ht ) {
    free(*ht);
    *ht = NULL;
}

int main(int argc, char **argv)
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
