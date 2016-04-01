CC=g++
CFLAGS=-Wall -c -static -I./rpc/include/
LIBS=rpc/bin/librpc.a
LDFLAGS=
# Build the test suite
TEST_SOURCES=$(wildcard test/*.cpp)
TEST_OBJECTS=$(addprefix obj/test/,$(notdir $(TEST_SOURCES:.cpp=.o)))
TEST=bin/rpc-test
# Build the benchmarks
BENCHMARK_SOURCES=$(wildcard benchmark/*.cpp)
BENCHMARK_OBJECTS=$(addprefix obj/benchmark/,$(notdir $(BENCHMARK_SOURCES:.cpp=.o)))
BENCHMARK=bin/rpc-benchmark
# Build the cli
CLI_SOURCES=$(wildcard src/*.cpp)
CLI_OBJECTS=$(addprefix obj/cli/,$(notdir $(CLI_SOURCES:.cpp=.o)))
CLI=bin/rpc

all: $(TEST_SOURCES) $(BENCHMARK_SOURCES) $(CLI_SOURCES) $(TEST) $(BENCHMARK) $(CLI)

$(TEST): $(TEST_OBJECTS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) $(TEST_OBJECTS) $(LIBS) -o $@

$(BENCHMARK): $(BENCHMARK_OBJECTS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) $(BENCHMARK_OBJECTS) $(LIBS) -o $@

$(CLI): $(CLI_OBJECTS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) $(CLI_OBJECTS) $(LIBS) -o $@

obj/test/%.o: test/%.cpp
	@mkdir -p obj/test
	$(CC) $(CFLAGS) $< -o $@

obj/benchmark/%.o: benchmark/%.cpp
	@mkdir -p obj/benchmark
	$(CC) $(CFLAGS) $< -o $@

obj/cli/%.o: src/%.cpp
	@mkdir -p obj/cli
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf obj/* bin/*

