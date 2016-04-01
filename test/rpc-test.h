#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <librpc.h>

// Which tests to run
#define RPC_TEST_SERVER
#define RPC_TEST_CLIENT
#define RPC_TEST_MESSAGE
// Which benchmarks to run
#define RPC_BENCHMARK_SERVER

#define RPC_TEST(test_name) \
({\
    err = test_name();\
    if (err == -1) {\
        printf("test_name exited with status %d", errno);\
    }\
})


// Server Tests
int test_server_correct_port();

// Client Tests
int test_client_contact_server();

// Message Tests
int test_message_parse();

// Server Benchmarks
int benchmark_server_connections_per_minute();

