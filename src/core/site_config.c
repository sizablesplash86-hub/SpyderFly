/*
#include "../spyderfly.h"

typedef struct
{
  char domain[128];
  char port[10];
  char root[128];
  char index[128];

  // SSL Directives
  char fullchain[256];
  char privkey[256];
  char trusted_cert[256];
} ServerConfig;

int next_token(FILE *fp, char *buf, size_t max_len)
{
  int c;
  size_t len = 0;

  while ((c = fgetc(fp)) != EOF)
  {
    if (c == '#')
    {
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

  c = fgetc(fp);

  if (c == '{' || c == '}' || c == ';')
  {
    buf[0] = (char)c;
    buf[1] = '\0';
    return 1;
  }

  if (c == '"')
  {
    while ((c = fgetc(fp)) != EOF)
    {
      if (c == '"')
      {
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
      if (strcmp(token, "}") == 0)
      {
        inside_server_block = 0;
        break;
      }

      int directive_handled = 1;

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
      else if (strcmp(token, "index") == 0)
      {
        if (next_token(fp, token, sizeof(token)))
        {
          snprintf(config->index, sizeof(config->index), "%s", token);
        }
      }
      else
      {
        directive_handled = 0;
        char skip_token[256];
        while (next_token(fp, skip_token, sizeof(skip_token)))
        {
          if (strcmp(skip_token, ";") == 0) break;
        }
      }

      if (directive_handled)
      {
        if (next_token(fp, token, sizeof(token)) && strcmp(token, ";") != 0)
        {
          printf("Syntax error: missing ';' after directive\n");
          fclose(fp);
          return -1;
        }
      }
    }
    else
    {
      printf("Could not find server block\n");
      return -1;
    }
  }
  fclose(fp);
  return 0;
}

int ste_conf(const char *full_path, const char *site_name)
{
  ServerConfig cfg = {0};

  if (parse_config(full_path, &cfg) == 0)
  {
    printf("Successfully Parsed Config:\n"
      "  Port:        %s\n"
      "  Root:        %s\n"
      "  Server Name: %s\n\n"

      "  Index:       %s\n\n"

      "  SSL info:\n"
      "    fullchain:      %s\n"
      "    privkey:        %s\n"
      "    trusted_cert:   %s\n",
      cfg.port, cfg.root, cfg.domain, cfg.index,

      cfg.fullchain, cfg.privkey, cfg.trusted_cert
    );
  }

  else
  {
    printf("Error in site config\n");
    return -1;
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

  pid_t pid = fork();

  if (pid < 0)
  {
    printf("Failed to create fork\n");
    return -1;
  }


  TODO: // Something is wrong with the fork
  if (pid == 0)
  {
//    setsid();

    if (chdir(site_root) != 0)
    {
      printf("Failed to locate site root directory\n");
      exit(1);
    }

    printf("SpyderFly site worker active for %s\n", site_name);

    site_bind(site_name, site_port, site_root, site_domain, dm_fullchain, dm_privkey, dm_trusted_cert);

    exit(0);
  } 

  else
  {
    printf("Spawned SpyderFly site background process with PID: %d\n", pid);
    
    FILE *f = fopen(pid_file, "a");
    if (f != NULL)
    {
      fprintf(f, "%d\n", pid);
      fclose(f);
      printf("Site PID saved to configuration.\n");
    }
    else printf("Failed to update site.conf with PID\n");
  }

  return 0;
}
*/



#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <dirent.h>
#include <ifaddrs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define NGX_CONF_BUFFER  4096

#define ngx_file_size(sb)        (sb)->st_size
#define ngx_memmove(dst, src, n)  (void) memmove(dst, src, n)

typedef intptr_t        ngx_int_t;
typedef uintptr_t       ngx_uint_t;
typedef intptr_t        ngx_flag_t;


typedef struct ngx_buf_s  ngx_buf_t;

typedef struct ngx_module_s          ngx_module_t;
typedef struct ngx_conf_s            ngx_conf_t;
typedef struct ngx_cycle_s           ngx_cycle_t;
typedef struct ngx_pool_s            ngx_pool_t;
typedef struct ngx_chain_s           ngx_chain_t;
typedef struct ngx_log_s             ngx_log_t;
typedef struct ngx_open_file_s       ngx_open_file_t;
typedef struct ngx_command_s         ngx_command_t;
typedef struct ngx_file_s            ngx_file_t;
typedef struct ngx_event_s           ngx_event_t;
typedef struct ngx_event_aio_s       ngx_event_aio_t;
typedef struct ngx_connection_s      ngx_connection_t;
typedef struct ngx_thread_task_s     ngx_thread_task_t;
typedef struct ngx_ssl_s             ngx_ssl_t;
typedef struct ngx_ssl_cache_s       ngx_ssl_cache_t;
typedef struct ngx_proxy_protocol_s  ngx_proxy_protocol_t;
typedef struct ngx_quic_stream_s     ngx_quic_stream_t;
typedef struct ngx_ssl_connection_s  ngx_ssl_connection_t;
typedef struct ngx_udp_connection_s  ngx_udp_connection_t;

