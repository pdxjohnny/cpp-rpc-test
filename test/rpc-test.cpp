#include "rpc-test.h"

int main (int argc, char ** argv, char ** env) {
    int err;

    // Run the test function
    printf("Hello rpc lib %d\n", rpc_test());

    // Run all the tests

#ifdef RPC_TEST_SERVER
    // Server Tests
    RPC_TEST(test_server_correct_port);
#endif

#ifdef RPC_TEST_CLIENT
    // Client Tests
    RPC_TEST(test_client_contact_server);
#endif

#ifdef RPC_TEST_MESSAGE
    // Message Tests
    RPC_TEST(test_message_parse);
    RPC_TEST(test_message_malloc_free_buffer);
#endif

    return EXIT_SUCCESS;
}

