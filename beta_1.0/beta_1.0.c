// abandoned     see beta 2.0

// Sources from C Programming A Modern Approach Second Edition by: K. N. King
// Stuff not in the book sources are from Google. If they aren't in the book, chapter and page are not listed.
#include <bits/sockaddr.h>
#include <stddef.h>
#include <stdio.h>  // standard I/O, on every page pretty much
#include <stdlib.h>  // standard library functions  chapter 10.2 p.224
#include <string.h>  // string operations  entirety of chaper 13
#include <sys/socket.h>  // imma pretend I know what "socket functions" are
#include <sys/stat.h>  // mkdir command
#include <netinet/in.h>  // IP and stuff
#include <unistd.h>  // provides needed stuff for the OS
#include <dirent.h>  // POSIX for directories on UNIX based OS

#define CURRENT_VERSION " beta v1.0"  // started working on it 9/12/26
#define STR_LEN 256  // part of strings defining limit.. I think?? chapter 13.5 p.291
#define name "spyderfly"

// chapter 7.3 p.135
char web_path[STR_LEN];

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

void load_sites(const char *filepath, SiteConfig *config)
{
 config->port = 0;
  snprintf(config->root, sizeof(config->root), "/etc/spyderfly/index");
  snprintf(config->domain, sizeof(config->domain), "localhost");

  FILE *idk = fopen(filepath, "r");
  if (idk == NULL)
  {
    perror("Failed to open file");
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), idk) != NULL)
  {
    line[strcspn(line, ";\r\n")] = 0;

    int parsed_port;
    if (sscanf(line, "listen %d", &parsed_port) == 1) config->port = parsed_port;

    char parsed_root[STR_LEN];
    if (sscanf(line, "root %s", parsed_root) == 1) snprintf(config->root, sizeof(config->root), "%s", parsed_root);

    char parsed_name[STR_LEN];
    if (sscanf(line, "server_name %s", parsed_name) == 1) snprintf(config->domain, sizeof(config->domain), "%s", parsed_name);
  }
  fclose(idk);

  if (config->port == 0) fprintf(stderr, "Error: Config file %s is missing a 'listen <port>' directive.\n", filepath);

  printf("Successfully parsed config: Port=%d, Root=%s, Domain=%s\n", config->port, config->root, config->domain);
}

int main()
{
  printf("\nWelcome to %s %s\nMake sure to follow the GitHub", name, CURRENT_VERSION);

  SiteConfig loaded_sites[10];
  int site_count = 0;

  DIR *dir = opendir("/etc/spyderfly/sites");
  if (dir != NULL)
  {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && site_count < 10)
    {
      if (entry->d_name[0] == '.') continue;

      char site_path[STR_LEN];
      snprintf(site_path, sizeof(site_path), "/etc/spyderfly/sites/%s", entry->d_name);

      printf("Loading %s ...", entry->d_name);

      load_sites(site_path, &loaded_sites[site_count]);
      site_count++;
    }
    closedir(dir);
  }
  else perror("Failed to load sites");

  int target_port = 0;
  for (int i = 0; i < site_count; i++)
  {
    if (loaded_sites[i].port > 0)
    {
      target_port = loaded_sites[i].port;
      break;
    }
  }

  if (target_port == 0)
  {
    fprintf(stderr, "Fatal: No valid ports found in any configuration files.\n");
    exit(EXIT_FAILURE);
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
  addr.sin_port = htons(target_port);
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
    int client_fd = accept(sockfd, NULL, NULL);
    if (client_fd < 0)
    {
      perror("accept failed");
      continue;
    }

    char request[1024];
    read(client_fd, request, sizeof(request) - 1);
    char *active_root = "/etc/spyderfly/index/";
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
    //
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
  } // loop ends here
} // main ends here