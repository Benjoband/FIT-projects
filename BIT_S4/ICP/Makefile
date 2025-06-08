# Not working, use for doxygen and clean only
# use cmake or QT for compiling
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -Isrc -fPIC

UI_FILES := $(wildcard src/.ui)
UI_HEADERS := $(patsubst %.ui,%.h,$(UI_FILES))

QT_LIBS = $(shell pkg-config --libs Qt5Core Qt5Network Qt5Widgets)
QT_INCLUDE = $(shell pkg-config --cflags Qt5Core Qt5Network Qt5Widgets)

SRCS := $(wildcard src/*.cpp) \
        $(wildcard src/communication/*.cpp) \
        $(wildcard src/client_objects/*.cpp) \
        $(wildcard src/server_objects/*.cpp)

OBJS := $(SRCS:.cpp=.o) $(UI_HEADERS:.h=.o)

all: pacman

pacman: $(OBJS)
    ${CXX} ${CXXFLAGS} ${QT_LIBS} -o $@ $^

%.o: %.cpp
    ${CXX} ${CXXFLAGS} ${QT_INCLUDE} -c $< -o $@

%.h: %.ui
    uic $< -o $@

clean:
    rm -f ${OBJS} pacman 

doxygen:
    doxygen Doxyfile