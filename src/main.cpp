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
    struct rpc_server_config config = {
        .addr = addr,
        .port = 0,
        .handlers = handlers,
        .comm = pipe_fd[0],
    };

    // Store the server exit status in this variable
    int server_exit;

    // Fork so that the server is running in the background
    switch (fork()) {
    case -1:
        // Error
        printf("Error while forking %d\n", errno);
        return 1;

    case 0:
        // Clild
        // Close the write end of the pipe, the server only reads
        close(pipe_fd[1]);
        // Start the server
        server_exit = rpc_start_server(&config);
        // Report the exit status and exit
        printf("Server (pid %d) exited with status %d\n", getpid(), server_exit);
        return EXIT_SUCCESS;

    default:
        // Parent
        // Close the read end of the pipe, the parent only writes
        close(pipe_fd[0]);
        // Make a request (for now just sleep a bit)
        sleep(1);
        // Send some data trough, the server will stop once we do
        char stop_msg[] = "stop";
        write(pipe_fd[1], stop_msg, strlen(stop_msg));
        // Data was send so close the write end of the pipe
        close(pipe_fd[1]);
        // Report the exit status and exit
        printf("Client (pid %d) exited with status 0\n", getpid());
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

