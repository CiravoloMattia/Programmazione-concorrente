#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: somma <num1> <num2>\n");
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int somma = num1 + num2;

    printf("[Somma] %d + %d = %d\n", num1, num2, somma);

    return 0;
}
