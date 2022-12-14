#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define NONE "\033[0m"
#define BLUE "\033[0;34m"

struct Carro {
    char marca[20];
    char cor[20];
    char placa[7];
    int portas;
    int litros;
};

void delay(unsigned int secs) {
    unsigned int end = time(0) + secs;
    while (time(0) < end)
        ;
}

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
    getTom(bomba, bombaI, tom);

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
    getTom(bomba, bombaI, tom);
    char op;
    bool rep = true;
    while (rep) {

        printf("\nDigite a opção desejada:\n"
               "A - Quantidade de litros vendida\n"
               "B - Valor total das vendas\n"
               "C - Carros atendidos\n"
               "D - Combustível restante\n"
               "E - Arquivo de impressão\n"
               "F - Voltar\n");
        flush_in();
        scanf("%c", &op);

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

                FILE *fp = fopen("registro.txt", "w");

                // That's fprintf, not printf!
                fprintf(fp, "Litros vendidos: %d\n", LVendidos);
                fprintf(fp, "Valor total arrecadado: R$ %.2f\n", valLitro * LVendidos);
                fprintf(fp, "Atendidos: %d carro(s)\n", LVendidos);
                fprintf(fp, "Gasolina na bomba: %d/%d\n", bomba, bombaI);
                fprintf(fp, "Caixa atual: R$ %.2f\n\n", caixa);
                fprintf(fp, "Tamanho maximo da fila: %d carro(s)\n", tamFila);
                fprintf(fp, "Preço da Gasolina: R$ %.2f/Litro\n", valLitro);
                fclose(fp);

                break;
            case 'F':
                rep = false;
                break;

            default:
                limpaChat();
                printf("%s\nOpção inválida%s\n\n", RED, NONE);
        }
    }
    limpaChat();
}

int menu(int op, int qtdCarros, int tamFila, int bombaI, int bomba,
         float caixa) {
    char tom[10];
    getTom(bomba, bombaI, tom);

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
           "%s6 - Encerrar%s\n",
           RED, NONE);
    scanf("%d", &op);

    return op;
}

void imprimirFila(struct Carro aux[], int t) {
    for (int i = 0; i < t; i++) {
        printf("%sPosicao %s[%s%d%s]\n", BLUE, NONE, RED, i + 1, NONE);
        printf("%sMarca: %s%s\n", BLUE, NONE, aux[i].marca);
        printf("%sCor: %s%s\n", BLUE, NONE, aux[i].cor);
        printf("%sPlaca: %s%s\n", BLUE, NONE, aux[i].placa);
        printf("%sPortas: %s%d\n\n", BLUE, NONE, aux[i].portas);
    }
}

void imprimirAtendidos(struct Carro aux[], int t) {
    for (int i = 0; i < t; i++) {
        printf("%sMarca: %s%s\n", BLUE, NONE, aux[i].marca);
        printf("%sCor: %s%s\n", BLUE, NONE, aux[i].cor);
        printf("%sPlaca: %s%s\n", BLUE, NONE, aux[i].placa);
        printf("%sPortas: %s%d\n", BLUE, NONE, aux[i].portas);
        printf("%sLitros Abastecidos: %s%d\n\n", BLUE, NONE, aux[i].litros);
    }
}

void adicionar(struct Carro fila[], int qtdCarros) {
    flush_in();
    limpaChat();
    printf("Digite o modelo da nave:");
    scanf("%s", &fila[qtdCarros].marca);
    printf("Digite a cor do potente:");
    scanf("%s", &fila[qtdCarros].cor);
    printf("Digite a placa da maquina:");
    scanf("%s", &fila[qtdCarros].placa);
    printf("Digite a quantidade de portas da carruagem:");
    fila[qtdCarros].portas = maior0i(fila[qtdCarros].portas);
    flush_in();
}

int main(void) {

    struct Carro *FilaAtendidos = (struct Carro *)calloc(1, sizeof(struct Carro));

    float valLitro, caixa;
    int tamFila;

    int op, atendidos = 0, LVendidos = 0, bombaI, LAbastecido, qtdCarros = 0,
            compra;

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
    struct Carro *fila = (struct Carro *)calloc(tamFila, sizeof(struct Carro));

    printf("Digite o valor atual no caixa:\n");
    caixa = maior0f(caixa);

    printf("Digite o tamanho da bomba em litros:\n");
    bombaI = maior0i(bombaI);

    int bomba = bombaI;

    // codigo ---------------------------------------

    limpaChat();
    printf("Configurações iniciais:\n");
    printf("Tamanho maximo da fila: %s%d carro(s)%s\n", BLUE, tamFila, NONE);
    printf("Preço da Gasolina: %sR$ %.2f/Litro%s\n\n", BLUE, valLitro, NONE);

    bool rep = true;
    while (rep) {

        op = menu(op, qtdCarros, tamFila, bombaI, bomba, caixa);
        switch (op) {
            case 1: // adicionar carro

                if (qtdCarros == tamFila) {
                    limpaChat();
                    printf("\n%sTamanho máximo da fila atingida!%s volte outra hora\n\n",
                           RED, NONE);
                } else {
                    qtdCarros++;
                    adicionar(fila, qtdCarros - 1);
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

                            FilaAtendidos[atendidos] = fila[0];
                            FilaAtendidos[atendidos].litros = LAbastecido;
                            atendidos++;
                            FilaAtendidos = (struct Carro *)realloc(
                                    FilaAtendidos, (atendidos + 1) * sizeof(struct Carro));
                            for (int i = 0; i < qtdCarros - 1; i++) {
                                fila[i] = fila[i + 1];
                            }

                            qtdCarros--;
                            bomba -= LAbastecido;
                            LVendidos += LAbastecido;
                            limpaChat();

                            caixa += LAbastecido * valLitro;
                            printf("\n%sCarro abastecido com %d litros%s\n", GREEN,
                                   LAbastecido, NONE);
                            printf("\n%sFoi adicionado R$ %.2f ao caixa%s\n\n", GREEN,
                                   LAbastecido * valLitro, NONE);

                            break;
                        }
                    } while (LAbastecido > bomba);
                }
                break;
            case 3: // exibir fila
                limpaChat();
                printf("Fila de Espera:\n\n");
                imprimirFila(fila, qtdCarros);
                printf("Atendidos:\n\n");
                imprimirAtendidos(FilaAtendidos, atendidos);

                break;
            case 4: // relatorio

                limpaChat();
                printf("\n%sRelatório:%s\n", BLUE, NONE);
                relatorio(tamFila, valLitro, atendidos, bomba, bombaI, caixa, LVendidos);
                break;
            case 5:
                compra = comprarGasosa(bomba, bombaI, caixa, valLitro);
                caixa -= compra * valLitro;
                bomba += compra;
                break;
            case 6:
                limpaChat();
                printf("Adeus\n");
                remove("registro.txt");
                delay(2);
                limpaChat();
                rep = false;
                break;

            default:
                limpaChat();
                printf("%s\nOpção inválida%s\n\n", RED, NONE);
                break;
        }
    }

    return 0;
}