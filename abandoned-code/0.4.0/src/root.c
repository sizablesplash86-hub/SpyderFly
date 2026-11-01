// File 3
#include "core.h"

void root(const char *conf)
{
  FILE *rt = fopen(conf, "r");
  if (rt == NULL) perror("Could not find the main config file\n");
  
  char tdb[FILE_SIZE];
  int idk = 0;

  while (fgets(tdb, sizeof(tdb), rt) != NULL)
  {
    if (strncmp(tdb, "root *", 5) == 0)
    {
      idk = 1;
      break;
    }
  }
  fclose(rt);

  char *root = tdb + 5;
  if (idk)
  {

    char *ptr = tdb + 5;
    while (*ptr == ' ' || *ptr == '\t') ptr++;

    ptr[strcspn(ptr, "\r\n; ")] = 0;
    size_t len = strlen(ptr);
    if (len > 1 && ptr[len - 1] == '/') ptr[len - 1] = '\0';
    strncpy(conf_root, ptr, STR_LEN);
    printf("Root is: %s\n", conf_root);
  }

  else
  {
    printf("\nRoot not found\n\n");
    return;
  }
}