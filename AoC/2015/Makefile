CFLAGS=-std=c11 -g -Wall -Werror -Wextra -Wpedantic

PUZZLES = $(wildcard *-input)
PROGS   = $(subst -input,-one,$(PUZZLES)) $(subst -input,-two,$(PUZZLES))

test: $(PROGS)
	@ for prog in $$( echo $^ | sed -e 's/ /\n/g' | LC_ALL=C sort ) ; do \
		input=`echo $$prog | sed -e 's/one\|two/input/'` ; \
		echo -n "$$prog: " ; \
		./$$prog $$input ; \
	done

clean:
	rm -rf $(PROGS)
