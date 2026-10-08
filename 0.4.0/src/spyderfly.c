// File 1
#include "core.h"

char conf[STR_LEN];
char conf_port[STR_LEN];
char conf_root[STR_LEN];
char site_name[STR_LEN];
char site_log[FILE_SIZE];
char ste_root[STR_LEN];
char ste_port[STR_LEN];
char ste_domain[STR_LEN];

int main()
{
  // side note, figure out how to do a full global parser
  snprintf(conf, sizeof(conf), "/etc/spyderfly/config/spyderfly.conf");
  printf("\nWelcome to SpyderFly %s!\n\n", VERSION);
  
  // cuz these are global characters, idk if I have to pass them through... probably not
  port(conf);  // File 2
  root(conf);  // File 3
  
  printf("starting SpyderFly on port %s in %s\n\n", conf_port, conf_root);

  ip_bind(conf_port);  // File 4
}