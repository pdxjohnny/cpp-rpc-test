#include "rpc-test.h"

int test_message_parse() {
    char request[] =
        "GET /somemethod HTTP/1.1\r\n"
        "Host: 127.0.0.1:45311\r\n"
        "Connection: keep-alive\r\n"
        "Accept: text/html,application/xhtml+x�ml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "User-Agent: Mozilla/5.0� (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.110 Safari/537.36\r\n"
        "DNT:� 1\r\n"
        "Accept-Encoding: gzip, deflate, sdch\r\n"
        "Accept-Language: en-US,en;q=0.8\r\n"
        "\r\n";

    // Create the message to parse into
    struct rpc_message msg;
    rpc_message_init(&msg);

    // Try parsing the request
    rpc_message_parse(&msg, request, strlen(request));

    // Make sure that the message was parsed correctly
    RPC_TEST_EQ(msg.protocol, RPC_PROTOCOL_HTTP);
    RPC_TEST_STR_EQ(msg.method, "somemethod");

    // Free the message
    rpc_message_free(&msg);

    return EXIT_SUCCESS;
}

