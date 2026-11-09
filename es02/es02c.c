#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

// Definizione costante per il numero di lampeggi
#define NUM_LAMPEGGI 10

// Puntatore alla memoria condivisa per la variabile LED
int *led;

// Funzione che gestisce la logica di lampeggio del processo figlio
void gestisci_lampeggio() {
    char *colore;
    useconds_t intervallo_us; // Intervallo espresso in microsecondi per usleep()

    // Selezione della configurazione in base al valore della variabile led
    switch (*led) {
        case 1:
            colore = "VERDE";
            intervallo_us = 300000; // 0.3 secondi
            break;
        case 2:
            colore = "ROSSO";
            intervallo_us = 700000; // 0.7 secondi
            break;
        case 3:
            colore = "GIALLO";
            intervallo_us = 1200000; // 1.2 secondi
            break;
        default:
            printf("[FIGLIO] Codice LED non valido.\n");
            exit(1);
    }

    printf("\n--- Avvio lampeggio LED %s (PID Figlio: %d) ---\n", colore, getpid());

    for (int i = 1; i <= NUM_LAMPEGGI; i++) {
        // Accensione (qui andrebbe inserito il comando fisico per il GPIO)
        printf("[FIGLIO %d] LED %s ACCESO (%d/%d)\n", getpid(), colore, i, NUM_LAMPEGGI);
        usleep(intervallo_us);

        // Spegnimento (qui andrebbe inserito il comando fisico per il GPIO)
        printf("[FIGLIO %d] LED %s SPENTO (%d/%d)\n", getpid(), colore, i, NUM_LAMPEGGI);
        usleep(intervallo_us);
    }

    printf("--- Terminato lampeggio LED %s ---\n\n", colore);
    exit(0); // Il processo figlio termina dopo il ciclo
}

int main() {
    char comando;

    // Allocazione di memoria condivisa per la variabile 'led'
    led = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (led == MAP_FAILED) {
        perror("Errore mmap");
        return 1;
    }

    printf("=== CONTROLLO LED MULTI-PROCESSO ===\n");
    printf("Comandi disponibili:\n");
    printf(" 'v' -> LED Verde  (10 lampeggi ogni 0.3s)\n");
    printf(" 'r' -> LED Rosso  (10 lampeggi ogni 0.7s)\n");
    printf(" 'g' -> LED Giallo (10 lampeggi ogni 1.2s)\n");
    printf(" 'q' -> Uscita dal programma\n");

    while (1) {
        printf("\nInserisci un comando: ");
        scanf(" %c", &comando); // Lo spazio prima di %c ignora eventuali invii residui

        if (comando == 'q') {
            printf("Chiusura del programma...\n");
            break;
        }

        // Impostazione del valore della variabile 'led' nel padre
        if (comando == 'v') {
            *led = 1;
        } else if (comando == 'r') {
            *led = 2;
        } else if (comando == 'g') {
            *led = 3;
        } else {
            printf("Comando non valido. Riprova.\n");
            continue;
        }

        // Creazione del processo figlio dopo aver impostato la variabile led
        pid_t pid = fork();

        if (pid < 0) {
            perror("Errore nella fork");
            return 1;
        } else if (pid == 0) {
            // --- CODICE DEL PROCESSO FIGLIO ---
            gestisci_lampeggio();
        } else {
            // --- CODICE DEL PROCESSO PADRE ---
            // Il padre attende che il figlio finisca prima di chiedere un nuovo comando
            wait(NULL);
        }
    }

    // Liberazione della memoria condivisa
    munmap(led, sizeof(int));
    return 0;
}
