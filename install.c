// Sources from C Programming A Modern Approach Second Edition by: K. N. King
// Stuff not in the book sources are from Google. If they aren't in the book, chapter and page are not listed.
#include <bits/sockaddr.h>
#include <stdio.h>  // standard I/O, on every page pretty much
#include <stdlib.h>  // standard library functions  chapter 10.2 p.224
#include <string.h>  // string operations  entirety of chaper 13
#include <sys/socket.h>  // imma pretend I know what "socket functions" are
#include <sys/stat.h>  // mkdir command
#include <netinet/in.h>  // IP and stuff
#include <unistd.h>

#define CURRENT_VERSION "v1.0.0"  // started working on it 9/12/26
#define STR_LEN 256  // part of strings defining limit.. I think?? chapter 13.5 p.291
#define name "SpyderFly"

// chapter 7.3 p.135
char web_path[STR_LEN];

int socket(int domain, int type, int protocol);  // The Linux Programming interface chapter 56 p. 1153
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);  // same page
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int main()
{
  printf("\nWelcome to %s %s\nMake sure to follow the GitHub", name, CURRENT_VERSION);
 
  // put this part in a shell script
  // chapter 22.8 p.575
  system("mkdir /etc/spyderfly > /dev/null 2>&1");  // chapter 26.2 p.688
  system("mkdir /etc/spyderfly/index > /dev/null 2>&1");
  system("mkdir /etc/spyderfly/config > /dev/null 2>&1");
  system("mkdir /etc/spyderfly/sites > /dev/null 2>&1");

  char index[50];
  if (system("ls -d /etc/spyderfly/index/index.html > /dev/null 2>&1") != 0)
  {
    snprintf(index, sizeof(index), "/etc/%s/index.html", name);
    FILE *ind = fopen(index, "w");
    fprintf(ind,
      "<!DOCTYPE html>\n"
      "<html>\n"
      "<head>\n"
      "<title>Welcome to %s</title>\n"
      "<style>\n"
      "html { color-scheme: light dark; }\n"
      "body { width: 35em; margin: 0 auto;\n"
      "font-family: Tahoma, Verdana, Arial, sans-serif; }\n"
      "</style>\n"
      "</head>\n"
      "<body>\n"
      "<h1>Welcome to %s!</h1>\n"
      "<p>If you see this page, the web server is successfully installed and working. Further configuration is required. see <a href=\"https://web.sizablesplash.com\">web.sizablesplash.com</a> for guides.</p>\n\n"

      "<p><em>Thank you for using my %s.</em></p>\n"
      "</body>\n"
      "</html>\n",
      name, name, name
    );
    fclose (ind);
  }  //

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("Socket creation failed\n");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8046);
  addr.sin_addr.s_addr = INADDR_ANY;

// socket(AF_INET, SOCK_STREAM, 0);
  int bind_status = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  if (bind_status < 0)
  {
    perror("Failed to bind address\n");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  if (listen(sockfd, 10) < 0)
  {
    perror("Listen failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  printf("\nweb server active! press ctrl+C to stop\n");
  while(1)
  {
    int client_fd = accept(sockfd, NULL, NULL);
    if (client_fd < 0)
    {
      perror("accept failed");
      continue;
    }
    TODO:
    close(client_fd);
  }

//  return 0;
}