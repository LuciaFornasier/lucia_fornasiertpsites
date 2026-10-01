#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    pid_t ritorno = fork();
    if (ritorno == -1) {
        perror("Errore nel fork");
        exit(-1);
    }
    if (!ritorno) {
        sleep(1);
        fprintf(stdout, "Sono il figlio\n");
        exit(42);
    }
    int status;
    pid_t child= wait(&status);
    if (WIFEXITED (status)) {
        int exit_code = WEXITSTATUS (status);
        printf("Figlio di pid %d uscito con codice %d\n", child, exit_code);
    }
    else
        printf("Figlio uscito in modo anomalo");
    return 0;
}