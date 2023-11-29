#ifndef ALGORITMO_H
#define ALGORITMO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <x86intrin.h>

int *geraVetorAleatorio1(int tamanho);
int* geraVetorAleatorio2(int tamanho);

//Funções de busca
void receberChaveBusca(int *vetor, int tamanho, int chaveBusca);
void lerElementosDoArquivo1(const char *fp, int **vetor, int *tamanho);
void geraResultadosBusca(int *vetor, int tamanho, int chaveBusca);
int buscaLinear(int *vetor, int tamanho, int chaveBusca, int **posicoes, int *contadorPosicoes);
int buscaLinearComSentinela(int *vetor, int tamanho, int chaveBusca);
int buscaBinaria(int *vetor, int tamanho, int chaveBusca);

//Funções de ordenação
void geraResultadosOrdenacao(int *vetor, int tamanho);
void lerElementosDoArquivo2(const char *fp, int **vetor, int *tamanho);
void insertionSort(int *vetor, int tamanho);
void selectionSort(int *vetor, int tamanho);
void bubbleSort(int *vetor, int tamanho);
int realizaParticao(int *vetor, int inicio, int fim);
void quickSort(int *vetor, int inicio, int fim);
void realizaMescla(int *vetor, int inicio, int meio, int fim);
void mergeSort(int *vetor, int inicio, int fim);


#endif