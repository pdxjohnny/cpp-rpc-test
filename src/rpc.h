#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <librpc.h>

#define RPC_FUNC(test_name) \
({\
    err = test_name(argc, argv, env);\
    if (err == -1) {\
        printf(#test_name " exited with status %d", errno);\
    }\
})

#define RPC_FUNC_IF(test_name) \
({\
    if (0 == strcmp(#test_name, argv[1])) {\
        RPC_FUNC(test_name);\
    }\
})


// Server
int server(int argc, char ** argv, char ** env);

// Client
int client(int argc, char ** argv, char ** env);

