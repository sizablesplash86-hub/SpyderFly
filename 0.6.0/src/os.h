/* Michael Kerrisk's The Linux Programming Interface */
#include <unistd.h>     // system calls. introduced in Chapter 3
#include <ctype.h>      // transform characters. Introduced in Chapter 4
#include <dirent.h>     // directory operations. introduced in Chapter 18
#include <ifaddrs.h>    // network interface addresses. introduced in Chapter 59
#include <sys/stat.h>   // file metadata and permissions. introduced in Chapter 4 / Chapter 15
#include <sys/types.h>  // system types like pid_t and size_t. introduced in Chapter 3
#include <arpa/inet.h>  // IPv4/IPv6 address manipulation. introduced in Chapter 59
#include <sys/socket.h> // core socket operations. introduced in Chapter 56
#include <netinet/in.h> // internet domain addresses. introduced in Chapter 59

/* OpenSSL library headers    https://openssl.org */
#include <openssl/ssl.h>  // core SSL/TLS context and connection handlers (libssl)
#include <openssl/err.h>  // crypto and SSL error reporting functions (libcrypto)


#define conf_file "/etc/nginx/config/spyderfly.conf"
#define sites_dir "/etc/spyderfly/enabled-sites"
#define logs "/etc/spyderfly/log"
#define pid_file "/run/spyderfly.pid"