/* 
 * * * * * *
 *  File 9 *
 * * * * * *
 */

#include "core.h"

void ste_port(const char *full_path)
{
  spydrfly_log("Checking for port number...");

  FILE *pt = fopen(full_path, "r");
  if (pt == NULL)
  {
    spydrfly_log("Could not find the main config file");
    return;
  }

  char line[512];
  int found = 0;
  while (fgets(line, sizeof(line), pt) != NULL)
  {
    if (strncmp(line, "listen ", 7) == 0)
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
    snprintf(global_ste_port, sizeof(global_ste_port), "%s", port);
    spydrfly_log("Port %s found", global_ste_port);
  }

  else
  {
    spydrfly_log("Port not found in %s", full_path);
    return;
  }
}