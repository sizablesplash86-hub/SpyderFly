// File 6
#include "core.h"

void load_sites(void)
{
  printf("Loading sites...\n");
  const char *dir_path = "/etc/spyderfly/enabled-sites";
  DIR *dir = opendir(dir_path);
    
  if (dir == NULL)
  {
    perror("Could not open sites directory");
    return;
  }

  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL)
  {
    if (entry->d_name[0] == '.') continue;

    snprintf(site_name, sizeof(site_name), "%s", entry->d_name);
    printf("Site name is %s\n", site_name);  // change them after verifying it works

    size_t len = strlen(entry->d_name);
    if (len > 5 && strcmp(entry->d_name + len - 5, ".conf") == 0)
    {
      char full_path[512];
      snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
      printf("Found site config: %s\n", full_path);

      site_root(full_path);
      site_port(full_path);
      
      site_domain(full_path);  // figure out this

      printf("Creating site in %s on port %s\n", ste_root, ste_port);

      snprintf(site_log, sizeof(site_log), "/etc/spyderfly/log/%s.log", entry->d_name);

      pid_t pid = fork();
      if (pid < 0)
      {
        perror("Fork failed!\n");
        continue;
      }

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

        site_bind(ste_port, ste_root);  // File 10

        printf("SpyderFly site worker active for %s\n", entry->d_name);
        exit(0);
      } 
      else
      {
        printf("Spawned SpyderFly site background process with PID: %d\n", pid);
        
        FILE *f = fopen(full_path, "a");
        if (f != NULL)
        { // make it so it adds it and removes it if its already there
          fprintf(f, "\npid=%d\n", pid);
          fclose(f);
          printf("Site PID saved to configuration.\n");
        }
        else perror("Failed to update site.conf with PID");
      }
    }
  }
  closedir(dir);
}