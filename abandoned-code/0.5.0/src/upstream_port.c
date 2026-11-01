/*
 * * * * * *
 *  File 4 *
 * * * * * *
 */

#include "core.h"

void upstream_port(void)
{
  FILE *fp = fopen(conf, "r");

  if (fp == NULL)
  {
    spydrfly_log("Failed to open main config file");
    return;
  }

  spydrfly_log("Opened main config file");

  char line[512];
  int found = 0;
  while (fgets(line, sizeof(line), fp) != NULL)
  {
    if (strncmp(line, "listen ", 7) == 0)
    {
      found = 1;
      break;
    }
  }
  char line2[512];
  int found2 = 0;
  while (fgets(line2, sizeof(line2), fp) != NULL)
  {
    if (strncmp(line2, "listen_ssl ", 11) == 0)
    {
      found2 = 1;
      break;
    }
  }
  fclose(fp);

  char *port = line + 7;
  char *port2 = line2 + 11;
  if (found)
  {
    line[strcspn(line, ";\r\n")] = 0;
    line2[strcspn(line2, ";\r\n")] = 0;


    snprintf(http_port, sizeof(http_port), "%s", port);
    snprintf(ssl_port, sizeof(ssl_port), "%s", port2);
    spydrfly_log("Found HTTP port to be %s", http_port);
    spydrfly_log("Found SSL port to be %s", ssl_port);
  }
}