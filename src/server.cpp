#include "rpc.h"

int server(int argc, char ** argv, char ** env) {
    // Configure the server
    uint16_t port = 0;
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

    // Start the server in the background
    rpc_server_start_background(&server_config);

    // Set the client port to be what the server reports its port is
    port = server_config.port;
    printf("Serving on port %d\n", port);

    // Serve until told to stop
    char buffer[100];
    memset(buffer, 0, sizeof(buffer));
    while (read(STDIN_FILENO, buffer, sizeof(buffer)) > 0) {
        memset(buffer, 0, sizeof(buffer));
    }

    // Stop the server before we (the client) exit
    rpc_server_stop(&server_config);

    return EXIT_SUCCESS;
}

