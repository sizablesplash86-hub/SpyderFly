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
    snprintf(ste_domain, sizeof(ste_domain), "%s", domain);

    if (strcmp(domain, "_") == 0)
    {
      printf("Ignoring site domain...\n");
    }

    else
    {
      printf("passing domain %s to SSL config...\n\n", domain);

      pid_t pid = fork();
      if (pid < 0)
      {
        perror("Fork failed!\n");
        return;
      }

      // Inside load_sites.c worker fork:
      if (pid == 0)
      {
        setsid();

        if (chdir(ste_root) != 0)
        {
          perror("Failed to locate site root directory");
          exit(1);
        }

        FILE *log = freopen(site_log, "w", stdout);
        freopen(site_log, "w", stderr);

        sdrfy_ssl(ste_domain);

        exit(0);
      }
    }


  }

  else
  {
    printf("\nServer name not found in %s\n\n", full_path);
    return;
  }
}