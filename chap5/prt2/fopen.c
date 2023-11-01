#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

void readLines(FILE *file, char savedText[MAX_LINES][MAX_LENGTH], int *totalLines) {
    int line = 0;
    int index = 0;
    char c;

    while ((c = fgetc(file)) != EOF && line < MAX_LINES) {
        if (c != '\n' && index < MAX_LENGTH - 1) {
            savedText[line][index++] = c;
        } else {
            savedText[line][index] = '\0';
            line++;
            index = 0;
            (*totalLines)++;
        }
    }
}

void printReversedLines(char savedText[MAX_LINES][MAX_LENGTH], int totalLines) {
    for (int i = totalLines - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(" 프로그램이름 파일이름\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("열수없습니다.\n");
        return 1;
    }

    char savedText[MAX_LINES][MAX_LENGTH] = {0};
    int totalLines = 0;
    readLines(file, savedText, &totalLines);

    printReversedLines(savedText, totalLines);

    fclose(file);
    return 0;
}

