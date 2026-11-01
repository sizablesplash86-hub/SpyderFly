/*
 * * * * * *
 * File 10 *
 * * * * * *
 */

#include "core.h"

void ste_domain(const char *full_path)
{
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
    if (strncmp(line, "server_name ", 11) == 0)
    {
      found = 1;
      break;
    }
  }
  fclose(pt);

  char *domain = line + 11;
  if (found)
  {
    line[strcspn(line, "\r\n;")] =0;
    
    while (*domain == ' ' || *domain == '\t') domain++;
    snprintf(global_ste_domain, sizeof(global_ste_domain), "%s", domain);
    spydrfly_log("Server name %s found!", global_ste_domain);
  }

  else
  {
    spydrfly_log("\nServer name not found in %s", full_path);
    return;
  }
}