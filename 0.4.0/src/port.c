// File 2
#include "core.h"

void port(const char *conf)
{
  FILE *pt = fopen(conf, "r");
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
//    printf("Port %s found!\n\n", port);
  }

  else
  {
    printf("\nPort not found\n\n");
    return;
  }
  snprintf(conf_port, sizeof(conf_port), "%s", port);
}