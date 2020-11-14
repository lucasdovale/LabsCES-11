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

FILE *ent, *saiMerge;

typedef char nome[52]; // declarando tamanho das entradas
typedef nome nome;
int n,contador=0; // contador de comparacoes
nome *T;

int compara (const char * a, const char * b) { // funcao para comparar strings e contar as comparacoes ao mesmo tempo
    contador++;
    return strcmp (a, b);
}

void Merge (nome *lista, int ini, int fim) { // funcao recursiva usada pelo MergeSort para ordenacao de strings
   int med,
       i,          //percorre T
       j,          //percorre lado esquerdo de V
       k;          //percorre lado direito  de V

   med = (ini+fim)/2; //mesmo arredondamento feito ao chamar MergeSort
   j = ini;
   k = med+1;
   i = ini;
   //percorrer selecionando os menores
   while (j <= med && k <= fim) {
      if (compara(lista[j],lista[k])<=0) {
         strcpy(T[i],lista[j]);
         j++;
      }
      else {
         strcpy(T[i],lista[k]);
         k++;
      }
      i++;
   }
   //se sobrou algo `a esquerda, copiar para T
   while(j <= med) {
        strcpy(T[i],lista[j]);
        i++;
        j++;
   }
   //se sobrou algo `a direita, copiar para T
   while(k<=fim) {
      strcpy(T[i],lista[k]);
      i++;
      k++;
   }
   // lista recebe T
   for(i=ini; i<=fim; i++)
      strcpy(lista[i],T[i]);
}

void MergeSort (nome *lista, int ini, int fim) { // MergeSort para strings
   int med;
   if (ini < fim) {
      med = (ini+fim)/2;          // dividir ao meio
      MergeSort (lista, ini,   med);  // ordenar lado esquerdo
      MergeSort (lista, med+1, fim);  // ordenar lado direito
      Merge     (lista, ini,   fim);  // mesclar as duas metades
   }
}

int main () {
    ent=fopen("C:\\Lab2\\StringsAleatorias.txt","r"); // abrindo arquivo de entrada
    saiMerge=fopen("C:\\Lab2\\merge.txt ","w"); // abrindo arquivos de saida
    clock_t inicioB,fimB;
    float tempoB;
    int compB;
    nome entrada; // declarando variavel a ser usada para armazenar as entradas
    nome *lista; // variavel lista (vetor de strings)
    fscanf(ent,"%d ", &n); // lendo o numero de entradas
    lista=(nome*)malloc(n*sizeof(nome)); // alocando na memoria
    T=(nome*)malloc(n*sizeof(nome)); // alocando a memoria no vetor de strings
    for(int i=0; i<n; i++) { // lendo cada entrada
        fgets(entrada,52,ent);
        strcpy(lista[i],entrada);
    }
    inicioB=clock(); // inicio da contagem de tempo
    MergeSort(lista,0,n-1); // executando BubbleSort
    fimB=clock(); // fim da contagem
    tempoB=(fimB - inicioB)/(float) CLOCKS_PER_SEC; // calculando tempo
    compB=contador; // armazenando o numero de comparacoes do Bubble
    fprintf(saiMerge,"Algoritmo: Merge-Sort\n\nTamanho da entrada: %d\nComparacoes feitas: %d\nTempo de execucao: %.7f segundos\n\n--------------------------------------------------\n", n, compB, tempoB); // printando no arquivo
    for(int i=0; i<n; i++) { // printando a lista ordenada no arquivo
        fprintf(saiMerge,"%s",lista[i]);
    }
    fclose(ent); // fechando arquivo de entrada pela ultima vez
    fclose(saiMerge); // fechando arquivo de saida do Bubble
    return 0;
}
