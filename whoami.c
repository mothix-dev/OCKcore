/*
    OCKcore - POSIX "whoami" utility

    Copyright (c) 2022 Lilly Cham
    Distributed under the terms of the ISC Licence.
*/

#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	register struct passwd *pw;
  register uid_t uid;
	uid = geteuid ();
  pw = getpwuid (uid);
  if (pw)
    {
      printf("%s", pw->pw_name);
      exit(0);
    }

	perror("whoami: cannot find username corresponding to uid\n");
	exit(-1);
}
