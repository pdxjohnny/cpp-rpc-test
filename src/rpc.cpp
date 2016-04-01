#include "rpc.h"

int help(int argc, char ** argv, char ** env) {
    printf("Usage: %s server|client\n", argv[0]);
    return EXIT_SUCCESS;
}

int main (int argc, char ** argv, char ** env) {
    int err;

    // Check if we have enough arguments to run
    if (argc < 2) {
        RPC_FUNC(help);
        return EINVAL;
    }

    // Run the correct function based on first argument
    RPC_FUNC_IF(server);

    return EXIT_SUCCESS;
}

