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

FILE *ent, *saiQuick;

typedef char nome[52]; // declarando tamanho das entradas
typedef nome nome;
int contador=0; // contador de comparacoes

int compara (const char * a, const char * b) { // funcao para comparar strings e contar as comparacoes ao mesmo tempo
    contador++;
    return strcmp (a, b);
}

int Partition (nome *lista, int ini, int fim) { // funcao partiton usada pelo QuickSort para ordenacao de strings
   nome pivo, aux;
   int esq, dir;
   strcpy(pivo,lista[ini]);    // neste exemplo, o pivo é o primeiro da esquerda
   esq  = ini + 1;
   dir  = fim;
   do {
      // percorrer da esquerda para a direita. encontrar alguem >= pivo
      while (esq < fim && compara(lista[esq],pivo)<0)
         esq++;
      // percorrer da direita para a esquerda. encontrar alguem < pivo
      while (ini < dir && compara(pivo, lista[dir])<=0)
         dir--;
      // se achou um `a esquerda e outro `a direita
      if(esq < dir) {
         // permutar
         strcpy(aux,lista[esq]);
         strcpy(lista[esq],lista[dir]);
         strcpy(lista[dir],aux);
      }
      // caso contrario, terminara´ a repeticao
   } while (esq < dir);
   // trocar o pivo com o elemento que "divide" os subvetores
   strcpy(lista[ini],lista[dir]);
   strcpy(lista[dir],pivo);
   // retornar a posição da "divisa"
   return dir;
}

void QuickSort (nome *lista, int ini, int fim) { // QuickSort para strings
   int p; //posição do pivo
   if (ini < fim) {
      p = Partition (lista, ini, fim);
      QuickSort (lista, ini, p-1); // chamando a recusiva duas vezes
      QuickSort (lista, p+1, fim);
   }
}

int main () {
    ent=fopen("C:\\Lab2\\StringsAleatorias.txt","r"); // abrindo arquivo de entrada
    saiQuick=fopen("C:\\Lab2\\quick.txt ","w"); // abrindo arquivos de saida
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
    QuickSort(lista,0,n-1); // executando BubbleSort
    fimB=clock(); // fim da contagem
    tempoB=(fimB - inicioB)/(float) CLOCKS_PER_SEC; // calculando tempo
    compB=contador; // armazenando o numero de comparacoes do Bubble
    fprintf(saiQuick,"Algoritmo: Quick-Sort\n\nTamanho da entrada: %d\nComparacoes feitas: %d\nTempo de execucao: %.7f segundos\n\n--------------------------------------------------\n", n, compB, tempoB); // printando no arquivo
    for(int i=0; i<n; i++) { // printando a lista ordenada no arquivo
        fprintf(saiQuick,"%s",lista[i]);
    }
    fclose(ent); // fechando arquivo de entrada pela ultima vez
    fclose(saiQuick); // fechando arquivo de saida do Bubble
    return 0;
}
