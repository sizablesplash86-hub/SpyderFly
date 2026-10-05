// File 0

#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stddef.h>
#include <ifaddrs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <bits/sockaddr.h>

#define FILE_SIZE 1024
#define STR_LEN 256
#define VERSION "0.4.0"

extern char conf[STR_LEN];
extern char conf_port[STR_LEN];
extern char conf_root[STR_LEN];

int socket(int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

typedef struct 
{
  char uri[256];
  char try_files[256];
  // other location-specific directives
} LocationConfig;

typedef struct
{
  int port;
  char server_name[256];
  char root[256];
  LocationConfig locations[32];
  int location_count;
} ServerConfig;

typedef struct
{    
  ServerConfig servers[16];
  int server_count;
} NginxConfig;

pid_t fork(void);  // this might not even be needed

void port(const char *conf);
void root(const char *conf);
void ip_bind(const char *conf_port);
void upstream(int sockfd, const char *conf_port);