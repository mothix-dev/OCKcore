/*
    OCKcore - POSIX "tty" utility
    https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/utilities/tty.html

    Copyright (c) 2022 Europa
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
  
  char* tty = ttyname(STDIN_FILENO);

  if(!tty && errno == ENOTTY) {
    fprintf(stderr, "not a tty: %s\n", strerror(errno));
    return 1;
  }
  else if (tty) {
    printf("%s\n", tty);
    return 0;
  }
  else {
    fprintf(stderr, "error: %s\n", strerror(errno));
    return errno;
  }
}
