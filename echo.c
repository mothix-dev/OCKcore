/*
    OCKcore - POSIX "echo" utility
    https://pubs.opengroup.org/onlinepubs/009604599/utilities/echo.html
    Copyright (c) 2022 VeryCoolMoment
*/
#include <stdio.h>
#include <errno.h>

void error(char error[])
{
   printf("error: %s\n", error);
}
int main( int argc, char *argv[] )  {

   if( argc == 2 ) {
      printf("%s\n", argv[1]);
      return 0;
   }
   else if( argc > 1 ) {
      error("too many arguments given");
   }
   else {
      printf("\n");
   }
}