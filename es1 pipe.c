#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2] ;
    int somma=0;
    int sommad=0;
    int a[10]={10,5,4,6,8,12,7,8,9,60};
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

        for (int i=0;i<10;i++) {
            if (a[i]%2==0) {
                somma+=a[i];
            }
        }
        write(fd[1], &somma, sizeof(somma));
        close(fd[1]);
        exit(0);
    }
    for (int i=0;i<10;i++) {
        if (a[i]%2!=0) {
            sommad+=a[i];
        }
    }
    wait(NULL);
    int bytes = read(fd[0], &somma, sizeof(somma));
    printf("%d\n", somma);
    close(fd[0]);
    printf("%d\n", sommad);
    printf("%d\n", somma+sommad);
    return 0;
}
