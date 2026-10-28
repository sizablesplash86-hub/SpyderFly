/*
 * * * * * *
 *  File 0 *
 * * * * * *
 */

/* portable headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* POSIX headers */
#include <unistd.h>
#include <stdarg.h>  // check chapter 3
#include <dirent.h>
#include <getopt.h> // kinda POSIX
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* placeholder */
#include "spydrfly_pltfrm.h"

/* define */
#define SPYDERFLY_VERSION "v0.5.0"
#define NOT_FOUND "HTTP/1.1 404 Not Found\r\n" "Content-Type: text/html; charset=UTF-8\r\n" "Connection: close\r\n\r\n" "<html>\n  <head>\n    <title>SpyderFly Site Not Found</title>\n  </head>\n\n" "  <body>\n    <center><h1>SpyderFly Site Not Found</h1></center>\n" "    <center>Visit <a href=\"https://spyderfly.sizablesplash.com/support/\">https://spyderfly.sizablesplash.com/support/</a> for support</center>\n  </body>\n</html>"
#define HEADER "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n"
#define SPYDERFLY_REPO "https://repo.sizablesplash.com/spyderfly"
#define SITES "/etc/spyderfly/enabled-sites"
#define conf_root "/var/www/html"

/* characters */
extern char conf[128];
extern char pid_conf[1024];
extern char http_port[10];
extern char ssl_port[10];

extern char global_ste_root[256];
extern char global_ste_port[10];
extern char global_ste_domain[128];

/* custom cmds */
void upstream_port(void);
void http_bind(void);
void ssl_bind(void);
int start_spyderfly(void);
int stop_spyderfly(void);
void load_sites(void);
void ste_root(const char *full_path);
void ste_port(const char *full_path);
void ste_domain(const char *full_path);
int site_fork(const char *site_name, const char *site_root, const char *site_port, const char *site_domain);
int http_site_bind(const char *site_root, const char *site_port);
void http_site_upstream(int sockfd, const char *site_root);

void upstream(int sockfd);
void spydrfly_log(const char *format, ...);
void log_timestamp(FILE *log, const char *format, va_list args);