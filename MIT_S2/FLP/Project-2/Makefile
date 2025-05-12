# Author: Alexej Beňuš xbenus01@stud.fit.vutbr.cz
# Brief: Makefile
NAME = flp24-log
SRC = main.pl input2.pl myIO.pl movement.pl goalState.pl search.pl
COMPILER = swipl
STARTFUNCTION = -g start

# Default target
all:
	$(COMPILER) $(STARTFUNCTION) -o $(NAME) -c $(SRC)

# Clean
clean:
	rm -f $(NAME)
	rm -rf tests/out

# Run tests
test: all
	@mkdir -p tests/out
	@for f in tests/*.txt; do \
		out=tests/out/$$(basename $$f); \
		printf "Running $$f\n"; \
		./$(NAME) < $$f > $$out; \
		printf "Output written to $$out\n\n"; \
	done