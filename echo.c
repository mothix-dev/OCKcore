
#include <stdio.h>

void error(char error[])
{
   printf("error: %s\n", error);
}
int main( int argc, char *argv[] )  {

   if( argc == 2 ) {
      printf("%s\n", argv[1]);
   }
   else if( argc > 2 ) {
      error("too many arguments given");
   }
   else {
      error("no argument given or unknown error");
   }
}