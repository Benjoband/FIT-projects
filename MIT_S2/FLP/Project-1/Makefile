# Makefile
# Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
# 2023-10-02
# Makefile

# Sources:
SOURCES =	./src/Main.hs \
			./src/DecisionTree.hs \
			./src/ParseArgs.hs \
			./src/ParseTree.hs \
			./src/Classification.hs \
			./src/ParseTraining.hs \
			./src/TrainingData.hs \
			./src/Cart.hs \
			./src/Helpers.hs

# Binary
EXECUTABLE = flp-fun
TEST_EXECUTABLE = ./tests/flp-fun
merlin_libncursesw_path = /lib/x86_64-linux-gnu/libncursesw.so.6.4

.PHONY: all clean

all: $(EXECUTABLE)

# make build on merlin possible
build-merlin:
	mkdir -p ./libs
	ln -s $(merlin_libncursesw_path) ./libs/libncursesw.so.5
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):./libs make build
	rm -rf ./libs

$(EXECUTABLE): $(SOURCES)
	ghc -Wall -o $(EXECUTABLE) $(SOURCES)

$(TEST_EXECUTABLE): $(SOURCES)
	ghc -Wall -o $(TEST_EXECUTABLE) $(SOURCES)

clean:
	rm -f $(EXECUTABLE)
	rm -f src/*.o src/*.hi
	rm -f tests/*.out ./*.out

# Running tests 
test1: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE) -1 ./trained/penguins_all.csv tmp

test2: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE) -2 ./datasets/penguins_all.csv

officialTest: $(TEST_EXECUTABLE)
	python3 ./tests/test_flp.py --test_type b