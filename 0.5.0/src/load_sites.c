/*
 * * * * * *
 *  File 7 *
 * * * * * *
 */

// this is what I'm working on
#include "core.h"

void load_sites(void)
{
  spydrfly_log("loading sites...");

  DIR *dir = opendir(SITES);
  if (dir == NULL)
  {
    spydrfly_log("Failed to open sites directory");
    return;
  }

  struct dirent *entry;

  while((entry = readdir(dir)) != NULL)
  {
    if (entry->d_name[0] == '.') continue;

    //
  }  // end of reading sites
  closedir(dir);
}