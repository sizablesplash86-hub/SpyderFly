#include "core.h"

typedef struct {
    char domain[128];
    char port[10];
    char root[128];

    // SSL Directives
    char fullchain[256];     // ssl_certificate
    char privkey[256];       // ssl_certificate_key
    char trusted_cert[256];  // ssl_trusted_certificate
} ServerConfig;

// Function to pull the next logical token from the file stream,
// handling whitespace, comments (#), and punctuation ({, }, ;)
int next_token(FILE *fp, char *buf, size_t max_len)
{
  int c;
  size_t len = 0;

  // 1. Skip whitespace and comments
  while ((c = fgetc(fp)) != EOF)
  {
    if (c == '#')
    {
      // Skip until end of line
      while ((c = fgetc(fp)) != EOF && c != '\n');
      continue;
    }
    if (!isspace(c))
    {
      ungetc(c, fp);
      break;
    }
  }

  if (c == EOF) return 0;

  // 2. Check for structural single-character tokens
  c = fgetc(fp);
  if (c == '{' || c == '}' || c == ';')
  {
    buf[0] = (char)c;
    buf[1] = '\0';
    return 1;
  }

  // 3. Read a standard word token (directive name, path, value, etc.)
  ungetc(c, fp);
  while ((c = fgetc(fp)) != EOF)
  { 
    if (isspace(c) || c == '{' || c == '}' || c == ';')
    {
      ungetc(c, fp);
      break;
    }
    if (len < max_len - 1)
    {
      buf[len++] = (char)c;
    }
  }
  buf[len] = '\0';
  return len > 0 ? 1 : 0;
}

// Function to parse the config file stream into a ServerConfig struct
int parse_config(const char *fullpath, ServerConfig *config)
{
  FILE *fp = fopen(fullpath, "r");
  if (!fp)
  {
    printf("Failed to open config file: %s\n", fullpath);
    return -1;
  }

  char token[256];
  int inside_server_block = 0;

  while (next_token(fp, token, sizeof(token)))
  {
    // Look for the "server" block declaration
    if (strcmp(token, "server") == 0)
    {
      if (next_token(fp, token, sizeof(token)) && strcmp(token, "{") == 0)
      {
        inside_server_block = 1;
      }
      else
      {
        printf("Syntax error: expected '{' after server\n");
        fclose(fp);
        return -1;
      }
    } 
    else if (inside_server_block)
    {
      // Check for block closure
      if (strcmp(token, "}") == 0)
      {
        inside_server_block = 0;
        break; 
      }

      int directive_handled = 1;

      // Parse known directives
      if (strcmp(token, "listen") == 0)
      {
        if (next_token(fp, token, sizeof(token)))
        {
          snprintf(config->port, sizeof(config->port), "%s", token);
        }
      } 
      else if (strcmp(token, "root") == 0)
      {
        if (next_token(fp, token, sizeof(token)))
        {
          size_t len = strlen(token);
          if (len > 1 && token[len - 1] == '/') token[len - 1] = '\0';
          snprintf(config->root, sizeof(config->root), "%s", token);
        }
      } 
      else if (strcmp(token, "server_name") == 0) 
      {
        if (next_token(fp, token, sizeof(token)))
        {
          snprintf(config->domain, sizeof(config->domain), "%s", token);
        }
      }
      else if (strcmp(token, "ssl_certificate") == 0)
      {
        if (next_token(fp, token, sizeof(token)))
        {
          snprintf(config->fullchain, sizeof(config->fullchain), "%s", token);
        }
      }
      else if (strcmp(token, "ssl_certificate_key") == 0)
      {
        if (next_token(fp, token, sizeof(token)))
        {
          snprintf(config->privkey, sizeof(config->privkey), "%s", token);
        }
      }
      else if (strcmp(token, "ssl_trusted_certificate") == 0)
      {
        if (next_token(fp, token, sizeof(token)))
        {
          snprintf(config->trusted_cert, sizeof(config->trusted_cert), "%s", token);
        }
      }
      else
      {
        // Unrecognized directive (e.g., include, ssl_dhparam, etc.)
        // Consume tokens safely until the trailing semicolon ';' is reached
        directive_handled = 0;
        char skip_token[256];
        while (next_token(fp, skip_token, sizeof(skip_token)))
        {
          if (strcmp(skip_token, ";") == 0) break;
        }
      }

      // If it was a recognized directive, verify it ends with a semicolon ';'
      if (directive_handled)
      {
        if (next_token(fp, token, sizeof(token)) && strcmp(token, ";") != 0)
        {
          spydrfly_log("Syntax error: missing ';' after directive\n");
          fclose(fp);
          return -1;
        }
      }
    }
  }
  fclose(fp);
  return 0;
}

int ste_conf(const char *full_path, const char *site_name)
{
  ServerConfig cfg = {0};

  // Assuming you drop your block config into a test file
  if (parse_config(full_path, &cfg) == 0)
  {
    spydrfly_log("Successfully Parsed Config:\n"
      "  Port:        %s\n"
      "  Root:        %s\n"
      "  Server Name: %s\n\n"

      "  SSL info:\n"
      "    fullchain:      %s\n"
      "    privkey:        %s\n"
      "    trusted_cert:   %s\n",
      cfg.port, cfg.root, cfg.domain,

      cfg.fullchain, cfg.privkey, cfg.trusted_cert
    );
  }

  char site_port[10];
  char site_root[128];
  char site_domain[128];

  char dm_fullchain[256];
  char dm_privkey[256];
  char dm_trusted_cert[256];
  
  snprintf(site_port, sizeof(site_port), "%s", cfg.port);
  snprintf(site_root, sizeof(site_root), "%s", cfg.root);
  snprintf(site_domain, sizeof(site_domain), "%s", cfg.domain);

  snprintf(dm_fullchain, sizeof(dm_fullchain), "%s", cfg.fullchain);
  snprintf(dm_privkey, sizeof(dm_privkey), "%s", cfg.privkey);
  snprintf(dm_trusted_cert, sizeof(dm_trusted_cert), "%s", cfg.trusted_cert);

/*
  pid_t pid = fork();

  if (pid == 0)
  {
    setsid();

    if (chdir(site_root) != 0)
    {
      spydrfly_log("Failed to locate site root directory");
      exit(1);
    }

//    site_bind(site_port, site_root, site_domain);

    spydrfly_log("SpyderFly site worker active for %s\n", site_name);
*/
    site_bind(site_port, site_root, site_domain, dm_fullchain, dm_privkey, dm_trusted_cert);
/*
    exit(0);
  } 

  else
  {
    spydrfly_log("Spawned SpyderFly site background process with PID: %d\n", pid);
    
    FILE *f = fopen(pid_file, "a");
    if (f != NULL)
    {
      fprintf(f, "%d\n", pid);
      fclose(f);
      spydrfly_log("Site PID saved to configuration.\n");
    }
    else spydrfly_log("Failed to update site.conf with PID\n");
  }
*/
  return 0;
}