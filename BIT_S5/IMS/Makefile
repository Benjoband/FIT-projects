CC := g++
CCFLAGS :=  -lstdc++ -lsimlib -g -Wall -Wextra

TARGET = model

FILES = vlakyZ.cpp generator.cpp main.cpp

all: $(TARGET)

$(TARGET): $(FILES)
	$(CC) -o $(TARGET) $(FILES) $(CCFLAGS)

clean:
	rm -f $(TARGET) *.out

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run