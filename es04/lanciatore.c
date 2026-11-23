#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int pid = fork();

    if (pid < 0) {
        perror("Errore nella fork");
        exit(1);
    } 
    else if (pid == 0) {
        execl("./somma", "somma", "15", "27", NULL);
        perror("Errore nella execl");
        exit(1);
    } 
    else {
        wait(0);
        printf("Calcolo completato\n");
    }

    return 0;
}
