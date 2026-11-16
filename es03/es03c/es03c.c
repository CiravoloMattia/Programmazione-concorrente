#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num1 = 5;
    int num2 = 4;
    int ris = 0;

    int pid1 = fork();

    if (pid1 == 0) {
        // PRIMO PROCESSO FIGLIO: moltiplicazione
        ris = num1 * num2;
        exit(ris);
    } 
    else {
        // PROCESSO PADRE: crea il secondo figlio
        int pid2 = fork();

        if (pid2 == 0) {
            // SECONDO PROCESSO FIGLIO: somma
            ris = num1 + num2;
            exit(ris);
        } 
        else {
            // PROCESSO PADRE: attende entrambi i figli
            int status;
            pid_t pid_terminato;

            for (int i = 0; i < 2; i++) {
                pid_terminato = wait(&status); // Unico punto in cui è obbligatorio usare '&'

                if (pid_terminato == pid1) {
                    printf("Il risultato della moltiplicazione (figlio 1) e': %d\n", WEXITSTATUS(status));
                } else if (pid_terminato == pid2) {
                    printf("Il risultato della somma (figlio 2) e': %d\n", WEXITSTATUS(status));
                }
            }
        }
    }

    return 0;
}
