#include "core.h"

void web_mc(const char *full_path)
{
  FILE *pt = fopen(full_path, "r");
  if (pt == NULL) perror("Could not find the main config file\n");
  char line[FILE_SIZE];
  int found = 0;
  while (fgets(line, sizeof(line), pt) != NULL)
  {
    if (strncmp(line, "define ", 7) == 0)
    {
      found = 1;
      break;
    }
  }
  fclose(pt);

  char *mc = line + 7;
  if (found)
  {
    line[strcspn(line, "\r\n;")] =0;
    
    while (*mc == ' ' || *mc == '\t') mc++;
    printf("Site is a Minecraft parser\n\n");
  }

  else printf("site is not a Minecraft parser\n");
}