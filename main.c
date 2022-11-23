#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

void relatorio() {
    char op;
    while (op != 'f') {
        printf("\n[!]Digite a opção desejada[!]\n"
               "a - Quantidade de litros vendida\n"
               "b - Valor total das vendas\n"
               "c - Carros atendidos\n"
               "d - Combustível restante\n"
               "e - Arquivo de impressão\n"
               "f - Voltar\n");
        flush_in();
        scanf("%c", &op);
        switch (op) {
            case 'a':
                printf("\nQuantidade de litros vendida: \n");
                break;
            case 'b':
                printf("\nValor total das vendas: \n");
                break;
            case 'c':
                printf("\nCarros atendidos: \n");
                break;
            case 'd':
                printf("\nCombustível restante: \n");
                break;
            case 'e':
                printf("\nQuantidade de litros vendida:\n"
                       "Valor total das vendas:\n"
                       "Carros atendidos:\n"
                       "Combustível restante:\n"
                       "Arquivo de impressão:\n"
                       "Voltar:\n");
                break;
        }
    }
}

int menu(int op) {
    printf("Digite a opção desejada:\n"
           "1 - Adicionar carro\n"
           "2 - Abastecer próximo carro\n"
           "3 - Exibir fila de espera\n"
           "4 - Relatório geral\n"
           "5 - Encerrar\n");
    scanf("%d", &op);
    return op;
}

int main(void) {

    float valLitro;
    int tamFila;
    int op;
    int atendidos;
    int bomba = 200;
    int caixa;
    int litros;
    char vAtendidos[100][255];

    // introducao ------------------------------------
    printf("Autor: Eduardo Fadel\n");
    printf("..:: Posto de Gasolina ::..\n");
    printf("O programa é um simulador de posto de gasolina que possui apenas uma "
           "bomba, o algoritmo é efetuado por meio de uma fila de carros que sao "
           "abastecidos por uma quantidade determinada de gasolina\n\n");
    //------------------------------------------------

    // requisitos iniciais ----------------------------
    printf("Digite o preço da gasosa\n");
    scanf("%f", &valLitro);
    printf("Digite o tamanho da fila\n");
    scanf("%d", &tamFila);
    char carros[tamFila][255];
    //------------------------------------------------

    while (op != 5) {
        op = menu(op);
        switch (op) {
            case 1: // adicionar carro

                printf("Carro adicionado\n");
                break;
            case 2: // abastecer
                printf("Carro abastecido, proxímo da fila\n");

                break;
            case 3: // exibir fila
                printf("Fila:\n");
                break;
            case 4: // relatorio
                printf("Relatório:\n");
                relatorio();
                break;
            case 5: // encerrar
                printf("Adeus\n");
                break;
        }
    }

    return 0;
}