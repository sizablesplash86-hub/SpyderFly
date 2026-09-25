/* * * * * * * * * * * * * * * *
 *  SpyderFly Upstream Handler *
 * * * * * * * * * * * * * * * */

#include <stdio.h>  // standard I/O, on every page pretty much
#include <stdlib.h>  // standard library functions  chapter 10.2 p.224
#include <string.h>  // string operations  entirety of chaper 13
#include <unistd.h>  // provides needed stuff for the OS
#include <dirent.h>  // POSIX for directories on UNIX based OS
#include <stddef.h>
#include <sys/socket.h>  // imma pretend I know what "socket functions" are
#include <netinet/in.h>  // IP and stuff
#include <bits/sockaddr.h>

#define CURRENT_VERSION "v0.3.0"  // started working on it 9/12/26
#define FILE_SIZE 1024
#define STR_LEN 256  // part of strings defining limit.. I think?? chapter 13.5 p.291

// chapter 7.3 p.135
char web_path[STR_LEN];
char conf[STR_LEN];
char conf_port[STR_LEN];

int socket(int domain, int type, int protocol);  // The Linux Programming interface chapter 56 p. 1153
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);  // same page
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

typedef struct
{
  char domain[STR_LEN];
  char root[STR_LEN];
  int port;
} 
SiteConfig;

int main()
{
  printf("\nWelcome to the SpyderFly web server %s!\n\n", CURRENT_VERSION);

  // the upstream config
  snprintf(conf, sizeof(conf), "/etc/spyderfly/config/spyderfly.conf");
  FILE *fp = fopen(conf, "r");
  if (fp == NULL) perror("Could not find the main config file\n");
  char line[FILE_SIZE];
  int found = 0;
  while (fgets(line, sizeof(line), fp) != NULL)
  {
    if (strncmp(line, "listen *", 6) == 0)
    {
      found = 1;
      break;
    }
  }
  fclose(fp);

  char *port = line + 6;
  if (found)
  {
    line[strcspn(line, "\r\n;")] =0;
    
    while (*port == ' ' || *port == '\t') port++;
    printf("Port %s found!\n\n", port);
  }

  else 
  {
    printf("\nPort not found\n\n");
    return 0;
  }

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("Socket creation failed\n");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
  {
    perror("setsockopt failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  int port_num = atoi(port);
  addr.sin_port = htons(port_num);
  addr.sin_addr.s_addr = INADDR_ANY;

  socket(AF_INET, SOCK_STREAM, 0);
  int bind_status = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  if (bind_status < 0)
  {
    perror("Failed to bind address\n");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  if (listen(sockfd, 10) < 0)
  {
    perror("Listen failed\n");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  printf("\nWeb server active! press ctrl+C to stop\n");
  while(1)
  {
    // add this crap later
    int client_fd = accept(sockfd, NULL, NULL);
    if (client_fd < 0)
    {
      perror("accept failed");
      continue;
    }

    char request[1024];
    read(client_fd, request, sizeof(request) - 1);
    char *active_root = "/etc/spyderfly/index/";

/*
    if (site_count > 0) active_root = loaded_sites[0].root;

    char *host_line = strstr(request, "Host: ");
    if (host_line != NULL)
    {
      char requested_host[STR_LEN];
      if (sscanf(host_line, "Host: %s", requested_host) == 1)
      {
        char *port_seperator = strchr(requested_host, ':');
        if (port_seperator != NULL) *port_seperator = '\0';

        for (int i = 0; i < site_count; i++)
        {
          if (strstr(loaded_sites[i].root, "index") != NULL)
          {
            target_port = loaded_sites[i].port;
            break;
          }
        }
      }
    }
*/

    char file_to_serve[STR_LEN];
    snprintf(file_to_serve, sizeof(file_to_serve), "%s/index.html", active_root);

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
    {
      char *not_found = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Index Not Found";
      write(client_fd, not_found, strlen(not_found));
    }
    close(client_fd);
  }
    
}