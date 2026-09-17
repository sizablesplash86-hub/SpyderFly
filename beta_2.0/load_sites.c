#include <stdio.h>  // standard I/O, on every page pretty much
#include <string.h>  // string operations  entirety of chaper 13
#include <unistd.h>  // provides needed stuff for the OS
#include <dirent.h>  // POSIX for directories on UNIX based OS
#include <stddef.h>
#include <sys/socket.h>  // imma pretend I know what "socket functions" are
#include <sys/stat.h>  // mkdir command
#include <netinet/in.h>  // IP and stuff
#include <bits/sockaddr.h>
#include "config.h"

void load_sites(const char *filepath, SiteConfig *config)
{
 config->port = 0;
  snprintf(config->root, sizeof(config->root), "/etc/spyderfly/index");
  snprintf(config->domain, sizeof(config->domain), "localhost");

  FILE *idk = fopen(filepath, "r");
  if (idk == NULL)
  {
    perror("Failed to open file");
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), idk) != NULL)
  {
    line[strcspn(line, ";\r\n")] = 0;

    int parsed_port;
    if (sscanf(line, "listen %d", &parsed_port) == 1) config->port = parsed_port;

    char parsed_root[STR_LEN];
    if (sscanf(line, "root %s", parsed_root) == 1) snprintf(config->root, sizeof(config->root), "%s", parsed_root);

    char parsed_name[STR_LEN];
    if (sscanf(line, "server_name %s", parsed_name) == 1) snprintf(config->domain, sizeof(config->domain), "%s", parsed_name);
  }
  fclose(idk);

  if (config->port == 0) fprintf(stderr, "Error: Config file %s is missing a 'listen <port>' directive.\n", filepath);

  printf("Successfully parsed config: Port=%d, Root=%s, Domain=%s\n", config->port, config->root, config->domain);
}
