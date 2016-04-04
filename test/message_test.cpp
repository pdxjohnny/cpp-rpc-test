#include "rpc-test.h"

const char get_request[] =
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

int test_message_malloc_free_buffer() {
    char request_1[] =
        "GET /somemethod HTTP/1.1\r\n"
        "Host: 127.0.0.1:45311\r\n";
    char request_2[] =
        "Connection: keep-alive\r\n"
        "Accept: text/html,application/xhtml+x�ml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n";
    char request_3[] =
        "Upgrade-Insecure-Requests: 1\r\n"
        "User-Agent: Mozilla/5.0� (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.110 Safari/537.36\r\n";
    char request_4[] =
        "DNT:� 1\r\n"
        "Accept-Encoding: gzip, deflate, sdch\r\n"
        "Accept-Language: en-US,en;q=0.8\r\n"
        "\r\n";

    // Create the message to parse into
    struct rpc_message msg;
    rpc_message_init(&msg);

    // Try parsing the request
    rpc_message_parse(&msg, request_1, strlen(request_1));
    rpc_message_parse(&msg, request_2, strlen(request_2));
    rpc_message_parse(&msg, request_3, strlen(request_3));
    rpc_message_parse(&msg, request_4, strlen(request_4));

    // Make sure that the message was parsed correctly
    RPC_TEST_EQ(msg.protocol, RPC_PROTOCOL_HTTP);
    RPC_TEST_STR_EQ(msg.method, "somemethod");

    // Free the message
    rpc_message_free(&msg);

    return EXIT_SUCCESS;
}

int test_message_parse() {
    // Create the message to parse into
    struct rpc_message msg;
    rpc_message_init(&msg);

    // Try parsing the request
    rpc_message_parse(&msg, get_request, strlen(get_request));

    // Make sure that the message was parsed correctly
    RPC_TEST_EQ(msg.protocol, RPC_PROTOCOL_HTTP);
    RPC_TEST_STR_EQ(msg.method, "somemethod");

    // Free the message
    rpc_message_free(&msg);

    return EXIT_SUCCESS;
}

int test_rpc_message_parse_http_path() {
    int err;

    // Create the message to parse into
    struct rpc_message msg;
    rpc_message_init(&msg);

    // Headers on the stack for simplicity
    char headers[] = "GET /path HTTP/1.1\r\n";
    msg.headers = headers;
    msg.length_headers = strlen(msg.headers);

    // Try parsing the request
    err = rpc_message_parse_http_path(&msg);
    if (err == -1) {
        return err;
    }

    // Make sure that the message was parsed correctly
    RPC_TEST_STR_EQ(msg.method, "path");

    // So that we dont try to free the headers
    msg.headers = NULL;

    // Free the message
    rpc_message_free(&msg);

    return EXIT_SUCCESS;
}

