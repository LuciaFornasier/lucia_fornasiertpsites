#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Errore nel fork");
            exit(0);
        }
        if (pid == 0) {
            printf("Sono il figlio %d\n", i + 1);
            sleep(2);
            exit(1);
        }

        printf("[Padre] Creato figlio %d con PID %d\n", i + 1, pid);
    }
    for (int i = 0; i < 3; i++) {
        pid_t child_pid = wait(NULL);
        if (child_pid == -1) {
            perror("Errore nella wait");
            break;
        }
    }

    printf("[Padre] Tutti i figli hanno terminato.\n");
    return 0;
}