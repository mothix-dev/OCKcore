/*
    OCKcore - "yes" utility

    Copyright (c) 2022 Griffin, Lilly Cham
    Distributed under the terms of the ISC Licence.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 8192

int main(int argc, char **argv) {
    char * buf     = malloc(BUFSIZE);
    int    bufused = 0;
    char * yes;
    int    len;

    if (argc == 1) {
        len = sizeof "y\n";
        yes = malloc(sizeof "y\n");
        strcpy(yes, "y\n");
    }

    else if (argc <= 2) {
        len = sizeof argv[1] + 2;
        yes = malloc(len);
        strcpy(yes, argv[1]);
        strcat(yes, "\n");
    }

    while (bufused < BUFSIZE) {
        memcpy(buf+bufused, yes, len);
        bufused += len;
    }

    while(write(1, buf, BUFSIZE));

    return 0;
}
