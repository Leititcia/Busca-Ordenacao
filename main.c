#include "algoritmo.h"

int main(void) {

    int op, tamanho, chaveBusca = -1, *array;
    printf("---------------------------------\n");
    printf("Algoritmos de Busca e Ordenação\n");
    printf("---------------------------------\n");
    printf("Escolha uma opção:\n");
    printf("1. Buscar um Elemento\n");
    printf("2. Classificação de Elementos\n");
    printf(">> ");
    scanf("%d", &op);
    printf("---------------------------------\n");

    switch(op){
        case 1:
            printf("Digite o tamanho do vetor:\n");
            scanf("%d", &tamanho);
            array = geraVetorAleatorio1(tamanho);
            free(array);
            break;
        case 2:
            printf("Digite o tamanho do vetor:\n");
            scanf("%d", &tamanho);
            array = geraVetorAleatorio2(tamanho);
            free(array);
            break;
        default:    
            printf("Opção inexistente!\n");
            break;
    }
    return 0;
}