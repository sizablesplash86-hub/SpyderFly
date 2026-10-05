// File 8
#include "core.h"

void site_root(const char *full_path)
{
  FILE *rt = fopen(full_path, "r");
  if (rt == NULL) {
    perror("Could not find the config file");
    return;
  }
  
  char tdb[FILE_SIZE];
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

    snprintf(ste_root, sizeof(ste_root), "%s", ptr);
    printf("Root %s found!\n", ste_root);
  }
  else
  {
    printf("Root not found\n");
  }
}