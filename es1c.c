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

        for (int i=1;i<=5;i++) {
            sleep(1);
            fprintf(stdout, "%d\n", i);
        }
        exit(42);
    }
    wait(NULL);
    for (int i=6;i<=10;i++) {
        fprintf(stdout, "%d\n", i);
    }
    return 0;
}