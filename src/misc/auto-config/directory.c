#include "auto-config.h"

int run_directory(void)
{
  int valid = 0;
  do
  {
    printf("Enter 1 for HTTP or 2 for HTTPS: ");
    fgets(http_https, sizeof(http_https), stdin);
    http_https[strcspn(http_https, "\r\n")] = 0;

    if (strcmp(http_https, "1") == 0)
    {
        if (run_http() != 0) return -1;
        return 0;
    }
    else if (strcmp(http_https, "2") == 0)
    {
        run_https();
        return 0;
    }
    else if (strcmp(http_https, "q") == 0 || strcmp(http_https, "Q") == 0)
    {
        printf("Exiting now...\n");
        return 0;
    }
  }while (!valid);

  return 0;
}