/*
    OCKcore - POSIX "uname" utility
    https://pubs.opengroup.org/onlinepubs/9699919799/utilities/uname.html

    Copyright (c) 2022 Europa
*/

#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <stdlib.h>

void help() {
  printf("Open Computing Kit's POSIX-compliant system name utility\n\n"
   "-a\tBehave as though all of the options -mnrsv were specified.\n"
   "-m\tWrite the name of the hardware type on which the system is running to standard output.\n"
   "-n\tWrite the name of this node within an implementation-defined communications network.\n"
   "-r\tWrite the current release level of the operating system implementation.\n"
   "-s\tWrite the name of the implementation of the operating system.\n"
   "-v\tWrite the current version level of this release of the operating system implementation.\n"
   "-h\tDisplay this help listing.\n\n"
   "If no options are specified, the uname utility shall write the operating system name, as if the -s option had been specified.\n");
  exit(0);
}

int main(int argc, char **argv) {
  struct utsname sysInfo;
  uname(&sysInfo);
  int c;
  int opt_a = 0;
  int opt_m = 0;
  int opt_n = 0;
  int opt_r = 0;
  int opt_s = 0;
  int opt_v = 0;
  while ((c = getopt(argc, argv, "amnrsvh")) != -1) {
    switch(c) {
      case 'a':
        opt_a = 1;
        break;
      case 'm':
        opt_m = 1;
        break;
      case 'n':
        opt_n = 1;
        break;
      case 'r':
        opt_r = 1;
        break;
      case 's':
        opt_s = 1;
        break;
      case 'v':
        opt_v = 1;
        break;
      case 'h':
        help();
        // No break because 'exit' exists in help() 
      default:
        printf("\nFor a list of possible options, please run 'uname -h'\n");
        exit(1);
    }
  }
  if (opt_a) {
    printf("%s %s %s %s %s\n", sysInfo.sysname, sysInfo.nodename, sysInfo.release, sysInfo.version, sysInfo.machine);
    exit(0);
    // Exit here to prevent duplicate information being printed
  }
  if (opt_m) {
    printf("%s ", sysInfo.machine);
  }
  if (opt_n) {
    printf("%s ", sysInfo.nodename);
  }
  if (opt_r) {
    printf("%s ", sysInfo.release);
  }
  if (opt_s) {
    printf("%s ", sysInfo.sysname);
  }
  if (opt_v) {
    printf("%s ", sysInfo.version);
  }
  else {
    printf("%s ", sysInfo.sysname);
  }
  printf("\n"); 
  exit(0);
}
