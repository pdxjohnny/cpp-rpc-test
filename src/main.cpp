#include "rpc-test.h"

int main (int argc, char ** argv, char ** env) {
    printf("Hello rpc lib %d\n", rpc_test());
    rpc_start_server(NULL);
}

