SHELL=/bin/bash
CFLAGS=-std=c11 -g -Wall -Werror -Wextra -Wpedantic
LDADD=-lm

all: $(patsubst %.c,%,$(wildcard aoc-*.c))

stack.o: stack.c stack.h
	$(CC) -c $(CFLAGS) -O2 -o $@ $<

intcode.o: intcode.c intcode.h stack.o
	$(CC) -c $(CFLAGS) -O2 -o intcode.o intcode.c

aoc-%: aoc-%.c aoc.h
	$(CC) $(CFLAGS) $(LDADD) $< -o $@

aoc-02: aoc-02.c aoc.h intcode.o stack.o
	$(CC) $(CFLAGS) -o $@ intcode.o stack.o $<

aoc-05: aoc-05.c aoc.h intcode.o stack.o
	$(CC) $(CFLAGS) -o $@ intcode.o stack.o $<

run-intcode: run-intcode.c intcode.o stack.o
	$(CC) $(CFLAGS) -o $@ intcode.o stack.o $<

test-stack: test-stack.c test.h stack.o
	$(CC) $(CFLAGS) -o $@ stack.o $<

test: all
	@if [ $$( ./aoc-01 -1 ) -eq 3161483 ] ; then echo -n ok ; else echo -n not ok ; fi ; echo " day 1.1"
	@if [ $$( ./aoc-01 -2 ) -eq 4739374 ] ; then echo -n ok ; else echo -n not ok ; fi ; echo " day 1.2"
	@if [ $$( ./aoc-02 -1 ) -eq 3765464 ] ; then echo -n ok ; else echo -n not ok ; fi ; echo " day 2.1"
	@if [ $$( ./aoc-02 -2 ) -eq    7610 ] ; then echo -n ok ; else echo -n not ok ; fi ; echo " day 2.2"
	@if [ $$( ./aoc-03 -1 ) -eq     806 ] ; then echo -n ok ; else echo -n not ok ; fi ; echo " day 3.1"
	@#if [ $$( ./aoc-03  -2 ) -eq        ] ; then echo -n ok ; else echo -n not ok ; fi ; echo " day 3.2"
	@if [ $$( ./aoc-04 -1 ) -eq    1048 ] ; then echo -n ok ; else echo -n not ok ; fi ; echo " day 4.1"
	@if [ $$( ./aoc-04 -2 ) -eq     677 ] ; then echo -n ok ; else echo -n not ok ; fi ; echo " day 4.2"
	@if [ $$( ./aoc-05 -1 | tail -1 ) -eq 5821753 ] ; then echo -n ok ; else echo -n not ok ; fi ; echo " day 5.1"

unit: test-stack
	@./test-stack

clean:
	rm -f aoc-[0-9][0-9]
