#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SITES "/etc/spyderfly/enabled-sites"
#define DIS_SITES "/etc/spyderfly/disabled-sites"
#define TEST "sudo spyderfly -t"
#define RELOAD "sudo systemctl reload spyderfly"
#define AUTO_VERS "0.1.0"

void ip(void);

int auto_config(void);
int run_presets(void);
int run_manual(void);

// create these
int run_jellyfin(void);
int run_plex(void);
int run_immich(void);
int run_nextcloud(void);

int run_proxy(void);
int run_directory(void);

int run_http(void);
int run_https(void);

int create_conf(void);

extern char lan_ip[256];

extern char conf_name[256];
extern char conf_path[1024];
extern char port[10];
extern char root[512];
extern char domain[512];

extern char start[5];
extern char manual[10];
extern char http_https[10];
extern char list[10];