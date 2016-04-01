#include "rpc.h"

int handler_not_found(int client, struct rpc_message * msg) {
    printf("Not found handler called\n");

    char reply[] = "HTTP/1.1 404 OK\r\n\r\nNot Found\r\n";
    write(client, reply, strlen(reply));

    return EXIT_SUCCESS;
}

int handler_hello(int client, struct rpc_message * msg) {
    printf("Hello handler called\n");

    char reply[] = "HTTP/1.1 200 OK\r\n\r\nHello World\r\n";
    write(client, reply, strlen(reply));

    return EXIT_SUCCESS;
}

int server(int argc, char ** argv, char ** env) {
    // Configure the server
    uint16_t port = 40000;
    char addr[] = "127.0.0.1";
    char method_hello[] = "hello";
    struct rpc_handler handlers[] = {
        {
            .method = method_hello,
            .func = handler_hello
        },
        NULL
    };
    int comm[2];
    struct rpc_server_config server_config = {
        .addr = addr,
        .port = port,
        .handlers = handlers,
        .not_found = handler_not_found,
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

