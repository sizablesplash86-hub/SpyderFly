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

/* define */
#define SPYDERFLY_VERSION "v0.5.0"
#define NOT_FOUND "HTTP/1.1 404 Not Found\r\n" "Content-Type: text/html; charset=UTF-8\r\n" "Connection: close\r\n\r\n" "<html>\n  <head>\n    <title>SpyderFly Site Not Found</title>\n  </head>\n\n" "  <body>\n    <center><h1>SpyderFly Site Not Found</h1></center>\n" "    <center>Visit <a href=\"https://spyderfly.sizablesplash.com/support/\">https://spyderfly.sizablesplash.com/support/</a> for support</center>\n  </body>\n</html>"
#define SITES "/etc/spyderfly/enabled-sites"

/* characters */
extern char conf[128];
extern char http_port[10];
extern char ssl_port[10];

/* custom cmds */
void upstream_port(void);
void http_bind(void);
void ssl_bind(void);
void load_sites(void);
void upstream(int sockfd);
void spydrfly_log(const char *format, ...);
void log_timestamp(FILE *log, const char *format, va_list args);

/* int cmds */
int start_spyderfly(void);