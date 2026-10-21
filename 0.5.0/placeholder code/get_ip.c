// This gets the code to log the IP of someone who visits a SpyderFly site, not ready to impliment

#include "../src/core.h"

void handle_incoming_connections(int server_sockfd)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_socket = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket < 0)
    {
        perror("Accept failed");
        return;
    }

    // Buffer to hold the human-readable IP address string
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
    
    // Extract the client port
    int client_port = ntohs(client_addr.sin_port);

    // Pass it directly to your custom logger
    spydrfly_log("Connection accepted from IP: %s, Port: %d", client_ip, client_port);

    // Proceed with handling the request...
    close(client_socket);
}