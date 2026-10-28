/* K. N. King's C Programming: A Modern Approach Second Edition */
#include <stdio.h>    // standard library. introduced in Chapter 2 p.10
#include <stdlib.h>   // general utils. introduced chapter 21 p.533
#include <string.h>   // chapter 13 p.277
#include <stddef.h>   // standard definitions like size_t and NULL chapter 21.4 p.535

/* OS headers */
#include "os.h"

#define VERSION "0.5.1"

/* HTML Stuff */
#define HEADER "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n"
#define NOT_FOUND "HTTP/1.1 404 Not Found\r\n" "Content-Type: text/html; charset=UTF-8\r\n" "Connection: close\r\n\r\n" "<html>\n  <head>\n    <title>SpyderFly Site Not Found</title>\n  </head>\n\n" "  <body>\n    <center><h1>SpyderFly Site Not Found</h1></center>\n" "    <hr>\n" "    <center>Visit <a href=\"https://spyderfly.sizablesplash.com/support/\">https://spyderfly.sizablesplash.com/support/</a> for support</center>\n  </body>\n</html>"
#define NO_INDEX "HTTP/1.1 404 Not Found\r\n" "Content-Type: text/html; charset=UTF-8\r\n" "Connection: close\r\n\r\n" "<html>\n  <head>\n    <title>SpyderFly Forbidden</title>\n  </head>\n\n" "  <body>\n    <center><h1>Index Not found</h1></center>\n" "    <hr>\n" "    <center>Visit <a href=\"https://spyderfly.sizablesplash.com\">https://spyderfly.sizablesplash.com</a>for support and info</center>\n  </body>\n</html>"

int start_spyderfly(void);
int load_sites(void);
int ste_conf(const char *full_path, const char *site_name);
int site_bind(const char *site_port, const char *site_root, const char *site_domain, const char *dm_fullchain, const char *dm_privkey, const char *dm_trusted_cert);
int site_upstream(int sockfd, int addrlen, const char *site_root);

void spydrfly_log(const char *format, ...);