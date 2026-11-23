#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

// Funzione eseguita allo scadere dei 5 secondi
void handler_timeout(int sig) {
    printf("\nTempo scaduto!\n");
    exit(1); // Termina il programma con codice di errore
}

int main() {
    char password[50];

    // Registriamo il gestore per il segnale di allarme
    signal(SIGALRM, handler_timeout);

    printf("Inserisci la password entro 5 secondi: ");
    // fflush forza la stampa immediata a schermo prima che scanf blocchi il programma
    fflush(stdout); 

    // Avvia il timer di 5 secondi
    alarm(5);

    // Legge la password da tastiera
    scanf("%49s", password);

    // Se arriviamo qui, l'utente ha premuto Invio in tempo!
    // Disattiviamo subito l'allarme
    alarm(0);

    // Controlliamo se la password è corretta
    if (strcmp(password, "segreto123") == 0) {
        printf("Accesso consentito! Password corretta.\n");
    } else {
        printf("Accesso negato! Password errata.\n");
    }

    return 0;
}
