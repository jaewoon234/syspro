#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("test.txt", "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }
    fclose(file);

    system("ls -ls test.txt");

    system("stat test.txt");

    system("ls -i test.txt");

    printf("\nBefore touch:\n");
    system("ls -l test.txt");

    system("touch test.txt");

    printf("\nAfter touch:\n");
    system("ls -l test.txt");

    return 0;
}

