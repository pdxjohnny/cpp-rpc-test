CC=g++
CFLAGS=-Wall -c -static -I./rpc/include/
LIBS=rpc/bin/librpc.a
LDFLAGS=
TEST_SOURCES=$(wildcard test/*.cpp)
TEST_OBJECTS=$(addprefix obj/test/,$(notdir $(TEST_SOURCES:.cpp=.o)))
CLI_SOURCES=$(wildcard src/*.cpp)
CLI_OBJECTS=$(addprefix obj/cli/,$(notdir $(CLI_SOURCES:.cpp=.o)))
TEST=bin/rpc-test
CLI=bin/rpc

all: $(TEST_SOURCES) $(CLI_SOURCES) $(TEST) $(CLI)

$(CLI): $(CLI_OBJECTS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) $(CLI_OBJECTS) $(LIBS) -o $@

$(TEST): $(TEST_OBJECTS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) $(TEST_OBJECTS) $(LIBS) -o $@

obj/test/%.o: test/%.cpp
	@mkdir -p obj/test
	$(CC) $(CFLAGS) $< -o $@

obj/cli/%.o: src/%.cpp
	@mkdir -p obj/cli
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf obj/* bin/*

