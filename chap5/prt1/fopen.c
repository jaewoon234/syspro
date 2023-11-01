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

void printRequestedLines(char savedText[MAX_LINES][MAX_LENGTH], char *lineNumbers) {
    if (strcmp(lineNumbers, "*") == 0) {
        for (int i = 0; i < MAX_LINES && strlen(savedText[i]) > 0; i++) {
            printf("%s\n", savedText[i]);
        }
    } else {
        char *token = strtok(lineNumbers, ",");
        while (token != NULL) {
            if (strstr(token, "-") != NULL) {
                int start, end;
                sscanf(token, "%d-%d", &start, &end);
                for (int i = start - 1; i < end && i < MAX_LINES; i++) {
                    printf("%s\n", savedText[i]);
                }
            } else {
                int line = atoi(token);
                printf("%s\n", savedText[line - 1]);
            }
            token = strtok(NULL, ",");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
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

    printf("Total Line : %d\n", totalLines);

    char lineNumbers[MAX_LENGTH];
    printf("you can choose 1 ~ 4 Line \n" "pls 'Enter' the line to select : ");
    fgets(lineNumbers, MAX_LENGTH, stdin);

    printRequestedLines(savedText, lineNumbers);

    fclose(file);
    return 0;
}