typedef int                      ngx_fd_t;
typedef struct stat              ngx_file_info_t;

typedef struct {
    size_t      len;
    u_char     *data;
} ngx_str_t;

struct ngx_file_s {
    ngx_fd_t                   fd;
    ngx_str_t                  name;
    ngx_file_info_t            info;

    off_t                      offset;
    off_t                      sys_offset;

    ngx_log_t                 *log;

#if (NGX_THREADS || NGX_COMPAT)
    ngx_int_t                (*thread_handler)(ngx_thread_task_t *task,
                                               ngx_file_t *file);
    void                      *thread_ctx;
    ngx_thread_task_t         *thread_task;
#endif

#if (NGX_HAVE_FILE_AIO || NGX_COMPAT)
    ngx_event_aio_t           *aio;
#endif

    unsigned                   valid_info:1;
    unsigned                   directio:1;
};

typedef char *(*ngx_conf_handler_pt)(ngx_conf_t *cf,
    ngx_command_t *dummy, void *conf);

struct ngx_command_s {
    ngx_str_t             name;
    ngx_uint_t            type;
    char               *(*set)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
    ngx_uint_t            conf;
    ngx_uint_t            offset;
    void                 *post;
};

typedef struct {
    ngx_file_t            file;
    ngx_buf_t            *buffer;
    ngx_buf_t            *dump;
    ngx_uint_t            line;
} ngx_conf_file_t;

typedef struct {
    void        *elts;
    ngx_uint_t   nelts;
    size_t       size;
    ngx_uint_t   nalloc;
    ngx_pool_t  *pool;
} ngx_array_t;

struct ngx_conf_s {
    char                 *name;
    ngx_array_t          *args;

    ngx_cycle_t          *cycle;
    ngx_pool_t           *pool;
    ngx_pool_t           *temp_pool;
    ngx_conf_file_t      *conf_file;
    ngx_log_t            *log;

    void                 *ctx;
    ngx_uint_t            module_type;
    ngx_uint_t            cmd_type;

    ngx_conf_handler_pt   handler;
    void                 *handler_conf;
};

typedef void *            ngx_buf_tag_t;
struct ngx_buf_s {
    u_char          *pos;
    u_char          *last;
    off_t            file_pos;
    off_t            file_last;

    u_char          *start;         /* start of buffer */
    u_char          *end;           /* end of buffer */
    ngx_buf_tag_t    tag;
    ngx_file_t      *file;
    ngx_buf_t       *shadow;


    /* the buf's content could be changed */
    unsigned         temporary:1;

    /*
     * the buf's content is in a memory cache or in a read only memory
     * and must not be changed
     */
    unsigned         memory:1;

    /* the buf's content is mmap()ed and must not be changed */
    unsigned         mmap:1;

    unsigned         recycled:1;
    unsigned         in_file:1;
    unsigned         flush:1;
    unsigned         sync:1;
    unsigned         last_buf:1;
    unsigned         last_in_chain:1;

    unsigned         last_shadow:1;
    unsigned         temp_file:1;

    /* STUB */ int   num;
};




