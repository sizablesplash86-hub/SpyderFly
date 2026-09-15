#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STR_LEN 256

char version[STR_LEN];
char conf[STR_LEN];

int main()
{
  printf("Enter version name (eg: \"1.0.0\" ): ");
  fgets(version, sizeof(version), stdin);
  version[strcspn(version, "\n")] = 0;

  system("rm spyderfly-pkg/DEBIAN/control");
  FILE *fp = fopen("spyderfly-pkg/DEBIAN/control", "w");
  fprintf(fp,
    "Package: spyderfly\n"
    "Version: %s\n"
    "Section: utils\n"
    "Priority: optional\n"
    "Architecture: amd64\n"
    "Depends: certbot\n"
    "Maintainer: sizablesplash86\n"
    "Description: Web server inspired by NGINX made easy\n",
    version
  );
  fclose(fp);

  system("rm /var/www/repos/spyderfly/releases/latest/latest");
  system("gcc -O2 install.c -o /var/www/repos/spyderfly/releases/latest/latest");
  system("chmod +x /var/www/repos/spyderfly/releases/latest/latest");
  system("cp /var/www/repos/spyderfly/releases/latest/latest /var/www/repos/spyderfly/releases/v%s/%s", version, version);
  system("chmod +x /var/www/repos/spyderfly/releases/v%s/%s", version, version);
  system("dpkg-deb --build spyderfly-pkg spyderfly_%s_amd64.deb", version);
  system("mv spyderfly_%s_amd64.deb /var/www/repos/spyderfly/releases/v%s/spyderfly_%s_amd64.deb", version, version, version);
  system("rm /var/www/repos/spyderfly/releases/latest/latest.deb");
  system("cp /var/www/repos/spyderfly/releases/v%s/spyderfly_%s_amd64.deb /var/www/repos/spyderfly/releases/latest/latest.deb", version, version);
}