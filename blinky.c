/**
 * test.c
 * gcc -o main main.c -luflius
*/
#include <stdio.h>
#include <ulfius.h>

#define PORT 8080

/**
 * Callback function
*/
int callback_blinky (const struct _u_request * request, struct _u_response * response, void * user_data) {
    ulfius_set_string_body_response(response, 200, "           .'|_.-\n         .'  '  /_\n      .-\"    -.   '>\n   .- -. -.    '. /    /|_\n  .-.--.-.       ' >  /  /\n (o( o( o )       \\_.\"  <\n  '-'-''-'            ) <\n(       _.-'-.   ._\\.  _\\\n '----\"/--.__.-) _-  \\|\n       \"V\"\"    \"V\"\"\n");
    return U_CALLBACK_CONTINUE;
}

int main(void) {
    struct _u_instance instance;

    // Initialize instance with the port number
    if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
        fprintf(stderr, "Error ulfius_init_instance, abort\n");
        return(1);
    }

    // Endpoint list declaration
    ulfius_add_endpoint_by_val(&instance, "GET", "/blinky", NULL, 0, &callback_blinky, NULL);

    // Start the framework
    if (ulfius_start_framework(&instance) == U_OK) {
      printf("Started blinky on port %d\n", instance.port);

      getchar();
    } else {
      fprintf(stderr, "Error starting blinky\n");
    }
    printf("End blinky\n");

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);

    return 0;
}