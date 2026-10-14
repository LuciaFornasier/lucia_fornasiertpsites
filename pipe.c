#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main() {
    int fd[2] ;
    if (pipe(fd) == -1) {
        fprintf(stderr, "Error pipe ");
        exit(-1);
    }
    pid_t ritorno = fork();
    if (ritorno == -1) {
        fprintf(stderr, "Error fork ");
        exit(-2);
    }
    if (!ritorno) {
        close(fd[0]);
        char msg[]="Ciao";

        write(fd[1], msg, sizeof(msg));
        close(fd[1]);
    }
    char buffer[100];
    int bytes = read(fd[0], buffer, sizeof(buffer));
    printf("%s", buffer);

}