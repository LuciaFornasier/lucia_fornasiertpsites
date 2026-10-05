#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t ritorno = fork();
    int n;

    if (ritorno == -1) {
        perror("Errore nel fork");
        exit(-1);
    }
    if (!ritorno) {
        int risultato;
        printf("Scrivi un numero");
        scanf("%d", &n);
        int primo = 1;
        if (n < 2)
            primo = 0;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                primo = 0;
                break;
            }
        }
        if (primo)
            risultato = 1;
        else if (n%2 == 0) {
            risultato = 2;
        }else {
            risultato=3;
        }
        exit(risultato);
    }
    int status;
    pid_t child= wait(&status);
    if (WIFEXITED (status)) {
        int risultato= WEXITSTATUS (status);
        if (risultato==1)
            printf("è primo\n");
        else if (risultato==2) {
            printf("è pari\n");
        }else if (risultato==3) {
            printf("è dispari\n");
        }else
            printf("Errore");
    }
    else
        printf("Figlio uscito in modo anomalo");

    printf("Finito\n");
}
