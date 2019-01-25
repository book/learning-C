# default is the first target
#

CFLAGS=-std=c11 -g -Wall -Werror -Wextra -Wpedantic

check: hashtable
	@ ./hashtable

hashtable: hashtable.c
	gcc $(CFLAGS) -O2 -o hashtable hashtable.c

cover: hashtable.c
	gcc $(CFLAGS) \
		-O0 -fprofile-arcs -ftest-coverage \
		-o hashtable-cover hashtable.c
	./hashtable-cover
	gcov --all-blocks --branch-probabilities --branch-counts --display-progress --use-colors hashtable.c
	less -R hashtable.c.gcov

clean:
	rm -f hashtable *.o *~
