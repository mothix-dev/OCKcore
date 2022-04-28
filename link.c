/*
    OCKcore - POSIX "link" utility
    https://pubs.opengroup.org/onlinepubs/9699919799/utilities/link.html

    Copyright (c) 2022 Thomas Sirack
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *options = "hv";
int verbose_mode = 0;

void help() {
    fprintf(stderr, "Usage: link [-hv] [file1] [file2]\n");
    exit(1);
}

int main(int argc, char **argv) {
    if(argc == 1)
        help();

    int c = 0;
    while((c = getopt(argc, argv, options)) != -1) {
        switch(c) {
            case 'h':
                help();
                /* no break needed as help exits */
            case 'v':
                verbose_mode = 1;
                break;
            default:
                abort();
        }
    }

    int status = link(argv[optind], argv[optind + 1]);
    if(status != 0)
        fprintf(stderr, "link: could not create link: %s\n", strerror(errno));
    else if(verbose_mode)
        fprintf(stderr, "%s -> %s\n", argv[optind], argv[optind + 1]);

    return 0;
}
