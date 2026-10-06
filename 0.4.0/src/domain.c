// File 9
#include "core.h"

// see docs/steps to know how to make this

void site_domain(const char *full_path)
{
  FILE *pt = fopen(full_path, "r");
  if (pt == NULL) perror("Could not find the main config file\n");
  char line[FILE_SIZE];
  int found = 0;
  while (fgets(line, sizeof(line), pt) != NULL)
  {
    if (strncmp(line, "server_name *", 11) == 0)
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
    printf("Server name %s found!\n\n", domain);

    if (strcmp(domain, "_") == 0)
    {
      printf("Ignoring site domain...\n");
      snprintf(ste_domain, sizeof(ste_domain), "%s", domain);
    }

    else
    {
      printf("passing domain to SSL config...\n\n");
      sdrfy_ssl(ste_domain);
    }


  }

  else
  {
    printf("\nServer name not found in %s\n\n", full_path);
    return;
  }
}