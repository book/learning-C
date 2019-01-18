# default is the first target
check: hashtable
	@ ./hashtable

hashtable: hashtable.c
	gcc -std=c11 -o hashtable -Wall -Werror -Wextra -Wpedantic -g hashtable.c

clean:
	rm hashtable *.o *~
