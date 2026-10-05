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
            printf("%d è primo\n", n);
        else if (n%2 == 0) {
            printf("%d è pari\n", n);
        }else {
            printf("%d è dispari\n", n);
        }
        exit(42);
    }
    wait(NULL);
    printf("Finito\n");
}
