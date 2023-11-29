#include "algoritmo.h"

int* geraVetorAleatorio2(int tamanho) {
    int* array = (int*)malloc(tamanho * sizeof(int)); 
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;  
    }
    
    int *tempArray = (int*)malloc(tamanho * sizeof(int));
    
    if (tempArray == NULL){
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    
    FILE *file = fopen("classificacao.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    printf("Elementos gerados: ");
    for (int i = 0; i < tamanho; i++) {
        array[i] = rand() % 1000;
        tempArray[i] = array[i];
        fprintf(file, "%d\t", tempArray[i]);
        printf("%d ", array[i]);
    }
    fprintf(file, "\n");
    fclose(file);

    printf("\n");
    
    geraResultadosOrdenacao(array, tamanho);
    return array; 
}

void lerElementosDoArquivoOrdenacao2(const char *fp, int **array, int *tamanho) {
    FILE *file = fopen(fp, "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    int num;
    int size = 0;

    while (fscanf(file, "%d", &num) == 1) {
        size++;
    }

    *array = (int *)malloc(size * sizeof(int));
    if (*array == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &(*array)[i]);
    }

    *tamanho = size;
    fclose(file);
}

//Função para gerar os resultados das execuções
void geraResultadosOrdenacao(int *array, int tamanho) {
   
    int *tempArray = (int *)malloc(tamanho * sizeof(int));

    clock_t inicio, fim;

    lerElementosDoArquivoOrdenacao2("classificacao.txt", &tempArray, &tamanho);


    inicio = clock();
    insertionSort(tempArray, tamanho);
    fim = clock();
    printf("\nTempo de classificação para Insertion Sort com n=%d: %ld \nTempo tomado: %f segundos\n\n", tamanho, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    inicio = clock();
    selectionSort(tempArray, tamanho);
    fim = clock();
    printf("Tempo de classificação para Selection Sort com n=%d: %ld \nTempo tomado: %f segundos\n\n", tamanho, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    inicio = clock();
    bubbleSort(tempArray, tamanho);
    fim = clock();
    printf("Tempo de classificação para Bubble Sort com n=%d: %ld \nTempo tomado: %f segundos\n\n", tamanho, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    inicio = clock();
    quickSort(tempArray, 0, tamanho - 1);
    fim = clock();
    printf("Tempo de classificação para Quick Sort com n=%d: %ld \nTempo tomado: %f segundos\n\n", tamanho, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    inicio = clock();
    mergeSort(tempArray, 0, tamanho - 1);
    fim = clock();
    printf("Tempo de classificação para Merge Sort com n=%d: %ld \nTempo tomado: %f segundos\n\n", tamanho, (long)(fim - inicio), ((double)(fim - inicio)) / CLOCKS_PER_SEC);

    
    free(tempArray);
    system("PAUSE");
}



//Função de classificação por inserção
void insertionSort(int *array, int tamanho) {
    int i, j, auxiliar;

    for (i = 1; i < tamanho; i++) {
        auxiliar = array[i];
        j = i - 1;

        while ((j >= 0) && (auxiliar < array[j])) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = auxiliar;
    }
}
//Função de classificação por seleção
void selectionSort(int *array, int tamanho) {
    int i, j, menor, auxiliar;
    
    for (i = 0; i < tamanho - 1; i++) {
        menor = i;
        
        for (j = i + 1; j < tamanho; j++) {
            if (array[j] < array[menor]) {
                menor = j;
            }
        }
        if (i != menor) {
            auxiliar = array[i];
            array[i] = array[menor];
            array[menor] = auxiliar;
        }
    }
}

//Função de classificação por bolha
void bubbleSort(int *array, int tamanho) {
    int i, auxiliar, continua, fim = tamanho;

    do {
        for (i = 0; i < fim - 1; i++) {
            if (array[i] > array[i + 1]) {
                auxiliar = array[i];
                array[i] = array[i + 1];
                array[i + 1] = auxiliar;
                continua = i;
            }
        }
        fim--;
    } while (continua != 0);
}

//Função para realizar a partição do vetor
int realizaParticao(int *array, int inicio, int fim) {
    int esquerda, direita, pivo, auxiliar;
    esquerda = inicio;    
    direita = fim;
    pivo = array[inicio];

    while (esquerda < direita) {
        
        while (array[esquerda] <= pivo) {
            esquerda++;
        }
        while (array[direita] > pivo) {
            direita--;
        }
        if (esquerda < direita) {
            auxiliar = array[esquerda];
            array[esquerda] = array[direita];
            array[direita] = auxiliar;
        }
    }
    array[inicio] = array[direita];
    array[direita] = pivo;
    return direita;
}

void quickSort(int *array, int inicio, int fim) {
    int pivo;

    if (fim > inicio) {
        pivo = realizaParticao(array, inicio, fim);
        quickSort(array, inicio, pivo - 1);
        quickSort(array, pivo + 1, fim);
    }
}

//Função de realizar mescla
void realizaMescla(int *array, int inicio, int meio, int fim) {
    int *temporario, pont1, pont2, i, j, k, fim1 = 0, fim2 = 0;

    int tamanho = fim - inicio + 1;
    pont1 = inicio;
    pont2 = meio + 1;

    temporario = (int *)malloc(tamanho * sizeof(int));

    if (temporario != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (!fim1 && !fim2) {
                if (array[pont1] < array[pont2]) {
                    temporario[i] = array[pont1++];   
                } 
                else {
                    temporario[i] = array[pont2++];
                }

                if (pont1 > meio) {
                    fim1 = 1;
                }
                if (pont2 > fim) {
                    fim2 = 1;
                }
            } 
            else {
                if (!fim1) {
                    temporario[i] = array[pont1++];
                } else {
                    temporario[i] = array[pont2++];
                }
            }
        }
        
        for (j = 0, k = inicio; j < tamanho; j++, k++) {
            array[k] = temporario[j];
        }
    }
    free(temporario);
}

//Função de classificação por mescla
void mergeSort(int *array, int inicio, int fim) {
    int meio;
    
    if (inicio < fim) {
        meio = floor((inicio + fim) / 2);
        mergeSort(array, inicio, meio);
        mergeSort(array, meio + 1, fim);
        realizaMescla(array, inicio, meio, fim);
    }
}