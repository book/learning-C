PUZZLES = $(wildcard *-input)
PROGS   = $(subst -input,-one,$(PUZZLES)) $(subst -input,-two,$(PUZZLES))

test: $(PROGS)
	@ for prog in $^ ; do \
		input=`echo $$prog | sed -e 's/one\|two/input/'` ; \
		echo -n "$$prog: " ; \
		./$$prog $$input ; \
	done

clean:
	rm -rf $(PROGS)
