/*
    OCKcore - POSIX "cat" utility

    Copyright (c) 2022 Griffin
    Distributed under the terms of the ISC Licence.
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *options = "hu";
char *present_file = NULL;

void help() {
    fprintf(stderr, "Usage: cat [-hu] [file] ...\n\n");
    fprintf(stderr, "Read files in order and output to standard output.\n"
                    "If no files are specified or file is '-', "
                    "read standard input.\n\n");
    fprintf(stderr, "Options:\n"
                    "\t-h\tdisplay this message\n"
                    "\t-u\t(ignored, present for compatibility only)\n");

    exit(1);
}

void error(const char *filename) {
    fprintf(stderr, "cat: cannot read file %s: %s\n",
            filename, strerror(errno));
}

int main(int argc, char **argv) {
    int c = 0;
    while((c = getopt(argc, argv, options)) != -1) {
        switch(c) {
            case 'h':
                help();
                /* no break needed */
            case 'u':
                break;
            default:
                fprintf(stderr, "cat: invalid option '-%c'\n", optopt);
                help();
        }
    }

    int argv_ind = optind;
    int buffer = 0;
    int fd = 0;

    /* almost certainly no options */
    if(optind == argc) {
        while((read(STDIN_FILENO, &buffer, 1)) != 0)
            write(STDOUT_FILENO, &buffer, 1);
        return 0;
    }

    for(; argv_ind != argc; argv_ind++) {
        /* read stdin explicitly */
        if((strcmp(argv[argv_ind], "-")) == 0) {
            while((read(STDIN_FILENO, &buffer, 1)) != 0)
                write(STDOUT_FILENO, &buffer, 1);
            continue;
        }
        else {
            /* otherwise, we have an actual file to read */
            fd = open(argv[argv_ind], O_RDONLY);
            if(fd == -1) {
                error(argv[argv_ind]);
                return 1;
            }

            while((read(fd, &buffer, 1)) != 0)
                write(STDOUT_FILENO, &buffer, 1);
            continue;
        }
    }

    return 0;
}
