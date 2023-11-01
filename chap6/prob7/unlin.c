#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (access(argv[1], F_OK) == -1) {
        perror("File access error");
        return 1;
    }

    if (unlink(argv[1]) == -1) {
        perror("Error deleting the file");
        return 1;
    }

    printf("%s deleted successfully.\n", argv[1]);
    return 0;
}

