# Makefile
# Author: Alexej Beňuš xbenus02@stud.fit.vutbr.cz
# Date: 2025-08-05

CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -std=c++20 -O2 #-DENABLE_DEBUG
LDFLAGS :=

TARGET := lz_codec
SRC_DIR := src
OBJ_DIR := obj
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean test testm testa testma testmany testdecompress

all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Pattern rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET) before.raw output.ben tmp*.txt

# --- Test targets ---
test: all
	./lz_codec -i tests/df1v.raw -o output.ben -c -w 512

testm: all
	./lz_codec -i tests/cb.raw -o output.ben -c -w 512 -m

testa: all
	./lz_codec -i tests/cb.raw -o output.ben -c -w 512 -a

testma: all
	./lz_codec -i tests/cb.raw -o output.ben -c -w 512 -m -a

testdecompress: all
	./lz_codec -i output.ben -o before.raw

testmany: all
	@for f in tests/*.raw; do \
		for opt in "-m -a" "-m" "-a" " "; do \
			echo "Testing $$f with options $$opt"; \
			./lz_codec -i $$f -o output.ben -c -w 512 $$opt; \
			./lz_codec -i output.ben -o before.raw; \
			diff -q $$f before.raw || echo "FAILED: $$f with $$opt"; \
		done; \
	done