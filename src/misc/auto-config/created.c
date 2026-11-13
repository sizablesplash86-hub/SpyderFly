#include "auto-config.h"

int created(void)
{

  if (system(TEST) != 0)
  {
    printf("\033[31mERROR\033[0m in site config! Moving into disabled sites...\n");

    char dis_conf[1024];
    snprintf(dis_conf, sizeof(dis_conf), "%s/%s.site", DIS_SITES, conf_name);
    if (rename(conf_path, dis_conf) == 0) printf("Sucessfully moved to disabled sites\n");
    else printf("Failed to move to disabled sites\n");
    return -1;
  }

  if (strcmp(start, "y") == 0 || strcmp(start, "Y") == 0 ||
    strcmp(manual, "1") == 0 || 
    strcmp(http_https, "2") == 0
  )
  {
    if (system(TEST) != 0)
    {
        printf("\033[31mERROR\033[0m in site config! Moving into disabled sites...\n");

        char dis_conf[1024];
        snprintf(dis_conf, sizeof(dis_conf), "%s/%s.site", DIS_SITES, conf_name);
        if (rename(conf_path, dis_conf) == 0) printf("Sucessfully moved to disabled sites\n");
        else printf("Failed to move to disabled sites\n");
        return -1;
    }
    else
    {
      char cert[1024];
      snprintf(cert, sizeof(cert), "sudo certbot --spyderfly -d %s", domain);

      if (system(cert) != 0)
      {
        printf("\033[31mERROR!\033[0m Failed to deploy cert\n");
        return -1;
      }
      else printf("Cert deployed!\n");

      if (system(RELOAD) != 0)
      {
        printf("\033[31mERROR\033[0m Failed to reload SpyderFly\n");
        return -1;
      }
      else printf("Site loaded! Visit \033[34mhttps://%s\033[0m in your browser to see your site\n", domain);
    }
  }

  else 
  {
    if (system(RELOAD) != 0)
    {
      printf("\033[31mERROR\033[0m Failed to reload SpyderFly\n");
      return -1;
    }
    else printf("Site loaded! Visit \033[34mhttp://%s:%s\033[0m in your browser to see your site\n", lan_ip, port);
  }

  return 0;
}