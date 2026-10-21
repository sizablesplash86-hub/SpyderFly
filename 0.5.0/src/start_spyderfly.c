/*
 * * * * * *
 *  File 2 *
 * * * * * *
 */

#include "core.h"

int start_spyderfly(void)
{
  printf("\nSee the recent log for what happens next\n\n");
  spydrfly_log("Welcome to SpyderFly %s", SPYDERFLY_VERSION);  // File 3

  snprintf(conf, sizeof(conf), "/etc/spyderfly/config/spyderfly.conf");
  upstream_port();  // File 4

  http_bind();  // File 5

  return 0;
}