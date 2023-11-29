#include "algoritmo.h"

int* geraVetorAleatorio1(int tamanho) {
    int chaveBusca = -1, i;

    FILE *file = fopen("busca.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    int* array = (int*)malloc(tamanho * sizeof(int)); 
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;  
    }

    printf("Números gerados: ");
    for (int i = 0; i < tamanho; i++) {
        array[i] = rand() % 1000;
        fprintf(file, "%d\t ", array[i]);
        printf("%d ", array[i]);
    }
    fprintf(file, "\n");

    fclose(file);

    printf("\n");    
    
    receberChaveBusca(array, tamanho, chaveBusca);

    return array; 
}

//Função para ler os elementos gerados no arquivo
void lerElementosDoArquivo1(const char *fp, int **array, int *tamanho) {

    FILE *file = fopen(fp, "r");
    
    if (file == NULL) {
        perror("Erro ao abrir arquivo.");
        exit(EXIT_FAILURE);
    }

    int num;
    int size = 0;

    while (fscanf(file, "%d", &num) == 1) {
        size++;
    }

    *array = (int *)malloc(size * sizeof(int));
    if (*array == NULL) {
        perror("Erro ao alocar memória.");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &(*array)[i]);
    }

    *tamanho = size;
    fclose(file);
}

//Função para receber a chave de busca
void receberChaveBusca(int *array, int tamanho, int chaveBusca){
    
    int i, contadorPosicoes = 0, *posicoes = NULL;

    printf("\nTendo gerado os números, digite o elemento que deseja buscar:\n");
    scanf("%d", &chaveBusca);

    lerElementosDoArquivo1("busca.txt", &array, &tamanho);


    buscaLinear(array, tamanho, chaveBusca, &posicoes, &contadorPosicoes);
    buscaLinearComSentinela(array, tamanho, chaveBusca);
    buscaBinaria(array, tamanho, chaveBusca);
    
    if (contadorPosicoes > 0){
        printf("Elemento encontrado na posição: ");
        for (i = 0; i < contadorPosicoes; i++){ 
            printf("%d, ", posicoes[i]);
        }
        printf("\n\n");
    }
    else{
        printf("Elemento não encontrado.\n");
    }
    free(posicoes);
    
    geraResultadosBusca(array, tamanho, chaveBusca);
}

void geraResultadosBusca(int *array, int tamanho, int chaveBusca) {
    
    int contadorPosicoes = 0, *posicoes = NULL;

    clock_t inicio, fim;
    
    inicio = clock();
    int resultadoLinear = buscaLinear(array, tamanho, chaveBusca, &posicoes, &contadorPosicoes);
    fim = clock();
    printf("Tempo de Busca Linear para n=%d: %d \nTempo tomado: %f\n\n", tamanho, (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    int resultadoSentinela = buscaLinearComSentinela(array, tamanho, chaveBusca);
    fim = clock();
    printf("Tempo de Busca Linear com Sentinela para n=%d: %d \nTempo tomado: %f\n\n", tamanho, (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    int resultadoBinaria = buscaBinaria(array, tamanho, chaveBusca);
    fim = clock();
    printf("Tempo de Busca Binária para n=%d: %d \nTempo tomado: %f\n\n", tamanho, (int)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    if (contadorPosicoes > 0) {
        printf("Elemento encontrado na posição:");
        for (int i = 0; i < contadorPosicoes; i++) {
            printf("%d, ", posicoes[i]);
        }
        printf("\n");
    }
    else {
        printf("Elemento não encontrado.\n");
    }  

    free(posicoes);

    system("PAUSE");

}

//Função de busca sequencial linear simples
int buscaLinear(int *array, int tamanho, int chaveBusca, int **posicoes, int *contadorPosicoes) {
    
    *contadorPosicoes = 0;
    *posicoes = (int *)malloc (tamanho * sizeof(int));
    
    if (*posicoes == NULL){
        printf("Erro ao alocar memória.\n");
    }
    for (int i = 0; i < tamanho; i++) {
        if (array[i] == chaveBusca) {
            (*posicoes)[(*contadorPosicoes)++] = i;
        }
    }
    return -1;
    
}

//Função de busca sequencial linear com valor sentinela
int buscaLinearComSentinela(int *array, int tamanho, int chaveBusca) {
    int lastElement = array[tamanho];
    array[tamanho] = chaveBusca; 
    int i = 0;
    while (array[i] != chaveBusca) {
        i++;
    }
    if ((i < tamanho - 1) || (array[tamanho - 1] == chaveBusca)) {
        return i;  
    }
    return -1;
}

//Função de busca binária
int buscaBinaria(int *array, int tamanho, int chaveBusca) {

    int left = 0;
    int right = tamanho - 1;
    
    while (left <= right) {
        int half = left + (right - left) / 2;
        if (array[half] == chaveBusca) {
            return half;
        }
        if (array[half] < chaveBusca) {
            left = half + 1;
        } else {
            right = half - 1;
        }
    }
    return -1;
}