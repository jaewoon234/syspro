#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [OPTION] File1 [File2 ...]\n", argv[0]);
        return 1;
    }

    int print_line_numbers = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        print_line_numbers = 1;
        i = 2;
    } else {
        i = 1;
    }

    for (; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            fprintf(stderr, "File %s Open Error\n", argv[i]);
            continue;
        }

        int line_number = 1;
        int c;
	int start_of_line = 1;

        while ((c = getc(fp)) != EOF) {
            if (print_line_numbers && start_of_line) {
                printf("%3d: ", line_number);
                line_number++;
		start_of_line = 0;
            }
            putc(c, stdout);

            if (c == '\n') {
                start_of_line = 1;
            }
        }

        fclose(fp);
    }

    return 0;
}

