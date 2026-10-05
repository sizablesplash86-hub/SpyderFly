// File 5
#include "core.h"

void upstream(int sockfd, const char *conf_port)
{
  printf("\nSpyderFly active on port %s!\n", conf_port);
  while(1)
  {
    int client_fd = accept(sockfd, NULL, NULL);
    if (client_fd < 0)
    {
      perror("accept failed");
      continue;
    }

    char request[1024];
    read(client_fd, request, sizeof(request) - 1);

    char method[16], uri[STR_LEN], protocol[16];
    sscanf(request, "%s %s %s", method, uri, protocol);

    char file_to_serve[STR_LEN * 2];
    if (strcmp(uri, "/") == 0) snprintf(file_to_serve, sizeof(file_to_serve), "%s/index.html", conf_root);
    else 
    {
      size_t len = strlen(uri);
      if (uri[len - 1] == '/') snprintf(file_to_serve, sizeof(file_to_serve), "%s%sindex.html", conf_root, uri);
      else snprintf(file_to_serve, sizeof(file_to_serve), "%s%s", conf_root, uri);
    }
    FILE *fts = fopen(file_to_serve, "r");
    if (fts != NULL)
    {
      char *header = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
      write(client_fd, header, strlen(header));

      char file_buffer[1024];
      size_t bytes_read;
      while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), fts)) > 0) write(client_fd, file_buffer, bytes_read);
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

      write(client_fd, not_found, strlen(not_found));
    }
    close(client_fd);
  }  // end of loop
}  // end of main