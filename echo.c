/*
    OCKcore - POSIX "echo" utility
    https://pubs.opengroup.org/onlinepubs/009604599/utilities/echo.html

    Copyright (c) 2022 VeryCoolMoment
    Distributed under the terms of the ISC Licence.
*/
#include <stdio.h>
#include <errno.h>

int main( int argc, char *argv[] )  {

   if( argc == 2 ) {
      printf("%s\n", argv[1]);
      return 0;
   }
   else if( argc > 1 ) {
      int counter;
	    for(counter=1; counter<argc; counter++)
            if(counter == 1)
            {
                printf("%s",argv[counter]);
            }
            else
            {
                printf("%s%s", " ",argv[counter]);
            } 
   }
   else {
      printf("\n");
   }
}