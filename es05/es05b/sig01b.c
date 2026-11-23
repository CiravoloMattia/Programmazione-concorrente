#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Variabile globale per contare quante volte viene premuto CTRL-C
volatile sig_atomic_t contatore = 0;

// Funzione che viene eseguita quando arriva il segnale SIGINT
void handler_sigint(int sig) {
    contatore++;
    
    if (contatore < 3) {
        printf("\nHai premuto CTRL-C! (%d/3)\n", contatore);
    } else {
        printf("\nArrivederci!\n");
        exit(0); // Termina il programma
    }
}

int main() {
    // Registriamo il gestore per SIGINT
    signal(SIGINT, handler_sigint);

    printf("Programma avviato. Premi CTRL-C 3 volte per uscire.\n");

    // Ciclo infinito per tenere vivo il programma
    while (1) {
        pause(); // Mette il processo in pausa finché non arriva un segnale
    }

    return 0;
}
