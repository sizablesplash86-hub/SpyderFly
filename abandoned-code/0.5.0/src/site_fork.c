/*
 * * * * * *
 * File 11 *
 * * * * * *
 */

#include "core.h"

int site_fork(const char *site_name, const char *site_root, const char *site_port, const char *site_domain)
{
  if (strcmp(site_domain, "_") == 0) spydrfly_log("Site domain = NULL. Ignoring site domain...");

  pid_t pid = fork();

  if (pid < 0)
  {
    spydrfly_log("Fork failed!");
    return 1;
  }

  if (pid == 0)
  {
    setsid();


    if (chdir(site_root) != 0)
    {
      spydrfly_log("Failed to find site root");
      exit(0);
    }

    if (strcmp(site_domain, "_") == 0)
    {
      spydrfly_log("Binding %s...", site_name);
      http_site_bind(site_root, site_port);
    }

    else
    {
      spydrfly_log("Starting HTTPS server for %s...", site_name);
      printf("HTTPS site bind is not setup yet\n");
//      https_site_bind(site_root, site_port, site_domain);
    }
  }

  else
  {
    printf("Not properly setup yet\n");
  }

  return 0;
}