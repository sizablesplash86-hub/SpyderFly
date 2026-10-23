/*
 * * * * * *
 * File 12 *
 * * * * * *
 */

 #include "core.h"

int http_site_bind(const char *site_root, const char *site_port)
{
  int port_num = atoi(site_port);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
  {
    spydrfly_log("Failed to create socket");
    return 1;
  }

  spydrfly_log("Created site socket!");

  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port_num);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    spydrfly_log("Failed to bind socket");
    return 1;
  }

  if (listen(sockfd, 10) < 0)
  {
    spydrfly_log("Failed to listen on site's port");
    return 1;
  }

  http_site_upstream(sockfd, site_root);
  
  close(sockfd);
  return 0;
}