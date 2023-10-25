#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _IO_UNBUFFERED 0x0002
#define _IO_LINE_BUF 0x0200

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s stream\n", argv[0]);
        exit(1);
    }

    if (!strcmp(argv[1], "stdin")) {
        fp = stdin;
        printf("Enter one letter:");
        if (getchar() == EOF)
            perror("getchar");
    } else if (!strcmp(argv[1], "stdout"))
        fp = stdout;
    else if (!strcmp(argv[1], "stderr"))
        fp = stderr;
    else if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        exit(1);
    } else if (getc(fp) == EOF)
        perror("getc");

    printf("Stream = %s, ", argv[1]);

    // Check buffering status
    int mode;
    if (setvbuf(fp, NULL, _IONBF, 0) == 0) {
        printf("Unbuffered");
    } else if (setvbuf(fp, NULL, _IOLBF, BUFSIZ) == 0) {
        printf("Line buffered");
    } else if (setvbuf(fp, NULL, _IOFBF, BUFSIZ) == 0) {
        printf("Fully buffered");
    } else {
        printf("Unknown");
    }

    printf(", Buffer size = %d\n", BUFSIZ);
    exit(0);
}

