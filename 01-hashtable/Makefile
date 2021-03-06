# default is the first target
#

CFLAGS=-std=c11 -g -Wall -Werror -Wextra -Wpedantic

check: test-hashtable
	@ ./test-hashtable

hashtable.o: hashtable.h hashtable.c
	gcc -c $(CFLAGS) -O2 -o hashtable.o hashtable.c

test-hashtable: hashtable.o test-hashtable.c
	gcc $(CFLAGS) -O2 -o test-hashtable hashtable.o test-hashtable.c

cover: hashtable.h hashtable.c test-hashtable.c
	gcc --coverage -c $(CFLAGS) -O0 -o hashtable.o hashtable.c
	mv hashtable.o hashtable+coverage.o
	gcc $(CFLAGS) \
		-O0 -fprofile-arcs -ftest-coverage \
		-o cover-hashtable hashtable+coverage.o test-hashtable.c
	./cover-hashtable
	gcov --all-blocks --branch-probabilities --branch-counts \
		--display-progress --use-colors test-hashtable.c hashtable.c
	less -R hashtable.c.gcov

hashtable-O0.o:
	gcc -c $(CFLAGS) -O0 -o hashtable-O0.o hashtable.c

valgrind-hashtable: test-hashtable.c hashtable-O0.o
	gcc $(CFLAGS) -O0 -o valgrind-hashtable hashtable-O0.o test-hashtable.c

valgrind: valgrind-hashtable
	valgrind -q --leak-check=full ./valgrind-hashtable

clean:
	rm -f test-hashtable valgrind-hashtable cover-hashtable \
		*.o *~ *.gcda *.gcno *.gcov
