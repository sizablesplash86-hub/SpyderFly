#include "core.h"


int main(int argc, char *argv[])
{
  if (getuid() != 0)
  {
    spydrfly_log("SpyderFly requires sudo privileges\n");
    return 0;
  }



  if (argc < 2)
  {
    printf("\nPlease enter a sub command. Run \"sudo spyderfly -h\" to see sub-commands\n\n");
    return 0;
  }

  if (strcmp(argv[1], "--certbot") == 0)
  {
    printf("Post install certbot install not setup yet\n");
    return 0;
  }

  if (strcmp(argv[1], "--auto-config") == 0)
  {
    printf("Setup eventually\n");
    return 0;
  }

  if (strcmp(argv[1], "-h") == 0)
  {
    printf("\nSpyderFly commands:\n\n"
      "  --certbot        post install Certbot installation\n"
      "  --auto-config    auto config for sites\n\n"
      "  -h    lists commands\n"
      "  -s    start SpyderFly\n"
      "  -t    test current config\n"
      "  -r    reload sites\n"
      "  -v    version\n\n"
    );
    return 0;
  }

  if (strcmp(argv[1], "-s") == 0) start_spyderfly();

  if (strcmp(argv[1], "-t") == 0)
  {
    printf("Testing not setup yet\n");
    return 0;
  }

  if (strcmp(argv[1], "-r") == 0)
  {
    printf("Reloading not setup yet\n");
    return 0;
  }

  if (strcmp(argv[1], "-v") == 0)
  {
    printf("SpyderFly v%s\n"
      "Copyright (c) SizableSplash\n"
      "Visit https://spyderfly.sizablesplash.com for releases and support\n"
      "Thank you for choosing SpyderFly!\n",
      VERSION
    );
    return 0;
  }

  else printf("Error! \"%s\" not found\n", argv[1]);
}