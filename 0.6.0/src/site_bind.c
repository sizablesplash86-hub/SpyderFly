#include "core.h"

SSL_CTX *create_contex()
{
  const SSL_METHOD *method;
  SSL_CTX *ctx;

  method = TLS_server_method();
  ctx = SSL_CTX_new(method);
  if (!ctx)
  {
    spydrfly_log("Unable to create SSL socket\n");
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }
  return ctx;
}

int site_bind(const char *site_port, const char *site_root, const char *site_domain, const char *dm_fullchain, const char *dm_privkey, const char *dm_trusted_cert)
{
  int port_num = atoi(site_port);
  int opt = 1;
  struct sockaddr_in addr;
  int addrlen = sizeof(addr);  // added for SSL
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // Initialize the OpenSSL Library
  SSL_load_error_strings();
  OpenSSL_add_ssl_algorithms();
  SSL_CTX *ctx = create_contex();
  // obviously added for SSL

  // Adds the fullchain
  if (strcmp(dm_fullchain, "") != 0)
  {
    if (SSL_CTX_use_certificate_file(ctx, dm_fullchain, SSL_FILETYPE_PEM) <= 0)
    {
      ERR_print_errors_fp(stderr);
      exit(EXIT_FAILURE);
    }
  }
  spydrfly_log("Passed the fullchain stuff\n");

  // Adds the privkey
  if (strcmp(dm_privkey, "") != 0)
  {
    if (SSL_CTX_use_PrivateKey_file(ctx, dm_privkey, SSL_FILETYPE_PEM) <= 0)
    {
      ERR_print_errors_fp(stderr);
      exit(EXIT_FAILURE);
    }
  }
  spydrfly_log("Passed the privkey stuff\n");
  // These two if statements were also obviously added for SSL


  // Creates socket
  if (sockfd < 0)
  {
    spydrfly_log("Failed to create socket\n");
    return 1;
  }

  spydrfly_log("Created socket\n");

  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port_num);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    spydrfly_log("Failed to bind port %s\n", port_num);
    return 1;
  }

  spydrfly_log("Socket binded\n");

  if (listen(sockfd, 10) < 0)
  {
    spydrfly_log("Failed to listen on port %s\n", site_port);
    return 1;
  }

  spydrfly_log("Listening on port %s\n", site_port);

  site_upstream(sockfd, addrlen, site_root);

  close(sockfd);
  return 0;
}