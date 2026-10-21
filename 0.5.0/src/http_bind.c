/*
 * * * * * *
 *  File 5 *
 * * * * * *
 */

#include "core.h"

void http_bind(void)
{
  int port_num = atoi(http_port);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
  {
    spydrfly_log("Failed to create socket");
    return;
  }

  spydrfly_log("created socket");

  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port_num);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    spydrfly_log("Failed to bind socket. May already be in use.");
    return;
  }

  spydrfly_log("Socket binded successfully");

  spydrfly_log("Running upstream...");
  upstream(sockfd);  // File 6

  spydrfly_log("Closing socket...");
  close(sockfd);
  return;
}