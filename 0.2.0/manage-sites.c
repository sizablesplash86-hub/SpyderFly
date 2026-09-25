#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STR_LEN 256

char options;
//char options[STR_LEN];

// this will eventually become the spyderfly binary. Change it to work with --example

int main()
{
  printf("What would you like to do?\n\n 1) Manage sites\n 2) run auto config\n 3) test sites\n Please choose: ");
  scanf(" %c", &options);

  if (options == 1)
  {
    char sites;
    printf("What would you like to do?\n\n 1) list enabled sites\n 2) list disabled sites\n 3) disable site\n 4) enable site\n 5) delete site\nPlease pick: ");
    scanf(" %c", &sites);
  }
}