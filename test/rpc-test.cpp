#include "rpc-test.h"

int main (int argc, char ** argv, char ** env) {
    int err;

    // Run the test function
    printf("Hello rpc lib %d\n", rpc_test());

    // Run all the tests

    // Server Tests
    RPC_TEST(test_server_correct_port);

    // Client Tests
    RPC_TEST(test_client_contact_server);

    // Server Benchmarks
    RPC_TEST(benchmark_server_connections_per_minute);

    return EXIT_SUCCESS;
}

