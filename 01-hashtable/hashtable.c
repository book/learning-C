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

int main(int argc, char **argv)
{
     int fails = 0;

/* - create a hashtable */
    struct hashtable *ht;
    ht = create_hashtable();

    if (!ht) {
        exit(1);
    }

/* - check it's empty */
    fails += ok( ht->count == 0, "hashtable is empty" );
/*
 * - add something
 * - get it back
 * - delete it
 * - check it's gone
 * - destroy the hashtable
 */

    exit(!!fails);
}
