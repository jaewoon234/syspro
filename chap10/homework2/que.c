#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*tail == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }

}
int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        fprintf(stderr, "큐가 비어있습니다.\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *head;
    int deletedData = temp->data;

    *head = temp->next;
    free(temp);

    if (*head == NULL) {
        *tail = NULL;
    }

    return deletedData;
}

void printQueue(struct node *head) {
    if (head == NULL) {
        printf("큐가 비어있습니다.\n");
        return;
    }

    struct node *current = head;
    printf("큐 내용: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;

    int value;
    while (1) {
       printf(" ");
        if (scanf("%d", &value) <= 0) {
            break;
        }

        addq(&head, &tail, value);
    }

    printQueue(head);

    return 0;
}

