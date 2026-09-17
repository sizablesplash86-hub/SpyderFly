#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>  // standard I/O, on every page pretty much
#include <stdlib.h>  // standard library functions  chapter 10.2 p.224
#include <string.h>  // string operations  entirety of chaper 13
#include <unistd.h>  // provides needed stuff for the OS
#include <dirent.h>  // POSIX for directories on UNIX based OS
#include <stddef.h>
#include <sys/socket.h>  // imma pretend I know what "socket functions" are
#include <sys/stat.h>  // mkdir command
#include <netinet/in.h>  // IP and stuff
#include <bits/sockaddr.h>

#define STR_LEN 256
#define CURRENT_VERSION "beta_2.0"

typedef struct
{
  char domain[STR_LEN];
  char root[STR_LEN];
  int port;
} 
SiteConfig;

extern char example[STR_LEN];

void ex_ample(void);
void load_sites(const char *filepath, SiteConfig *config);

int socket(int domain, int type, int protocol);  // The Linux Programming interface chapter 56 p. 1153
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);  // same page
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#endif