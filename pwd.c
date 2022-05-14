/*
    OCKcore - POSIX "pwd" utility
    https://pubs.opengroup.org/onlinepubs/9699919799/utilities/pwd.html

    Copyright (c) 2022 Europa
    Distributed under the terms of the ISC Licence.
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

char *pwd;

int errchk() {

  int ret = 0;

  if(errno != 0) {
    fprintf(stderr, "error: %s\n", strerror(errno));
    ret = errno;
  }
  else {
    printf("%s\n", pwd);
  }

  exit(ret);
}

void help() {

   printf("Open Computing Kit's POSIX-compliant pwd utility\n\n"
   "-L\tShow relative path, including symbolic links.\n"
   "-P\tShow absolute path, following symbolic links.\n"
   "-h\tDisplay this help dialogue.\n"
   "If both -L and -P are given as options, the last option given is acted upon. If no options are given, the pwd utility proceeds as if -L had been specified.\n");
}

int main(int argc, char **argv) {

  int c = 0;
  char opt = 'L';
  const char *name = "PWD";
  while ((c = getopt(argc, argv, "LPh")) != -1) {
    switch(c) {
      case 'L':
        break;
      case 'P':
        opt = 'P'; 
        break;
      case 'h':
        help();
        exit(0);
      default:
        help();
        exit(1);
    }
  }

  if (opt == 'P') {
    pwd = (char *) malloc(PATH_MAX);
    getcwd(pwd, PATH_MAX);
    errchk();
  }
  else {
    pwd = getenv(name); 
    errchk();
  }
}
