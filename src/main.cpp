#include "rpc-test.h"

int main (int argc, char ** argv, char ** env) {
    int err;

    // Run the test function
    printf("Hello rpc lib %d\n", rpc_test());

    // Configure the server
    uint16_t port = 4000;
    char addr[] = "127.0.0.1";
    struct rpc_handler handlers[] = {
        NULL
    };
    int comm[2];
    struct rpc_server_config server_config = {
        .addr = addr,
        .port = port,
        .handlers = handlers,
        .comm = comm
    };

    // Configure the client
    struct rpc_client_config client_config = {
        .addr = addr,
        .port = 0,
    };

    // Start the server in the background
    rpc_server_start_background(&server_config);

    // Set the client port to be what the server reports its port is
    client_config.port = server_config.port;
    // Make a request
    printf("Client will connect to port %d\n", client_config.port);
    // Make the request
    err = rpc_client(&client_config);
    if (err == -1) {
        // Report the exit status and exit
        printf("Error from client: %d\n", errno);
    }

    // Stop the server before we (the client) exit
    rpc_server_stop(&server_config);

    return EXIT_SUCCESS;
}

