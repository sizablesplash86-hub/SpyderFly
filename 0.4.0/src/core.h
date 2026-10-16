// File 0
#define CORE_H

// https://gemini.google.com/app/2afd71c0a629b5ff


/* K. N. King's C Programming: A Modern Approach Second Edition */
#include <stdio.h>    // standard library. introduced in Chapter 2 p.10
#include <stdlib.h>   // general utils. introduced chapter 21 p.533
#include <string.h>   // chapter 13 p.277
#include <stddef.h>   // standard definitions like size_t and NULL chapter 21.4 p.535


/* Michael Kerrisk's The Linux Programming Interface */
#include <unistd.h>     // system calls. introduced in Chapter 3
#include <dirent.h>     // directory operations. introduced in Chapter 18
#include <ifaddrs.h>    // network interface addresses. introduced in Chapter 59
#include <sys/stat.h>   // file metadata and permissions. introduced in Chapter 4 / Chapter 15
#include <sys/types.h>  // system types like pid_t and size_t. introduced in Chapter 3
#include <arpa/inet.h>  // IPv4/IPv6 address manipulation. introduced in Chapter 59
#include <sys/socket.h> // core socket operations. introduced in Chapter 56
#include <netinet/in.h> // internet domain addresses. introduced in Chapter 59

#include <bits/sockaddr.h>  // Internal glibc header. Automatically pulled in by <sys/socket.h>; not needed.


/* OpenSSL library headers    https://openssl.org */
#include <openssl/ssl.h>  // core SSL/TLS context and connection handlers (libssl)
#include <openssl/err.h>  // crypto and SSL error reporting functions (libcrypto)



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
extern char minecraft[STR_LEN];

// actually use these. TLPI chapter 56
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
void web_mc(const char *full_path);  // undefined file
void mc_check(const char *conf);