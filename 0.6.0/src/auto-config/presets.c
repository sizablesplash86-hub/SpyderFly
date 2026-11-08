#include "auto-config.h"

int run_presets(void)
{
  char preset[256];
  int valid = 0;
  do 
  {
    printf("Enter 1 for Jellyfin, 2 for Plex, 3 for Immich, 4 for Nextcloud LSMP stacks: ");
    fgets(preset, sizeof(preset), stdin);
    preset[strcspn(preset, "\n")] = 0;

    if (strcmp(preset, "1") == 0) 
    {
//      run_jellyfin();
      return 0;
    }
    else if (strcmp(preset, "2") == 0) 
    {
//      run_plex();
      return 0;
    }
    else if (strcmp(preset, "3") == 0) 
    {
//      run_immich();
      return 0;
    }
    else if (strcmp(preset, "4") == 0) 
    {
//      run_nextcloud();
      return 0;
    }
    else if (strcmp(preset, "q") == 0 || strcmp(preset, "Q") == 0)
    {
      printf("Exiting now...\n");
      return 0;
    }
    else printf("Please enter 1-4 or q to exit\n");
  }while (!valid);

  return 0;
}