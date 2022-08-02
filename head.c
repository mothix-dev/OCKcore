/*
    OCKcore - "head" utility

    Copyright (c) 2022 Lilly Cham
    Distributed under the terms of the ISC Licence.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINE_LENGTH 4096
#define BUFFER_LENGTH 4096

static void usage() {
	fprintf(stderr, "usage: head <file> [lines]\n");
    fprintf(stderr, "to read from stdin, use <file> arg -\n");
	exit(-1);
}

int main(int argc, char * argv[]) {
    FILE* fp;
    char* line = malloc(BUFFER_LENGTH);

    int c = 0;
    long line_max = 10;

    if (argc < 2)
        usage();

    else if (argc < 3)
        line_max = strtol(argv[1], NULL, 10);

    // open file
    fp = (strcmp(argv[1], "-") == 0) ? stdin : fopen(argv[1],"r");
    if (fp == NULL) {
        fprintf(stderr, "%s file can not be opened\n", argv[1]);
        exit(1);
    }

    // read lines from file one by one
    while (fgets(line, BUFFER_LENGTH, fp)) {
        c++;
        if (c > line_max)
            break;
        printf("%s",line); 
        fflush(stdout);
    }

    // teardown
    fclose(fp);
    free(line);
    return 0;
}
