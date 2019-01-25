# default is the first target
#

CFLAGS=-std=c11 -g -Wall -Werror -Wextra -Wpedantic

check: test-hashtable
	@ ./test-hashtable

test-hashtable: hashtable.c test-hashtable.c
	gcc $(CFLAGS) -O2 -o test-hashtable test-hashtable.c

cover: hashtable.c test-hashtable
	gcc $(CFLAGS) \
		-O0 -fprofile-arcs -ftest-coverage \
		-o cover-hashtable test-hashtable.c
	./cover-hashtable
	gcov --all-blocks --branch-probabilities --branch-counts --display-progress --use-colors hashtable.c
	less -R hashtable.c.gcov

clean:
	rm -f test-hashtable cover-hashtable *.o *~ *.gcda *.gcno *.gcov
