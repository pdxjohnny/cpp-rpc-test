CC=g++
CFLAGS=-Wall -c -static -I./rpc/include/
LIBS=rpc/bin/librpc.a
LDFLAGS=
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
BIN=bin/rpc-test

all: $(SOURCES) $(BIN)

$(BIN): $(OBJECTS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f obj/* bin/*

