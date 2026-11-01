/*
 * * * * * *
 *  File 7 *
 * * * * * *
 */

#include "core.h"

typedef struct
{
  char site_root[64];
  char site_port[10];
  char site_domain[32];
} SiteConfig;

void load_sites(void)
{
  spydrfly_log("loading sites...");

  DIR *dir = opendir(SITES);
  if (dir == NULL)
  {
    spydrfly_log("Failed to open sites directory");
    return;
  }

  struct dirent *entry;

  while((entry = readdir(dir)) != NULL)
  {
    if (entry->d_name[0] == '.') continue;

    // Reset globals for each iteration
    memset(global_ste_root, 0, sizeof(global_ste_root));
    memset(global_ste_port, 0, sizeof(global_ste_port));
    memset(global_ste_domain, 0, sizeof(global_ste_domain));

    char site_name[128];
    snprintf(site_name, sizeof(site_name), "%s", entry->d_name);

    spydrfly_log("Checking %s...", site_name);

    size_t len = strlen(entry->d_name);
    if (len > 5 && strcmp(entry->d_name + len - 5, ".site") == 0)
    {
      SiteConfig cfg;
      memset(&cfg, 0, sizeof(cfg));

      char full_path[256];
      snprintf(full_path, sizeof(full_path), "%s/%s", SITES, site_name);
      spydrfly_log("Found site config in %s", full_path);

      spydrfly_log("Opening config...");
      ste_root(full_path);
      snprintf(cfg.site_root, sizeof(cfg.site_root), "%s", global_ste_root);
      if (strlen(cfg.site_root) == 0)
      {
        spydrfly_log("ERROR. Site %s does not contain root", site_name);
        return;
      }

      spydrfly_log("checking for port...");
      ste_port(full_path);
      snprintf(cfg.site_port, sizeof(cfg.site_port), "%s", global_ste_port);
      if (strlen(cfg.site_port) == 0)
      {
        spydrfly_log("ERROR. Site %s does not contain port number", site_name);
        return;
      }

      spydrfly_log("Checking site domain...");
      ste_domain(full_path);
      snprintf(cfg.site_domain, sizeof(cfg.site_domain), "%s", global_ste_domain);
      if (strlen(cfg.site_domain) == 0) 
      {
        spydrfly_log("Site domain not found. Moving on...");
        snprintf(cfg.site_domain, sizeof(cfg.site_domain), "_");
      }

      spydrfly_log("running site fork...");
      site_fork(site_name, cfg.site_root, cfg.site_port, cfg.site_domain);
    }
  }
  closedir(dir);
}