#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/errno.h>
#include <unistd.h>
#include <limits.h>

const char options[] = "1ha";

static int usage() {
    fprintf(stderr, "usage:\tls <directory> [-1ha]\n");
    exit(EXIT_FAILURE);
}

void ls_(const char *dir, int show_all, int newlines) {
    struct dirent *d;
	DIR *dh = opendir(dir);
    
    if (!dh) {
		if (errno == ENOENT) {
			perror("Directory doesn't exist");
		}
		else {
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE);
	}

    while ((d = readdir(dh)) != NULL) {
		if (!show_all && d->d_name[0] == '.')
			continue;
		printf("%s  ", d->d_name);
		if(newlines) printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int c = 0;
    int all = 0;
    int nl  = 0;
    while((c = getopt(argc, argv, options)) != -1) {
        switch(c) {
            case 'h':
                usage();
            case '1':
                nl = 1;
                break;
            case 'a':
                all = 1;
                break;
            default:
                fprintf(stderr, "ls: invalid option '-%c'\n", optopt);
                usage();
        }
    }

    if(optind != argc - 1) {
        fprintf(stderr, "Invalid number of arguments.");
        return EXIT_FAILURE;
    }
    
    else {
        ls_(argv[optind], all, nl);
    }
}
