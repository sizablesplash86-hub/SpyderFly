/*
 * * * * * *
 *  File 6 *
 * * * * * *
 */

#include "core.h"

void upstream(int sockfd)
{
  load_sites();  // File 7
  spydrfly_log("SpyderFly active!");
  printf("SpyderFly active!\n");
  while (1)
  {
    int client_fd = accept(sockfd, NULL , NULL);
    if (client_fd < 0)
    {
      spydrfly_log("Failed to accept socket");
      return;
    }

    char request[1024];
    read(client_fd, request, sizeof(request) - 1);

    spydrfly_log("Client accepted for the main upstream");
    close(client_fd);
  }  // end of loop
}