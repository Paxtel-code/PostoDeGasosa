#include <stdio.h>

void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

int main(void) {

    int tamFila;
    float valLitro;

    // introducao
    printf("Autor: Eduardo Fadel\n");
    printf("..:: Posto de Gasolina ::..\n");
    printf("O programa é um simulador de posto de gasolina que possui apenas uma "
           "bomba, o algoritmo é efetuado por meio de uma fila de carros que sao "
           "abastecidos por uma quantidade determinada de gasolina\n");

    // requisitos iniciais
    printf("Digite o preço da gasosa\n");
    scanf("%f", &valLitro);
    printf("Digite o tamanho da fila\n");
    scanf("%d", &tamFila);
    char carros[tamFila][255];

    return 0;
}
