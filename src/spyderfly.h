#include "core/core.h"
#include "os/os.h"
#include "lib/lib.h"
#include "misc/misc.h"
#include "mc/mc.h"

#define SPYDRFLY_CURR_VERS "0.6.0"
#define REPO_URL "https://api.github.com/repos/sizablesplash86-hub/spyderfly/releases/latest"

/* Commands */
int update(void);
int start_spyderfly(void);
int load_sites(void);
int ste_conf(const char *full_path, const char *site_name);
int site_bind(const char *site_name, const char *site_port, const char *site_root, const char *site_domain, const char *dm_fullchain, const char *dm_privkey, const char *dm_trusted_cert);

//int site_upstream(int sockfd, int addrlen, const char *site_root);
int site_upstream(int sockfd, const char *site_root);

void spydrfly_log(const char *format, ...);