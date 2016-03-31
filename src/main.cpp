#include "rpc-test.h"

int main (int argc, char ** argv, char ** env) {
    int err;

    printf("Hello rpc lib %d\n", rpc_test());

    // Create a pipe so we can tell the server when to stop running
    // Read end of the pipe is index 0 write end is index 1
    int pipe_fd[2];
    err = pipe(pipe_fd);
    if (err == -1) {
        printf("Error creating pipe %d\n", errno);
    }

    // Configure the server
    char addr[] = "127.0.0.1";
    struct rpc_handler handlers[] = {
        NULL
    };
    struct rpc_server_config server_config = {
        .addr = addr,
        .port = 0,
        .handlers = handlers,
        .comm = pipe_fd
    };

    // Configure the client
    struct rpc_client_config client_config = {
        .addr = addr,
        .port = 0,
    };

    // Store the server exit status in this variable
    int server_exit;

    // Store the client exit status in this variable
    int client_exit;

    // The server will send back the port number through comm
    char buffer[12];
    int port;

    // Fork so that the server is running in the background
    switch (fork()) {
    case -1:
        // Error
        printf("Error while forking %d\n", errno);
        return 1;

    case 0:
        // Clild
        // Start the server
        server_exit = rpc_start_server(&server_config);
        // Report the exit status and exit
        printf("Server (pid %d) exited with status %d\n", getpid(), server_exit);
        return EXIT_SUCCESS;

    default:
        // Parent
        // Read the port from the pipe
        read(pipe_fd[RPC_COMM_READ], buffer, 12);
        // Convert the string to a port number
        port = atoi(buffer);
        // Set the client port to be what the server reports its port is
        client_config.port = port;
        // Make a request
        printf("Client will connect to port %d\n", client_config.port);
        // Sleep a bit to allow server to start
        sleep(2);
        // Make the request
        client_exit = rpc_client(&client_config);
        // Report the exit status and exit
        printf("Client (pid %d) exited with status %d\n", getpid(), client_exit);
        // Send some data trough, the server will stop once we do
        char stop_msg[] = "stop";
        write(pipe_fd[RPC_COMM_WRITE], stop_msg, strlen(stop_msg));
        // Data was send so close the write end of the pipe
        close(pipe_fd[RPC_COMM_WRITE]);
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

