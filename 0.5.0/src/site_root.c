/*
 * * * * * *
 *  File 8 *
 * * * * * *
 */

#include "core.h"

void ste_root(const char *full_path)
{
  spydrfly_log("Reading for root...");

  FILE *rt = fopen(full_path, "r");
  if (rt == NULL) {
    spydrfly_log("Could not open the config file");
    return;
  }
  
  char tdb[512];
  int idk = 0;

  while (fgets(tdb, sizeof(tdb), rt) != NULL)
  {
    if (strncmp(tdb, "root ", 5) == 0)
    {
      idk = 1;
      break;
    }
  }
  fclose(rt);

  if (idk)
  {
    char *ptr = tdb + 5;
    while (*ptr == ' ' || *ptr == '\t') ptr++;

    ptr[strcspn(ptr, "\r\n; ")] = 0;
    size_t len = strlen(ptr);
    if (len > 1 && ptr[len - 1] == '/') ptr[len - 1] = '\0';

    snprintf(global_ste_root, sizeof(global_ste_root), "%s", ptr);
    spydrfly_log("Root %s found!", global_ste_root); // Fixed: using global_ste_root string buffer
  }
  else
  {
    spydrfly_log("Root not found in %s", full_path);
    global_ste_root[0] = '\0';
    return;
  }
}