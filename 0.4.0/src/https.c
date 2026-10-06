/* * * * * * * * * * * * * * * * * * * *
 * This is new and idk where to set it *
 * * * * * * * * * * * * * * * * * * * */

#include "core.h"

// Create the SSL Context structure
SSL_CTX *create_context()
{
  const SSL_METHOD *method;
  SSL_CTX *ctx;

  method = TLS_server_method(); // Create a modern TLS server method
  ctx = SSL_CTX_new(method);
  if (!ctx)
  {
    perror("Unable to create SSL context");
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }
  return ctx;
}

// main
void sdrfy_ssl(const char *ste_domain)
{
  char domain_path[STR_LEN];
  char fullchain[STR_LEN];
  char privkey[STR_LEN];
  snprintf(domain_path, sizeof(domain_path), "/etc/letsencrypt/live/%s", ste_domain);
  snprintf(fullchain, sizeof(fullchain), "%s/fullchain.pem", domain_path);
  snprintf(privkey, sizeof(privkey), "%s/privkey.pem", domain_path);
  
  int server_fd;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);

  // initialize OpenSSL library
  SSL_load_error_strings();
  OpenSSL_add_ssl_algorithms();

  SSL_CTX *ctx = create_context();

  // Load the certificate and private key into the context
  // Use the real Let's Encrypt paths
  if (SSL_CTX_use_certificate_file(ctx, fullchain, SSL_FILETYPE_PEM) <= 0)
  {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }

  if (SSL_CTX_use_PrivateKey_file(ctx, privkey, SSL_FILETYPE_PEM) <= 0)
  {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }


  // 1. Create standard TCP socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0)
  {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(443);  // wonder if it can be 80/443

  // 2. Bind and Listen
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 10) < 0)
  {
    perror("Listen failed");
    exit(EXIT_FAILURE);
  }

  printf("\nNative HTTPS server active!\n");

  // 3. Main Server Loop
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

    // Perform the TLS Handshake (encrypts the channel)
    if (SSL_accept(ssl) <= 0) ERR_print_errors_fp(stderr);
    else 
    {
      char buffer[1024] = {0};
      // Read encrypted request data (OpenSSL handles the decryption under the hood)
      SSL_read(ssl, buffer, sizeof(buffer) - 1);
      printf("Received encrypted request:\n%s\n", buffer);

      // Send back a secure HTTPS 200 OK response
      const char *response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<h1>Hello from native C HTTPS!</h1>"
        "<p>Encrypted via OpenSSL directly inside SpyderFly's architecture.</p>";

      SSL_write(ssl, response, strlen(response));
    }

    // Clean up the client SSL session and close the socket descriptor
    SSL_free(ssl);
    close(client_sock);
  }

  close(server_fd);
  SSL_CTX_free(ctx);
  
  // cleanup OpenSSL
  EVP_cleanup();

  return;
}