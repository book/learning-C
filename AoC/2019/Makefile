CFLAGS=-std=c11 -g -Wall -Werror -Wextra -Wpedantic

all: $(patsubst %.c,%,$(wildcard aoc-*.c))

aoc-%: aoc-%.c aoc.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f aoc-[0-9][0-9]
