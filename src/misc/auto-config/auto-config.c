#include "auto-config.h"

char lan_ip[256];

char conf_name[256];
char conf_path[1024];
char port[10];
char root[512];
char domain[512];

char start[5];
char manual[10];
char http_https[10];
char list[10];

int auto_config(void)
{
  ip();

  printf("\nWelcome to the SpyderFly auto config v%s!\n\n", AUTO_VERS);

  int valid = 0;
  do
  {
    printf("Would you like to do presets? y/n: ");
    fgets(start, sizeof(start), stdin);
    start[strcspn(start, "\n")] = 0;

    if (strcmp(start, "y") == 0 || strcmp(start, "Y") == 0) 
    {
      run_presets();
      return 0;
    }

    else if (strcmp(start, "n") == 0 || strcmp(start, "N") == 0) 
    {
      run_manual();
      return 0;
    }

    else if (strcmp(start, "q") == 0 || strcmp(start, "Q") == 0)
    {
      printf("Exiting now...\n");
      return 0;
    }
    else printf("Please enter y or n\n");
  }while(!valid);

  return 0;
}