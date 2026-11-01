// this is a concept to handle the NGINX config import

#include "core.h"

/*    // noting this so the compiler ignores it for now

// Pseudo-code concept for parsing tokens
void parse_config(TokenList *tokens, NginxConfig *config)
{
  int current_server = -1;

  for (int i = 0; i < tokens->count; i++)
  {
    if (strcmp(tokens[i].val, "server") == 0 && strcmp(tokens[i+1].val, "{") == 0)
    {
      current_server = config->server_count++;
      // Initialize new server block
    } 
    else if (strcmp(tokens[i].val, "listen") == 0) 
    {
      config->servers[current_server].port = atoi(tokens[i+1].val);
    }
    else if (strcmp(tokens[i].val, "root") == 0)
    {
      strcpy(config->servers[current_server].root, tokens[i+1].val);
    }
    // Handle brackets, locations, etc.
  }
}

*/