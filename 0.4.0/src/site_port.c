// File 7
#include "core.h"

void site_port(const char *full_path)
{
  FILE *pt = fopen(full_path, "r");
  if (pt == NULL) perror("Could not find the main config file\n");
  char line[FILE_SIZE];
  int found = 0;
  while (fgets(line, sizeof(line), pt) != NULL)
  {
    if (strncmp(line, "listen *", 7) == 0)
    {
      found = 1;
      break;
    }
  }
  fclose(pt);

  char *port = line + 7;
  if (found)
  {
    line[strcspn(line, "\r\n;")] =0;
    
    while (*port == ' ' || *port == '\t') port++;
    printf("Port %s found!\n\n", port);
    snprintf(ste_port, sizeof(ste_port), "%s", port);
  }

  else
  {
    printf("\nPort not found\n\n");
    return;
  }
}