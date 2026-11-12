#include "../spyderfly.h"

int start_spyderfly(void)
{
  if (remove(pid_file) == 0) printf("Removed PID file\n");
  else printf("Failed to remove PID file\n");

  printf("loading sites...\n");
  if (load_sites() != 0)
  {
    printf("Failed to load sites. Exiting now...\n");
    return 1;
  }

  printf("Starting SpyderFly...\n");
  while (1)
  {
    printf("[*] Main loop is here\n");
    
    sleep(5);
  }
}