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

// third party
// https://docs.openssl.org/
#include <openssl/ssl.h>
#include <openssl/err.h>

#define FILE_SIZE 1024
#define STR_LEN 256
#define VERSION "0.4.0"
#define SPYDRFLY_REPO "https://repo.sizablesplash.com/spyderfly/add_later/"

extern char conf[STR_LEN];
extern char conf_port[STR_LEN];
extern char conf_root[STR_LEN];
extern char site_name[STR_LEN];
extern char site_log[FILE_SIZE];
extern char ste_root[STR_LEN];
extern char ste_port[STR_LEN];
extern char ste_domain[STR_LEN];

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

void load_sites(void);  // File 6
void sdrfy_ssl(const char *ste_domain);  // Used, just not assigned a number yet
void port(const char *conf);  // File 2
void root(const char *conf);  // File 3
void site_root(const char *full_path);  // File 8
void site_port(const char *full_path);  // File 7
void site_domain(const char *full_path);  // File 9
void site_bind(const char *ste_port, const char *ste_root);  // File 10
void ip_bind(const char *conf_port);  // File 4
void upstream(int sockfd, const char *conf_port);  // File 5