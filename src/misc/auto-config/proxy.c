#include "auto-config.h"

int run_proxy(void)
{
  printf("Enter config name: ");
  fgets(conf_name, sizeof(conf_name), stdin);
  conf_name[strcspn(conf_name, "\r\n")] = 0;
  snprintf(conf_path, sizeof(conf_path), "%s/%s.site", SITES, conf_name);
  struct stat st;

  if (stat(conf_path, &st) == 0)
  {
    printf("\033[31mERROR!\033[0m Config file already exists\n");
    return -1;
  }

  char temp[512];
  printf("Enter proxy IP (or leave blank for localhost): ");
  fgets(temp, sizeof(temp), stdin);
  temp[strcspn(temp, "\r\n")] = 0;

  if (strcmp(temp, "") == 0 || strcmp(temp, " ") == 0) snprintf(prox, sizeof(prox), "127.0.0.1");
  else snprintf(prox, sizeof(prox), "%s", temp);

  TODO: // add rest

  return 0;
}