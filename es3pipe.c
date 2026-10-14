#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
int main() {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }
    pid_t pidB = fork();
    if (pidB == -1) {
        perror("fork B");
        exit(1);
    }

    if (pidB == 0) {
        close(pipe1[1]);
        close(pipe2[0]);

        int n;
        while (read(pipe1[0], &n, sizeof(n)) > 0) {
            if (n < 50) {
                continue;
            }
            int quadrato = n * n;
            write(pipe2[1], &quadrato, sizeof(quadrato));
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }

    pid_t pidC = fork();
    if (pidC == -1) {
        perror("fork C");
        exit(1);
    }

    if (pidC == 0) {
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);

        int q;
        long somma = 0;
        int conteggio = 0;

        printf("C: quadrati ricevuti:\n");
        while (read(pipe2[0], &q, sizeof(q)) > 0) {
            printf("  %d\n", q);
            somma += q;
            conteggio++;
        }
        close(pipe2[0]);

        if (conteggio > 0) {
            printf("C: media aritmetica = %.2f (su %d numeri)\n",
                   (double)somma / conteggio, conteggio);
        } else {
            printf("C: nessun numero >= 50, media non calcolabile\n");
        }
        exit(0);
    }
    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe2[1]);

    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        int n = rand() % 100 + 1;
        write(pipe1[1], &n, sizeof(n));
    }
    close(pipe1[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}