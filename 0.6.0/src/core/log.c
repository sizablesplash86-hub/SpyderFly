#include "core.h"

void log_timestamp(FILE *log, const char *format, va_list args)
{
  time_t now = time(NULL);
  char *timestamp = ctime(&now);
  timestamp[strcspn(timestamp, "\n")] = 0;

  vprintf(format, args);
  printf("\n");

  fprintf(log, "[%s] ", timestamp);
  vfprintf(log, format, args);
  fprintf(log, "\n");
}

void spydrfly_log(const char *format, ...)
{
  char log_file[256];

  time_t raw_time = time(NULL);
  struct tm *info = localtime(&raw_time);
  
  char date[128];
  strftime(date, sizeof(date), "%Y-%m-%d", info);

  snprintf(log_file, sizeof(log_file), "%s/%s.log", logs, date);
  FILE *log = fopen(log_file, "a");
  if (log == NULL)
  {
    printf("Failed to open log file\n");
    return;
  }

  va_list args;
  va_start(args, format);
  log_timestamp(log, format, args);
  va_end(args);

  fclose(log);
}