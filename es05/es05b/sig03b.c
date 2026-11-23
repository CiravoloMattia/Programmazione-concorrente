#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Unico gestore per tutti i segnali
void gestore_segnali(int sig) {
    if (sig == SIGUSR1) {
        printf("\nSegnale 1 ricevuto - LED VERDE acceso\n");
    } 
    else if (sig == SIGUSR2) {
        printf("\nSegnale 2 ricevuto - LED ROSSO acceso\n");
    } 
    else if (sig == SIGINT) {
        printf("\nTerminazione richiesta dall'utente\n");
        exit(0);
    }
}

int main() {
    // Colleghiamo i tre segnali allo stesso handler
    signal(SIGUSR1, gestore_segnali);
    signal(SIGUSR2, gestore_segnali);
    signal(SIGINT, gestore_segnali);

    // Stampiamo il PID per facilitare i test da un altro terminale
    printf("Programma in ascolto. Il mio PID è: %d\n", getpid());

    // Loop infinito
    while (1) {
        pause();
    }

    return 0;
}
