/*
 * * * * * *
 * File 13 *
 * * * * * *
 */

#include "core.h"

void http_site_upstream(int sockfd, const char *site_root)
{
  spydrfly_log("Starting HTTP site upstream");

  while (1)
  {
    int clientfd = accept(sockfd, NULL, NULL);

    if (clientfd < 0)
    {
      spydrfly_log("Failed to accept site socket");
      continue;
    }
    
    char file_to_serve[512];
    snprintf(file_to_serve, sizeof(file_to_serve), "%s/index.html", site_root);

    FILE *fts = fopen(file_to_serve, "r");
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
  }  // end of loop
}