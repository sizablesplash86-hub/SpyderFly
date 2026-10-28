#include "core.h"

int start_spyderfly(void)
{
  if (remove(pid_file) == 0) spydrfly_log("Removed PID file\n");
  else spydrfly_log("Failed to remove PID file\n");

  spydrfly_log("loading sites...\n");
  if (load_sites() != 0)
  {
    spydrfly_log("Failed to load sites. Exiting now...\n");
    return 1;
  }

  spydrfly_log("Starting SpyderFly...\n");
  while (1)
  {
    //
  }
}