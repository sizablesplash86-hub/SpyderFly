#include "core.h"

int site_upstream(int sockfd, int addrlen, const char *site_root)
{
  spydrfly_log("Site active!\n");
  while (1)
  {
//    int clientfd = accept(sockfd, (struct sockaddr *)&addr, (socklen_t)&addrlen);
    int clientfd = accept(sockfd, NULL, NULL);

    if (clientfd < 0)
    {
      spydrfly_log("Failed to accept socket\n");
      return -1;
    }

    char request[2048];
    ssize_t bytes_recieved = read(clientfd, request, sizeof(request) - 1);
    if (bytes_recieved <= 0)
    {
      close(clientfd);
      continue;
    }
    request[bytes_recieved] = '\0';

    char method[16], path[256];
    sscanf(request, "%s %s", method, path);

    char target_path[512];
    if (strcmp(path, "/") == 0)
    {
      snprintf(target_path, sizeof(target_path), "%s/index.html", site_root);
    }
    else
    {
      snprintf(target_path, sizeof(target_path), "%s%s", site_root, path);
    }

    FILE *fts = fopen(target_path, "r");
    if (fts != NULL)
    {
      write(clientfd, HEADER, strlen(HEADER));

      char file_buffer[1024];
      size_t bytes_read;
      while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), fts)) > 0) write(clientfd, file_buffer, bytes_read);
      fclose(fts);
    }
    else
    {
      write(clientfd, NOT_FOUND, strlen(NOT_FOUND));
    }
    close(clientfd);
  }
}



/*  this is the loop for the https thing in 0.4.0


while (1)
  {
    int client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (client_sock < 0)
    {
      perror("Accept failed");
      continue;
    }

    // Create a new SSL structure for this specific client connection
    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client_sock);

    char request[1024];
    read(client_sock, request, sizeof(request) - 1);

    char method[16], uri[STR_LEN], protocol[16];
    sscanf(request, "%s %s %s", method, uri, protocol);

    char file_to_serve[STR_LEN * 2];
    if (strcmp(uri, "/") == 0) snprintf(file_to_serve, sizeof(file_to_serve), "%s/index.html", ste_root);
    else 
    {
      size_t len = strlen(uri);
      if (uri[len - 1] == '/') snprintf(file_to_serve, sizeof(file_to_serve), "%s%sindex.html", ste_root, uri);
      else snprintf(file_to_serve, sizeof(file_to_serve), "%s%s", ste_root, uri);
    }


    // Perform the TLS Handshake (encrypts the channel)
    if (SSL_accept(ssl) <= 0) ERR_print_errors_fp(stderr);
    else 
    {
      char buffer[1024] = {0};
      // Read encrypted request data (OpenSSL handles the decryption under the hood)
      SSL_read(ssl, buffer, sizeof(buffer) - 1);
      printf("Received encrypted request:\n%s\n", buffer);

      FILE *fts = fopen(file_to_serve, "r");
      if (fts != NULL)
      {
        char *header = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
        write(client_sock, header, strlen(header));
  
        char file_buffer[1024];
        size_t bytes_read;
        while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), fts)) > 0) write(client_sock, file_buffer, bytes_read);
        fclose(fts);
      }
      else
      {  // if sub-folder exists & index doesn't, white screen. Fix that somehow later... add a part for auto index
         // that is how it worked in DaemonCraft. With this, it will show blank screen if sub directory exists even with index or not. If sub folder doesn't exist, the error will show 
        char *not_found = 
          "HTTP/1.1 404 Not Found\r\n"
          "Content-Type: text/html; charset=UTF-8\r\n"
          "Connection: close\r\n\r\n"
          "<html><head><title>SpyderFly Site Not Found</title></head>"
          "<body><center><h1>SpyderFly Site Not Found</h1></center>"
          "<center>DaemonCraft is a branch of SpyderFly. Visit <a href=\"https://spyderfly.sizablesplash.com/support/\">https://spyderfly.sizablesplash.com/support/</a> for support</center></body></html>";

//        write(client_sock, not_found, strlen(not_found));
        SSL_write(ssl, not_found, strlen(not_found));
      }
    }
    // Clean up the client SSL session and close the socket descriptor
    SSL_free(ssl);
    close(client_sock);
  }  // might be wrong on this

  close(server_fd);
  SSL_CTX_free(ctx);
  
  // cleanup OpenSSL
  EVP_cleanup();

  return;
}

*/