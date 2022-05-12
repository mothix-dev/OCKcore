/*
    OCKcore - POSIX "link" utility
    https://pubs.opengroup.org/onlinepubs/9699919799/utilities/link.html

    Copyright (c) 2022 Griffin
    Distributed under the terms of the ISC Licence.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *options = "hv";
int verbose_mode = 0;

void help() {
    fprintf(stderr, "Usage: link [-hv] file1 file2\n\n");
    fprintf(stderr, "Create a hard link from file1 to file2.\n\n");
    fprintf(stderr, "Options:\n"
                    "\t-h\tdisplay this message\n"
                    "\t-v\tactivate verbose mode\n");
    exit(1);
}

int main(int argc, char **argv) {
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
                fprintf(stderr, "link: invalid option '-%c'\n", optopt);
                help();
        }
    }

    if(!argv[optind] || !argv[optind + 1]) {
        fprintf(stderr, "link: missing operand\n");
        help();
    }

    int status = link(argv[optind], argv[optind + 1]);
    if(status != 0) {
        fprintf(stderr, "link: could not create link: %s\n", strerror(errno));
        return 1;
    }
    else if(verbose_mode)
        fprintf(stderr, "%s -> %s\n", argv[optind], argv[optind + 1]);

    return 0;
}
