#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char comando[50];
    int pid, status;

    while (1) {
        // 1. Stampa il prompt e legge il comando
        printf("\nmia_shell> ");
        scanf("%s", comando);

        // 2. Se l'utente scrive "exit", il programma termina
        if (strcmp(comando, "exit") == 0) {
            printf("Uscita dalla shell.\n");
            break;
        }

        // 3. Creazione del processo figlio
        pid = fork();

        if (pid < 0) {
            perror("Errore nella fork");
            exit(1);
        } 
        else if (pid == 0) {
            // PROCESSO FIGLIO: esegue il comando
            // execlp cerca il comando nelle cartelle di sistema (es. /bin)
            execlp(comando, comando, NULL);

            // Se arriva qui significa che la execlp ha fallito
            perror("Errore exec");
            exit(1);
        } 
        else {
            // PROCESSO PADRE: attende la fine del figlio
            wait(&status);

            // Controlla se il figlio ha restituito un errore
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                printf("Il comando e' terminato con errore (codice %d)\n", WEXITSTATUS(status));
            }
        }
    }

    return 0;
}
