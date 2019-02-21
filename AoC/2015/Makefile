CFLAGS=-std=c11 -g -Wall -Werror -Wextra -Wpedantic

PROGS   = $(patsubst %.c,%,$(wildcard *-one.c) $(wildcard *-two.c))

test: $(PROGS)
	@ for prog in $$( echo $^ | sed -e 's/ /\n/g' | LC_ALL=C sort ) ; do \
		input=`echo $$prog | sed -e 's/one\|two/input/'` ; \
		echo -n "$$prog: " ; \
		./$$prog $$input ; \
	done

04-%: 04-%.c
	$(CC) $(CFLAGS) -lgcrypt $< -o $@

clean:
	rm -rf $(PROGS)
