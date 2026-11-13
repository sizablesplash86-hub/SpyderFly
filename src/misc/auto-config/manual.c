#include "auto-config.h"

int run_manual(void)
{
  int valid = 0;
  do
  {
    printf("Enter 1 for proxy or 2 for static directory: ");
    fgets(manual, sizeof(manual), stdin);
    manual[strcspn(manual, "\r\n")] = 0;

    if (strcmp(manual, "1") == 0)
    {
      run_proxy();
      return 0;
    }
    else if (strcmp(manual, "2") == 0)
    {
      if (run_directory() != 0) return -1;
      return 0;
    }
    else if (strcmp(manual, "q") == 0 || strcmp(manual, "Q") == 0)
    {
      printf("Exiting now...\n");
      return 0;
    }
    else printf("Please enter 1 or 2\n");
  }while (!valid);

  return 0;
}