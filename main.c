#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define NONE "\033[0m"
#define BLUE "\033[0;34m"

void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

void getTom(int bomba, int bombaI, char *tom) {
    if (bomba > (bombaI / 3) * 2) {
        strcpy(tom, GREEN);
    } else if ((bomba < bombaI / 3) || bomba == 0) {
        strcpy(tom, RED);
    } else {
        strcpy(tom, YELLOW);
    }
}

void limpaChat() { system("clear"); }

char YN(char aux) {
    do {
        printf("[%sY%s/%sN%s]\n", GREEN, NONE, RED, NONE);
        flush_in();
        scanf("%c", &aux);
        if (aux != 'Y' && aux != 'N') {
            printf("%s\nOpção inválida%s\n\n", RED, NONE);
        }
    } while (aux != 'Y' && aux != 'N');
    return aux;
}

float maior0f(float aux) {
    do {
        scanf("%f", &aux);
        if (aux <= 0) {
            printf("%sValor inválido, digite novamente:%s\n\n", RED, NONE);
        }
    } while (aux <= 0);
    return aux;
}

int maior0i(int aux) {
    do {
        scanf("%d", &aux);
        if (aux <= 0) {
            printf("%sValor inválido, digite novamente:%s\n\n", RED, NONE);
        }
    } while (aux <= 0);
    return aux;
}

int comprarGasosa(int bomba, int bombaI, float caixa, float valLitro) {
    char comprarGasosa;
    int compra;
    char confirm;
    char tom[10];
    getTom(bomba,bombaI, tom);

    limpaChat();
    printf("%sGasolina na bomba: %s%d%s/%d\n", BLUE, tom, bomba, NONE, bombaI);
    printf("%sValor no caixa: %sR$ %.2f\n", BLUE, NONE, caixa);
    printf("%s\nDeseja comprar mais gasosa?%s ", BLUE, NONE);
    comprarGasosa = YN(comprarGasosa);

    if (comprarGasosa == 'Y') { // comprar
        limpaChat();

        printf("%sGasolina na bomba: %s%d%s/%d\n", BLUE, tom, bomba, NONE, bombaI);
        printf("%sValor no caixa: %sR$ %.2f\n", BLUE, NONE, caixa);
        printf("\n%sQuantos litros deseja comprar?:%s\n", BLUE, NONE);
        compra = maior0i(compra);
        printf("Deseja confirmar a compra de %s%d%s litros por %sR$ %.2f%s? ", RED,
               compra, NONE, RED, compra * valLitro, NONE);
        confirm = YN(confirm);

        float custo = compra * valLitro;

        if (custo > caixa) { // nao tem  dinheiro sulficiente
            limpaChat();
            printf("\n%sSeu caixa não tem dinheiro sulficiente! transação "
                   "cancelada%s\n",
                   RED, NONE);
            printf("%sVolte quando tiver mais R$%.2f (você tem R$%.2f)  %s\n\n", RED,
                   custo - caixa, caixa, NONE);
            return 0;
        } else {                // tem dinheiro sulficiente
            if (confirm == 'Y') { // transação completa
                limpaChat();
                printf("\n%sObrigado pela compra!%s\n\n", GREEN, NONE);
                return compra;
            } else {
                limpaChat();
                printf("\n%sTransação cancelada!%s\n\n", RED, NONE);
                return 0;
            }
        }

    } else {
        limpaChat();
        printf("\n%sTransação cancelada!%s\n\n", RED, NONE);
        return 0;
    }
}

void relatorio(int tamFila, float valLitro, int atendidos, int bomba,
               int bombaI, float caixa, int LVendidos) {
    char tom[10];
    getTom(bomba,bombaI, tom);
    char op;
    while (op != 'F') {
        do {
            printf("\nDigite a opção desejada:\n"
                   "A - Quantidade de litros vendida\n"
                   "B - Valor total das vendas\n"
                   "C - Carros atendidos\n"
                   "D - Combustível restante\n"
                   "E - Arquivo de impressão\n"
                   "F - Voltar\n");
            flush_in();
            scanf("%c", &op);
            if (op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' &&
                op != 'F') {
                limpaChat();
                printf("%s\nOpção inválida%s\n\n", RED, NONE);
            }
        } while (op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' &&
                 op != 'F');

        switch (op) {
            case 'A':
                limpaChat();
                printf("\n%sLitros vendidos: %s%d\n", BLUE, NONE, LVendidos);
                break;
            case 'B':
                limpaChat();
                printf("\n%sValor total arrecadado:%s R$ %.2f\n", BLUE, NONE,
                       valLitro * LVendidos);
                break;
            case 'C':
                limpaChat();
                printf("\n%sAtendidos:%s %d\n", BLUE, NONE, atendidos);
                break;
            case 'D':
                limpaChat();
                printf("\n%sGasolina na bomba: %s%d%s/%d\n", BLUE, tom, bomba, NONE,
                       bombaI);
                break;
            case 'E':
                limpaChat();
                printf("\n%sLitros vendidos: %s%d\n", BLUE, NONE, LVendidos);
                printf("%sValor total arrecadado:%s R$ %.2f\n", BLUE, NONE,
                       valLitro * LVendidos);
                printf("%sAtendidos: %s%d carro(s)\n", BLUE, NONE, atendidos);
                printf("%sGasolina na bomba: %s%d%s/%d\n\n", BLUE, tom, bomba, NONE,
                       bombaI);

                printf("%sTamanho maximo da fila:%s %d carro(s)\n", BLUE, NONE, tamFila);
                printf("%sPreço da Gasolina:%s R$ %.2f/Litro\n", BLUE, NONE, valLitro);
                printf("%sCaixa atual:%s R$ %.2f\n", BLUE, NONE, caixa);
                break;
        }
    }
    limpaChat();
}

