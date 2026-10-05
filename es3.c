#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("Errore nel fork");
        exit(0);
    }
    if (pid1 == 0) {
        pid_t pid2 = fork();
        if (pid2 == -1) {
            perror("Errore nel fork");
            exit(0);
        }
        if (pid2 == 0) {
            printf("Sono il nipote\n");
            exit(0);
        }
        int status;
        pid_t child = wait(&status);
        if (WIFEXITED(status)) {
            printf("Sono il padre: il nipote di pid %d \n", child );
        }
        else
            printf("Sono il padre: il nipote è uscito in modo anomalo\n");
        exit(0);
    }
    int status;
    pid_t child = wait(&status);
    if (WIFEXITED(status)) {
        printf("Sono il nonno: il padre di pid %d \n", child);
    }
    else
        printf("Sono il nonno: il padre è uscito in modo anomalo\n");
    return 0;
}