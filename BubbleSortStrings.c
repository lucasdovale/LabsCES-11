/* Lucas do Vale Bezerra                    */
/* Turma 3                                  */
/* Exercício 2: Ordenação                   */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Prof. Armando                            */
/* Setembro de 2018                         */
/* Programa compilado com CodeBlocks 13.12  */

#include <stdio.h> // declarando bibliotecas
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *ent, *saiBubble;

typedef char nome[52]; // declarando tamanho das entradas
typedef nome nome;
int contador=0; // contador de comparacoes

int compara (const char * a, const char * b) { // funcao para comparar strings e contar as comparacoes ao mesmo tempo
    contador++;
    return strcmp (a, b);
}

void BubbleSort (nome *lista, int n) { // BubbleSort nao otimizado para strings
    int i,p;
    nome aux; // string auxiliar para fazer a troca
    p=n-2;
    while (p>=0) {
        i=0;
        while (i<=p) {
            if (compara(lista[i],lista[i+1])>0) { // comparando strings consecutivas
                strcpy(aux,lista[i]);
                strcpy(lista[i],lista[i+1]);
                strcpy(lista[i+1],aux);
            }
            i++;
        }
        p--;
    }
}

int main () {
    ent=fopen("C:\\Lab2\\StringsAleatorias.txt","r"); // abrindo arquivo de entrada
    saiBubble=fopen("C:\\Lab2\\bubble.txt ","w"); // abrindo arquivos de saida
    clock_t inicioB,fimB;
    float tempoB;
    int n, compB;
    nome entrada; // declarando variavel a ser usada para armazenar as entradas
    nome *lista; // variavel lista (vetor de strings)
    fscanf(ent,"%d ", &n); // lendo o numero de entradas
    lista=(nome*)malloc(n*sizeof(nome)); // alocando na memoria
    for(int i=0; i<n; i++) { // lendo cada entrada
        fgets(entrada,52,ent);
        strcpy(lista[i],entrada);
    }
    inicioB=clock(); // inicio da contagem de tempo
    BubbleSort(lista,n); // executando BubbleSort
    fimB=clock(); // fim da contagem
    tempoB=(fimB - inicioB)/(float) CLOCKS_PER_SEC; // calculando tempo
    compB=contador; // armazenando o numero de comparacoes do Bubble
    fprintf(saiBubble,"Algoritmo: Bubble-Sort\n\nTamanho da entrada: %d\nComparacoes feitas: %d\nTempo de execucao: %.7f segundos\n\n--------------------------------------------------\n", n, compB, tempoB); // printando no arquivo
    for(int i=0; i<n; i++) { // printando a lista ordenada no arquivo
        fprintf(saiBubble,"%s",lista[i]);
    }
    fclose(ent); // fechando arquivo de entrada pela ultima vez
    fclose(saiBubble); // fechando arquivo de saida do Bubble
    return 0;
}
