/*
 * Currently just placeholder, proably won't be in final release
 */


#include "../spyderfly.h"

int main(void)
{
  printf("Checking latest release...\n");

  char cmd[512];
  char latest_version[64];

  snprintf(cmd, sizeof(cmd), "curl -s H\"User-Agent: spyderfly\" %s | grep '\"tag_name\":' | sed -E 's/.*\"([^\"]+)\".*/\\1/'", REPO_URL);

  FILE *fp = popen(cmd, "r");
  if (fp == NULL)
  {
    printf("Failed to check latest version\n");
    return -1;
  }

  fgets(latest_version, sizeof(latest_version), fp);
  latest_version[strcspn(latest_version, "\r\n")] = 0;

  pclose(fp);

  if (strcmp(latest_version, "") == 0)
  {
    printf("\nHi! It seems there are no releases for SpyderFly as of now. Thank you for being a beta supporter.\n\n");
    return 0;
  }

  printf("Latest version: %s\nCurrent version: %s\n", latest_version, SPYDRFLY_CURR_VERS);

  if (strcmp(latest_version, SPYDRFLY_CURR_VERS) > 0)
  {
    printf("Would you like to update? y/n: ");

    char ans;
    scanf("%c", &ans);

    if (ans == 'y')
    {
      TODO: // add updating thing
    }

    else printf("Not updating...\n");
  }

  else if (strcmp(latest_version, SPYDRFLY_CURR_VERS) == 0) printf("Current release is latest release\n");

  else printf("\nHi! It seems there are no releases for SpyderFly as of now. Thank you for being a beta supporter.\n\n");

  return 0;
}






#include <curl/curl.h>

struct MemoryStruct
{
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) return -1;

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

int get_latest_version(const char *repo_url, char *version_out, size_t max_len)
{
  CURL *curl_handle;
  CURLcode res;

  struct MemoryStruct chunk;
  chunk.memory = malloc(1);
  chunk.size = 0;

  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();

  if(!curl_handle)
  {
    free(chunk.memory);
    return -1;
  }

  curl_easy_setopt(curl_handle, CURLOPT_URL, repo_url);

  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "spyderfly");

  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);

  res = curl_easy_perform(curl_handle);

  if(res != CURLE_OK)
  {
    fprintf(stderr, "Failed to check latest version: %s\n", curl_easy_strerror(res));
    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    curl_global_cleanup();
    return -1;
  }

  char *tag_ptr = strstr(chunk.memory, "\"tag_name\"");
  int found = 0;

  if (tag_ptr)
  {
    char *colon = strchr(tag_ptr, ':');
    if (colon)
    {
      char *start_quote = strchr(colon, '"');
      if (start_quote)
      {
        start_quote++;
        char *end_quote = strchr(start_quote, '"');
        if (end_quote)
        {
          size_t len = end_quote - start_quote;
          if (len < max_len)
          {
            memcpy(version_out, start_quote, len);
            version_out[len] = '\0';
            found = 1;
          }
        }
      }
    }
  }

  curl_easy_cleanup(curl_handle);
  free(chunk.memory);
  curl_global_cleanup();

  return found ? 0 : -1;
}