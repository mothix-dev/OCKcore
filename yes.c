/*
    OCKcore - "yes" utility

    Copyright (c) 2022 Griffin
    Distributed under the terms of the ISC Licence.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 8192

int main(int argc, char **argv) {
    char *buf   = malloc(BUFSIZE);
    int bufused = 0;

    if (argc <= 1) {
        char yes[]  = {'y', '\n'};
        while (bufused < BUFSIZE) {
            memcpy(buf+bufused, yes, sizeof(yes));
            bufused += sizeof(yes);
        }
        while(write(1, buf, BUFSIZE));
    }

    else if (argc <= 2) {
        while (1)
            puts(argv[1]);
    }

    return 0;
}
