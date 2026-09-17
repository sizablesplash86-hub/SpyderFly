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
#include "config.h"

  //project started 9/12/26 and this version started 9/15/26

int main()
{
  printf("\nWelcome to SpyderFly %s!\n\nRead the docs at \033[34mhttps://spyderfly.sizablesplash.com\033[0m\n", CURRENT_VERSION);

  // https://gemini.google.com/app/2afd71c0a629b5ff
  // https://gemini.google.com/app/e9cbc5fc7bd8982d
  // https://claude.ai/chat/71e94e7d-da19-411d-93e1-44243e24ea52

  // read through /mnt/code-projects/packages/web-server/nginx-examples/nginx/source-code/src/core/ngx_conf_file.c  to understand how it handles the config
}