int menu(int op, int qtdCarros, int tamFila, int bombaI, int bomba,
         float caixa) {
    char tom[10];
    getTom(bomba,bombaI, tom);
    do {
        printf("%sCarros atualmente na fila: %s%d/%d\n", BLUE, NONE, qtdCarros,
               tamFila);
        printf("%sValor no caixa: %sR$ %.2f\n", BLUE, NONE, caixa);
        printf("%sGasolina na bomba: %s%d%s/%d\n", BLUE, tom, bomba, NONE, bombaI);

        printf("Digite a opção desejada:\n"
               "1 - Adicionar carro\n"
               "2 - Abastecer próximo carro\n"
               "3 - Exibir fila de espera\n"
               "4 - Relatório geral\n"
               "5 - Comprar gasosa\n"
               "6 - Encerrar\n");
        scanf("%d", &op);
        if (op < 1 || op > 6) {
            limpaChat();
            printf("%s\nOpção inválida%s\n\n", RED, NONE);
        }
    } while (op < 1 || op > 6);

    return op;
}

int main(void) {


    float valLitro, caixa;
    int tamFila;

    int op, atendidos = 0, LVendidos = 0, bombaI, LAbastecido,  qtdCarros = 0, compra;

    // introducao ------------------------------------
    limpaChat();
    printf("%sAutor: %sEduardo Marcon Fadel\n\n", BLUE, NONE);
    printf("%s..:: Posto de Gasolina ::..%s\n\n", YELLOW, NONE);
    printf("O programa é um simulador de posto de gasolina que possui apenas uma "
           "bomba, o algoritmo é efetuado por meio de uma fila de carros que sao "
           "abastecidos por uma quantidade determinada de gasolina\n\n");
    //------------------------------------------------

    // requisitos iniciais ----------------------------

    printf("Digite o preço da gasosa:\n");
    valLitro = maior0f(valLitro);

    printf("Digite o tamanho máximo da fila:\n");
    tamFila = maior0i(tamFila);

    printf("Digite o valor atual no caixa:\n");
    caixa = maior0f(caixa);

    printf("Digite o tamanho da bomba em litros:\n");
    bombaI = maior0i(bombaI);

    int bomba = bombaI;

    //------------------------------------------------

    limpaChat();
    printf("Configurações iniciais:\n");
    printf("Tamanho maximo da fila: %s%d carro(s)%s\n", BLUE, tamFila, NONE);
    printf("Preço da Gasolina: %sR$ %.2f/Litro%s\n\n", BLUE, valLitro, NONE);

    while (op != 6) {

        op = menu(op, qtdCarros, tamFila, bombaI, bomba, caixa);
        switch (op) {
            case 1: // adicionar carro

                if (qtdCarros == tamFila) {
                    limpaChat();
                    printf("\n%sTamanho máximo da fila atingida!%s volte outra hora\n\n",
                           RED, NONE);
                } else {
                    qtdCarros++;
                    limpaChat();
                    printf("\n%sCarro adicionado%s\n\n", GREEN, NONE);
                }

                break;
            case 2: // abastecer
                if (bomba == 0) {
                    limpaChat();
                    printf("%s\nAcabou a gasosa%s\n\n", RED, NONE);
                    bomba = comprarGasosa(bomba, bombaI, caixa, valLitro);
                    break;
                } else if (qtdCarros == 0) { // fila vazia
                    limpaChat();
                    printf("%s\nNão tem nenhum carro na fila, vai achar clientes%s\n\n",
                           RED, NONE);
                } else {
                    do { // quanto o carro vai abastecer
                        printf("\nDigite a quantidade de litros a ser abastecido:\n");
                        LAbastecido = maior0i(LAbastecido);
                        if (LAbastecido > bomba) {

                            printf("\n%sAtualmente a bomba tem %d litro%s\n", RED, bomba, NONE);
                            printf("%sDigite um valor menor%s\n", RED, NONE);
                        } else { // abastecimento bem sucedido
                            qtdCarros--;
                            bomba -= LAbastecido;
                            LVendidos += LAbastecido;
                            limpaChat();
                            printf("\n%sCarro abastecido com %d litros%s\n\n", GREEN,
                                   LAbastecido, NONE);
                            caixa += LAbastecido * valLitro;
                            atendidos++;

                            break;
                        }
                    } while (LAbastecido > bomba);
                }
                break;
            case 3: // exibir fila
                limpaChat();
                printf("\nFila:\n\n");

                break;
            case 4: // relatorio

                limpaChat();
                printf("\n%sRelatório:%s\n\n", BLUE, NONE);
                relatorio(tamFila, valLitro, atendidos, bomba, bombaI, caixa, LVendidos);
                break;
            case 5:
                compra = comprarGasosa(bomba, bombaI, caixa, valLitro);
                caixa -= compra * valLitro;
                bomba += compra;
                break;
            case 6:
                limpaChat();
                printf("\nAdeus\n");
                break;
        }
    }

    return 0;
}