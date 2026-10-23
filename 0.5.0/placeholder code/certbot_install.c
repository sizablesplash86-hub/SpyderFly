#include "../src/core.h"

void post_install_certbot(void)
{
  if (system("certbot --version") != 0)
  {
    printf("Certbot not installed! Please install and rerun\n");
    return;
  }

  char cmd[128];
  snprintf(cmd, sizeof(cmd), "wget %s/certbot/releases/latest.deb -O /tmp/spyderfly_certbot.deb", SPYDERFLY_REPO);
  if (system(cmd) != 0)
  {
    printf("Failed to download certbot for SpyderFly\n");
    return;
  }
  else
  {
    printf("Installing deb...\n");
    if (system("sudo apt install /tmp/spyderfly_certbot.deb") != 0)
    {
      printf("Failed to install deb package\n");
      return;
    }

    else printf("Sucessfully installed SpyderFly certbot! Run\"sudo certbot --spyderfly\" to verify install\n");
  }
}