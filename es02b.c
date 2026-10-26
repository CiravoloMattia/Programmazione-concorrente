#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Il processo padre inizializza le variabili
    int base = 5;
    int altezza = 10;
    int risultato;

    // Creazione del processo figlio
    pid_t pid = fork();

    if (pid < 0) {
        // Errore nella creazione del processo
        perror("Errore durante la fork");
        return 1;
    } 
    else if (pid == 0) {
        // --- CODICE DEL PROCESSO FIGLIO ---
        risultato = 2 * (base + altezza);
        printf("[PROCESSO FIGLIO - PID: %d] Perimetro del rettangolo: %d\n", getpid(), risultato);
        exit(0);
    } 
    else {
        risultato = base * altezza;
        printf("[PROCESSO PADRE - PID: %d] Area del rettangolo: %d\n", getpid(), risultato);

        wait(NULL);
    }

    return 0;
}
