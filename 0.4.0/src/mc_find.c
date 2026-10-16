#include "core.h"

void mc_check(const char *conf)
{
  FILE *pt = fopen(conf, "r");
  if (pt == NULL) perror("Could not find the main config file\n");
  char line[FILE_SIZE];
  int found = 0;
  while (fgets(line, sizeof(line), pt) != NULL)
  {
    if (strncmp(line, "minecraft *", 10) == 0)
    {
      found = 1;
      break;
    }
  }
  fclose(pt);

  char *mc = line + 10;
  if (found)
  {
    line[strcspn(line, "\r\n;")] =0;
    
    while (*mc == ' ' || *mc == '\t') mc++;

    if (strcmp(mc, "yes") == 0)
    {
      printf("Minecraft detected. Binding later...\n");
      snprintf(minecraft, sizeof(minecraft), "%s", mc);
    }

    else
    {
      printf("Not doing Minecraft...\n");
    }
  }

  else
  {
    printf("\nMinecraft define not found\n\n");
  }
}