static ngx_int_t ngx_conf_read_token(ngx_conf_t *cf)
{
  u_char      *start, ch, *src, *dst;
  off_t        file_size;
  size_t       len;
  ssize_t      n, size;
  ngx_uint_t   found, need_space, last_space, sharp_comment, variable;
  ngx_uint_t   quoted, s_quoted, d_quoted, start_line;
  ngx_str_t   *word;
  ngx_buf_t   *b, *dump;

  found = 0;
  need_space = 0;
  last_space = 1;
  sharp_comment = 0;
  variable = 0;
  quoted = 0;
  s_quoted = 0;
  d_quoted = 0;

  cf->args->nelts = 0;
  b = cf->conf_file->buffer;
  dump = cf->conf_file->dump;
  start = b->pos;
  start_line = cf->conf_file->line;

  file_size = ngx_file_size(&cf->conf_file->file.info);

  for ( ;; )
  {
    if (b->pos >= b->last)
    {
      if (cf->conf_file->file.offset >= file_size)
      {
        if (cf->args->nelts > 0 || !last_space)
        {
          if (cf->conf_file->file.fd == -1)
          {
            printf("unexpected end of parameter, " "expecting \";\"\n");
//            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "unexpected end of parameter, " "expecting \";\"");
            return -1;
          }

          printf("unexpected end of file, " "expecting \";\" or \"}\"\n");
//          ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "unexpected end of file, " "expecting \";\" or \"}\"");
          return -1;
        }

        return 3;
      }

      len = b->pos - start;

      if (len == NGX_CONF_BUFFER)
      {
        cf->conf_file->line = start_line;

        if (d_quoted)
        {
          ch = '"';

        } 
        
        else if (s_quoted) ch = '\'';
        
        else
        {
          printf("too long parameter \"%*s...\" started\n", (size_t) 10, start);
//          ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "too long parameter \"%*s...\" started", (size_t) 10, start);
          return -1;
        }

        printf("too long parameter, probably " "missing terminating \"%c\" character\n", ch);
//        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "too long parameter, probably " "missing terminating \"%c\" character", ch);
        return -1;
      }

      if (len) ngx_memmove(b->start, start, len);

      size = (ssize_t) (file_size - cf->conf_file->file.offset);

      if (size > b->end - (b->start + len)) size = b->end - (b->start + len);

 
      //   nginx/src/os/unix/ngx_files.c  line 31
      n = ngx_read_file(&cf->conf_file->file, b->start + len, size, cf->conf_file->file.offset);

      if (n == -1) return -1;

      if (n != size)
      {
        printf(" returned " "only %z bytes instead of %z\n", n, size);
//        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, ngx_read_file_n " returned " "only %z bytes instead of %z", n, size);
        return -1;
      }

      b->pos = b->start + len;
      b->last = b->pos + n;
      start = b->start;

      TODO: // not right either
      if (dump) dump->last = ngx_cpymem(dump->last, b->pos, size);
    }

    ch = *b->pos++;

    if (ch == LF)
    {
      cf->conf_file->line++;

      if (sharp_comment) sharp_comment = 0;
    }

    if (sharp_comment) continue;

    if (quoted)
    {
      quoted = 0;
      continue;
    }

    if (need_space)
    {
      if (ch == ' ' || ch == '\t' || ch == CR || ch == LF)
      {
        last_space = 1;
        need_space = 0;
       continue;
      }

      if (ch == ';') return 0;

      if (ch == '{') return 1;

      if (ch == ')')
      {
        last_space = 1;
        need_space = 0;
      }
      else
      {
        printf("unexpected \"%c\"\n", ch);
//        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "unexpected \"%c\"", ch);
        return -1;
      }
    }

    if (last_space)
    {
      start = b->pos - 1;
      start_line = cf->conf_file->line;

      if (ch == ' ' || ch == '\t' || ch == CR || ch == LF) continue;

      switch (ch)
      {
        case ';':
        case '{':
          if (cf->args->nelts == 0)
          {
            printf("unexpected \"%c\"\n", ch);
//            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "unexpected \"%c\"", ch);
            return -1;
          }

          if (ch == '{') return 1;

          return 0;

        case '}':
          if (cf->args->nelts != 0)
          {
            printf("unexpected \"}\"\n");
//            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "unexpected \"}\"");
            return -1;
          }

          return 2;

        case '#':
          sharp_comment = 1;
          continue;

        case '\\':
          quoted = 1;
          last_space = 0;
          continue;

        case '"':
          start++;
          d_quoted = 1;
          last_space = 0;
          continue;

        case '\'':
          start++;
          s_quoted = 1;
          last_space = 0;
          continue;

        case '$':
          variable = 1;
          last_space = 0;
          continue;

        default:
          last_space = 0;
      }

    } 
    
    else
    {
      if (ch == '{' && variable) continue;

      variable = 0;

      if (ch == '\\')
      {
        quoted = 1;
        continue;
      }

      if (ch == '$')
      {
        variable = 1;
        continue;
      }

      if (d_quoted)
      {
        if (ch == '"')
        {
          d_quoted = 0;
          need_space = 1;
          found = 1;
        }

      } 
      
      else if (s_quoted)
      {
        if (ch == '\'')
        {
          s_quoted = 0;
          need_space = 1;
          found = 1;
        }

      }
      
      else if (ch == ' ' || ch == '\t' || ch == CR || ch == LF || ch == ';' || ch == '{')
      {
        last_space = 1;
        found = 1;
      }

      if (found)
      {
        word = ngx_array_push(cf->args);
        if (word == NULL) return -1;

        word->data = ngx_pnalloc(cf->pool, b->pos - 1 - start + 1);
        if (word->data == NULL) return -1;

        for (dst = word->data, src = start, len = 0; src < b->pos - 1; len++)
        {
          if (*src == '\\')
          {
            switch (src[1])
            {
              case '"':
              case '\'':
              case '\\':
                src++;
                break;

              case 't':
                *dst++ = '\t';
                src += 2;
                continue;

              case 'r':
                *dst++ = '\r';
                src += 2;
                continue;

              case 'n':
                *dst++ = '\n';
                src += 2;
                continue;
            }

          }
          *dst++ = *src++;
        }
        
        *dst = '\0';
        word->len = len;

        if (ch == ';') return NULL;

        if (ch == '{') return 1;

        found = 0;
      }
    }
  }
}