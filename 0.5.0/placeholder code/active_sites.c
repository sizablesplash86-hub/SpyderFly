// This is for to see how many active SpyderFly servers there are

#include "../src/core.h"

void handle_status_api(int client_socket) {
    char response_body[128];
    int active_count = get_active_server_count(); // Your tracking logic here
    
    int len = snprintf(response_body, sizeof(response_body), 
                       "{\"active_servers\": %d}", active_count);

    char header[512];
    int header_len = snprintf(header, sizeof(header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n\r\n", len);

    write(client_socket, header, header_len);
    write(client_socket, response_body, len);
}