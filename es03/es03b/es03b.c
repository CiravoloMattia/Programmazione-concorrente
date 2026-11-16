#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num1 = 5;
    int num2 = 4;
    int ris = 0;
    int operazione = 2; // 1 = somma, 2 = moltiplicazione

    int pid = fork();

    if (pid == 0) {
        // PROCESSO FIGLIO
        if (operazione == 1) {
            ris = num1 + num2;
        } else {
            ris = num1 * num2;
        }
        exit(ris);
    } 
    else {
        // PROCESSO PADRE
        int status;
        wait(&status); // Unico punto in cui è obbligatorio usare '&'
        
        // WEXITSTATUS estrae il numero restituito dal figlio
        printf("Il risultato ricevuto dal figlio e': %d\n", WEXITSTATUS(status));
    }

    return 0;
}
