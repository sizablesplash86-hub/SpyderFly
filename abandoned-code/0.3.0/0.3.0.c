/* * * * * * * * * * * * * * * *
 * SpyderFly Upstream Handler  *
 * * * * * * * * * * * * * * * */

// abandoned again for 0.4.0

// check reference-code/fork.c

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
  FILE *pt = fopen(conf, "r");
  if (pt == NULL) perror("Could not find the main config file\n");
  char line[FILE_SIZE];
  int found = 0;
  while (fgets(line, sizeof(line), pt) != NULL)
  {
    if (strncmp(line, "listen *", 6) == 0)
    {
      found = 1;
      break;
    }
  }
  fclose(pt);

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

  /*
  // finds the root; fix this later

  FILE *rt = fopen(conf, "r");
  if (rt == NULL) perror("Could not find the main config file\n");
  
  char tdb[FILE_SIZE];
  int idk = 0;

  while (fgets(tdb, sizeof(tdb), rt) != NULL)
  {
    if (strncmp(tdb, "root *", 4) == 0)
    {
      idk = 1;
      break;
    }
  }
  fclose(rt);

  char *root = tdb + 4;
  if (idk)
  {
    tdb[strcspn(tdb, "/\r\n;")] =0;
    
    while (*root == ' ' || *root == '\t') root++;
    printf("Root %s found!\n\n", root);
  }

  else 
  {
    printf("\nRoot not found\n\n");
    return 0;
  }    */
  // end of new code

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

  printf("\nSpyderFly Web server upstream active! press ctrl+C to stop\n");
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
    char *root = "/etc/spyderfly/index/";  // change this to import from the conf file. Code is there, just figure it out

    char method[16], uri[STR_LEN], protocol[16];
    sscanf(request, "%s %s %s", method, uri, protocol);
    char file_to_serve[STR_LEN * 2];

    if (strcmp(uri, "/") == 0) snprintf(file_to_serve, sizeof(file_to_serve), "%s/index.html", root);
    else 
    {
      size_t len = strlen(uri);
      if (uri[len - 1] == '/') snprintf(file_to_serve, sizeof(file_to_serve), "%s%sindex.html", root, uri);
      else snprintf(file_to_serve, sizeof(file_to_serve), "%s%s", root, uri);
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
    {
      // if sub-folder exists & index doesn't, white screen. Fix that somehow later...
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
  }        // end of loop
}  // end of main