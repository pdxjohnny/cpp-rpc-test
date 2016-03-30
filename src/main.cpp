#include "rpc-test.h"

int main (int argc, char ** argv, char ** env) {
    printf("Hello rpc lib %d\n", rpc_test());

    struct rpc_handler handlers[] = {
        NULL
    };
    rpc_start_server(handlers);
}

