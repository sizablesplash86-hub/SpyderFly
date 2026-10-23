/*
 * * * * * *
 *  File 1 *
 * * * * * *
 */

#include "core.h"

char conf[128];
char pid_conf[1024];
char http_port[10];
char ssl_port[10];

char global_ste_root[256];
char global_ste_port[10];
char global_ste_domain[128];

void list_commands(void)
{
  printf(
    "\n  --certbot       Post install SpyderFly certbot setup\n"
    "  --auto-config     Runs a built in auto config for sites\n\n"

    "  -s            Start SpyderFly web server\n"
    "  -t            Test SpyderFly configuration\n"
    "  -r            Reload sites\n"
    "  -h            List actions\n"
    "  -v            See current version\n\n"
  );
}

int main(int argc, char *argv[])  // check C.13.7
{
  if (getuid() != 0)
  {
    printf("SpyderFly must be run with sudo/root privileges\n");
    return 1;
  }

  if (argc < 2) 
  {
    printf("\nPlease enter sub command\nrun \"sudo spyderfly -h\" to see sub-commands\n\n");
    return 0;
  }

  if (strcmp(argv[1], "--certbot") == 0)
  {
    printf("Running Certbot post-install setup...\n\n");
//    run_certbot_setup();  // add later. See ../'placeholder code'/ for the prototype
  }

  if (strcmp(argv[1], "--auto-config") == 0)
  {
    printf("Auto config not ready yet\n");
//    auto_config();  // add eventually
  }

  if (strcmp(argv[1], "-s") == 0)
  {
    printf("Starting SpyderFly...\n");
    start_spyderfly();  // File 2
  }

  if (strcmp(argv[1], "-t") == 0) 
  {
    printf("Testing command not setup yet\n");
//    test_config();  // add later
  }

  if (strcmp(argv[1], "-r") == 0)
  {
    printf("Reloading sites not setup yet\n");
//    load_sites();  // File is there, just need to make sure other stuff works first
  }

  if (strcmp(argv[1], "-h") == 0) list_commands();

  if (strcmp(argv[1], "-v") == 0) printf("Current SpyderFly version is %s\n", SPYDERFLY_VERSION);
}