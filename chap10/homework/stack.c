#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top) {
    double data;
    printf("스택에 추가할 값을 입력하세요 (0 이하의 값 입력 시 종료): ");
    
    while (1) {
        scanf("%lf", &data);

        if (data <= 0) {
            break;
        }

        int integerPart = (int)data;

        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        if (newNode == NULL) {
            fprintf(stderr, "메모리 할당 오류\n");
            exit(EXIT_FAILURE);
        }

        newNode->data = integerPart;
        newNode->next = *top;
        *top = newNode;

        printf("현재 스택 내용: ");
        struct node *current = *top;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");

        printf("스택에 추가할 값을 입력하세요 (0 이하의 값 입력 시 종료): ");
    }
}

int pop(struct node **top) {
    if (*top == NULL) {
        fprintf(stderr, "스택이 비어있습니다.\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *top;
    int poppedData = temp->data;

    *top = temp->next;
    free(temp);

    return poppedData;
}

void printStack(struct node *top) {
    if (top == NULL) {
        printf("스택이 비어있습니다.\n");
        return;
    }

    struct node *current = top;
    printf("스택 내용: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct node *top = NULL;

    push(&top);

    printStack(top);

    int poppedValue = pop(&top);
    printf("%d이(가) 스택에서 제거되었습니다.\n", poppedValue);

    printStack(top);

    return 0;
}

