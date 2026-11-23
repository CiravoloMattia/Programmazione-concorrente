#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Handler che intercetta il segnale ma non termina il programma
void handler_ignora(int sig) {
    printf("\nSIGINT ricevuto ma ignorato!\n");
}

int main() {
    // Impostiamo l'handler che "ignora" la terminazione
    // (Nota: per ignorarlo senza nemmeno stampare nulla, si userebbe signal(SIGINT, SIG_IGN);)
    signal(SIGINT, handler_ignora);

    printf("SIGINT ignorato per 10 secondi. Prova a premere CTRL-C...\n");

    // Ciclo di attesa di 10 secondi (come da suggerimento)
    unsigned int tempo_rimanente = 10;
    while (tempo_rimanente > 0) {
        tempo_rimanente = sleep(tempo_rimanente);
    }

    // Ripristiniamo il comportamento predefinito (Default)
    signal(SIGINT, SIG_DFL);
    printf("\nComportamento default ripristinato. CTRL-C ora terminerà il programma.\n");

    // Aspettiamo all'infinito che l'utente prema CTRL-C
    while (1) {
        pause();
    }

    return 0;
}
