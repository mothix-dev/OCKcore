/*
    OCKcore - "yes" utility

    Copyright (c) 2022 Griffin
    Distributed under the terms of the ISC Licence.
*/

#include <stdio.h>

int main(int argc, char **argv) {
    if(argc == 1)
        while(1)
            printf("y\n");
    else
        while(1)
            printf("%s\n", argv[1]);

    return 0;
}
