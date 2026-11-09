#include "auto-config.h"

int run_https(void)
{
  struct stat st;

  int valid = 0;
  do
  {
    printf("Enter config name: ");
    fgets(conf_name, sizeof(conf_name), stdin);
    conf_name[strcspn(conf_name, "\r\n")] = 0;

    snprintf(conf_path, sizeof(conf_path), "%s/%s.site", SITES, conf_name);
    if (stat(conf_path, &st) == 0)
    {
      printf("\033[31mERROR!\033[0m Config file already exists\n");
      continue;
    }

    printf("Enter directory root: ");
    fgets(root, sizeof(root), stdin);
    root[strcspn(root, "\r\n")] = 0;

    if (stat(root, &st) != 0)
    {
      printf("\033[31mERROR!\033[0m Root does not exist\n");
      continue;
    }

    printf("Enter domain name: ");
    fgets(domain, sizeof(domain), stdin);
    domain[strcspn(domain, "\r\n")] = 0;

    int valid2 = 0;
    do
    {
      printf("Would you like to add more? Enter 'list' to list options or press enter to continue: ");
      fgets(list, sizeof(list), stdin);
      list[strcspn(list, "\r\n")] = 0;

      if (strcmp(list, "list") == 0 || strcmp(list, "List") == 0)
      {
        printf(
          "More options:\n"
          "  '1'    PHP integration\n"
          "  '2'    auto index\n\n"
          "Type how many you want. (Eg: '1 2 4')\n"
        );
      }
      else if (strcmp(list, "q") == 0 || strcmp(list, "Q") == 0)
      {
        printf("Exiting now...\n");
        return 0;
      }
      else break;
    }while(!valid2);

    break;

  }while (!valid);

  printf("Press enter to create the config: ");
  char ent;
  scanf("%c", &ent);
  if (ent == 'q' || ent == 'Q')
  {
    printf("Exiting now...\n");
    return 0;
  }

  FILE *fp = fopen(conf_path, "w");
  if (fp == NULL)
  {
    printf("Failed to create config file\n");
    return -1;
  }

  fprintf(fp, 
    "server {\n"
    "  listen 80;\n"
    "  listen [::]:80;\n"
    "  root %s;\n"
    "  server_name %s;\n\n"

    "  index index.html;\n\n"

    "  location / {\n"
    "    default_type text/html;\n"
    "    try_files $uri $uri/ $uri/index.html $uri.html =404;\n"
    "  }\n"
    "\n  # add SSL here\n"
    "\n"
    "}\n",
    root, domain
  );

  fclose(fp);

  printf("Config created!\n");
  created();

  return 0;
}