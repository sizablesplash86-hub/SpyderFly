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

void handle_client_request(int client_fd, SiteConfig *site)
{
  char file_to_serve[STR_LEN];
  // It dynamically builds the path using whatever root the config specified!
  snprintf(file_to_serve, sizeof(file_to_serve), "%s/index.html", site->root);

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
    char *not_found = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nSite Index Not Found";
    write(client_fd, not_found, strlen(not_found));
  }
}

int main()
{
  handle_client_request(client_fd, &active_site);
}
