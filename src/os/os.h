/* POSIX Headers    Chapters from The Linux Programming Interface by Michael Kerrisk */
#include <unistd.h>     // system calls. introduced in Chapter 3
#include <dirent.h>     // directory operations. introduced in Chapter 18
#include <ifaddrs.h>    // network interface addresses. introduced in Chapter 59
#include <sys/stat.h>   // file metadata and permissions. introduced in Chapter 4 / Chapter 15
#include <sys/types.h>  // system types like pid_t and size_t. introduced in Chapter 3
#include <arpa/inet.h>  // IPv4/IPv6 address manipulation. introduced in Chapter 59
#include <sys/socket.h> // core socket operations. introduced in Chapter 56
#include <netinet/in.h> // internet domain addresses. introduced in Chapter 59

/* Libraries NGINX uses    I just need to put this somewhere I'll check
 *
 * zlib
 * perl
 * pcre
 * OpenSSL
 * libxslt
 * libgd
 * libatomic
 * google-perftools
 * geoip
 *
 */

/* POSIX define */
#define conf_file "/etc/nginx/config/spyderfly.conf"
#define sites_dir "/etc/spyderfly/enabled-sites"
#define spydrfly_logs "/etc/spyderfly/log"
#define pid_file "/run/spyderfly.pid"