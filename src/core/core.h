/* Portable Headers    Chapters listed from C Programming A Modern Approach Second Edition by K. N. King*/
#include <stdio.h>    // standard library. introduced in Chapter 2 p.10
#include <stdlib.h>   // general utils. introduced chapter 21 p.533
#include <string.h>   // chapter 13 p.277
#include <ctype.h>    // transform characters. Introduced in Chapter 23.5
#include <time.h>     // Chapter 26.3
#include <stdarg.h>   // Technically POSIX, but mentioned in 26.1

#define VERSION "0.6.0"

/* HTML Stuff */
#define HEADER "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n"
#define NOT_FOUND "HTTP/1.1 404 Not Found\r\n" "Content-Type: text/html; charset=UTF-8\r\n" "Connection: close\r\n\r\n" "<html>\n  <head>\n    <title>SpyderFly Site Not Found</title>\n  </head>\n\n" "  <body>\n    <center><h1>SpyderFly Site Not Found</h1></center>\n" "    <hr>\n" "    <center>Visit <a href=\"https://spyderfly.sizablesplash.com/support/\">https://spyderfly.sizablesplash.com/support/</a> for support</center>\n  </body>\n</html>"
#define NO_INDEX "HTTP/1.1 404 Not Found\r\n" "Content-Type: text/html; charset=UTF-8\r\n" "Connection: close\r\n\r\n" "<html>\n  <head>\n    <title>SpyderFly Forbidden</title>\n  </head>\n\n" "  <body>\n    <center><h1>Index Not found</h1></center>\n" "    <hr>\n" "    <center>Visit <a href=\"https://spyderfly.sizablesplash.com\">https://spyderfly.sizablesplash.com</a>for support and info</center>\n  </body>\n</html>"