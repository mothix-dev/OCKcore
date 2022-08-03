/*
    OCKcore - "yes" utility
    Copyright (c) 2022 Griffin
    Distributed under the terms of the ISC Licence.
*/

#include <stdio.h>

int main(int argc, char **argv) {
    if(argc == 1)
        while(1)
            puts("y");
    else
        while(1)
            for (int i=1; i<argc; i++)
                puts(argv[i]);

    fflush(stdout);
    return 0;
}
