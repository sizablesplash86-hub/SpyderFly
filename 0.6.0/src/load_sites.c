#include "core.h"
/*
typedef struct
{
  site_domain[128];
  site_port[10];
  site_root[128];
} siteconfig;
*/

int load_sites(void)
{
  DIR *ste = opendir(sites_dir);

  if (ste == NULL)
  {
    spydrfly_log("Failed to open sites directory\n");
    return -1;
  }

  struct dirent *entry;

  while ((entry = readdir(ste)) != NULL)
  {
    if (entry->d_name[0] == '.') continue;

    char site_name[128];
    snprintf(site_name, sizeof(site_name), "%s", entry->d_name);

    spydrfly_log("Checking %s\n", site_name);

    size_t len = strlen(entry->d_name);
    if (len > 5 && strcmp(entry->d_name + len - 5, ".site") == 0)
    {
//      siteconfig cfg;

//      memset(&cfg, 0, sizeof(cfg));

      char full_path[1024];
      snprintf(full_path, sizeof(full_path), "%s/%s", sites_dir, site_name);

      if (ste_conf(full_path, site_name) < 0)
      {
        spydrfly_log("Failed to load site config for %s\n", site_name);
        return 1;
      }
    }
  }

  closedir(ste);
  return 0;
}