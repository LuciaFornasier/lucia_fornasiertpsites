#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
struct Messaggio {
    char testo[100];
    int vocali;
};

int main() {
    int pipe1[2];
    int pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        char buffer[100];
        struct Messaggio m;
        memset(&m, 0, sizeof(m));
        if (read(pipe1[0], buffer, sizeof(buffer)) <= 0) {
            printf("read figlio");
            exit(1);
        }
        close(pipe1[0]);
        buffer[100 - 1] = '\0';
        strcpy(m.testo, buffer);
        for (int i = 0; m.testo[i] != '\0'; i++) {
            m.testo[i] = toupper((unsigned char)m.testo[i]);
            char c = m.testo[i];
            if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                m.vocali++;
            }
        }
        write(pipe2[1], &m, sizeof(m));
        close(pipe2[1]);
        exit(0);

    } else {
        close(pipe1[0]);
        close(pipe2[1]);

        char buffer[100];
        memset(buffer, 0, sizeof(buffer));
        printf("Inserisci una stringa: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            perror("fgets");
            exit(1);
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        write(pipe1[1], buffer, sizeof(buffer));
        close(pipe1[1]);
        struct Messaggio m;
        if (read(pipe2[0], &m, sizeof(m)) <= 0) {
            perror("read padre");
            exit(1);
        }
        close(pipe2[0]);
        wait(NULL);
        printf("Stringa maiuscola: %s\n", m.testo);
        printf("Numero di vocali: %d\n", m.vocali);
    }

    return 0;
}