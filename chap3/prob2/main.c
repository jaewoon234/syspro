#include <stdio.h>
#include <string.h>
#include "copy.h"

#define NUM_SENTENCES 5

int main() {
    char lines[NUM_SENTENCES][MAXLINE];  // 배열로 입력된 문장을 저장
    int lengths[NUM_SENTENCES];  // 입력된 문장의 길이를 저장
    int sentenceCount = 0;

    while (sentenceCount < NUM_SENTENCES) {
        if (fgets(lines[sentenceCount], MAXLINE, stdin) == NULL) {
            fprintf(stderr, "Error reading input.\n");
            return 1;
        }
        lengths[sentenceCount] = strlen(lines[sentenceCount]);
        sentenceCount++;
    }

    // 정렬: 가장 긴 문자열부터 출력
    for (int i = 0; i < NUM_SENTENCES - 1; i++) {
        for (int j = i + 1; j < NUM_SENTENCES; j++) {
            if (lengths[j] > lengths[i]) {
                // 문자열 길이와 내용을 교환
                int tempLength = lengths[i];
                lengths[i] = lengths[j];
                lengths[j] = tempLength;
                
                char tempLine[MAXLINE];
                strcpy(tempLine, lines[i]);
                strcpy(lines[i], lines[j]);
                strcpy(lines[j], tempLine);
            }
        }
    }

    printf("\n");
    for (int i = 0; i < NUM_SENTENCES; i++) {
        printf("%s", lines[i]);
    }

    return 0;
}

