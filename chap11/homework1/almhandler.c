#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void alarmHandler(int signo);

int main() {
    struct sigaction newact;
    
    newact.sa_handler = alarmHandler;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    
    if (sigaction(SIGALRM, &newact, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    
    alarm(5);
    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }
    printf("end\n");
    
    return 0;
}

void alarmHandler(int signo) {
    printf("Wake up\n");
    exit(0);
}

