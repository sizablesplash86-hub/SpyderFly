// File  9
#include "core.h"

void site_bind(const char *ste_port, const char *ste_root)
{
  int port_num = atoi(ste_port);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("Socket creation failed");
    return;
  }

  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port_num);
  addr.sin_addr.s_addr = INADDR_ANY;

  printf("Site parsed its port correctly\n");

  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror("Failed to bind address");
    return;
  }

  if (listen(sockfd, 10) < 0)
  {
    perror("Listen failed");
    return;
  }

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
    if (strcmp(uri, "/") == 0) snprintf(file_to_serve, sizeof(file_to_serve), "%s/index.html", ste_root);
    else 
    {
      size_t len = strlen(uri);
      if (uri[len - 1] == '/') snprintf(file_to_serve, sizeof(file_to_serve), "%s%sindex.html", ste_root, uri);
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
        "<center>Visit <a href=\"https://spyderfly.sizablesplash.com/support/\">https://spyderfly.sizablesplash.com/support/</a> for support</center></body></html>";

      write(client_fd, not_found, strlen(not_found));
    }
    close(client_fd);
  }  // end of loop
}