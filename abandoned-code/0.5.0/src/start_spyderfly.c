/*
 * * * * * *
 *  File 2 *
 * * * * * *
 */

#include "core.h"

int start_spyderfly(void)
{
  snprintf(pid_conf, sizeof(pid_conf), "/run/spyderfly.pid");
  FILE *rn = fopen("/run/spyderfly.pid", "w");
  if (rn == NULL)
  {
    spydrfly_log("Failed to access PID file");
    return 1;
  }
  fclose(rn);

  spydrfly_log("Flushed PID file");

  spydrfly_log("Welcome to SpyderFly %s!", SPYDERFLY_VERSION);  // File 3

  snprintf(conf, sizeof(conf), "/etc/spyderfly/config/spyderfly.conf");
  upstream_port();  // File 4

  http_bind();  // File 5

  return 0;
}