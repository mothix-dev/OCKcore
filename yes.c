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
            puts(argv[1]);

    fflush(stdout);
    return 0;
}
