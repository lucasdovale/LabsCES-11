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

FILE *ent, *saiBubble, *saiMerge, *saiQuick; // declarando os arquivos de entrada e saida

typedef char nome[52]; // declarando tamanho das entradas
typedef nome nome;
int n,contador=0; // contador de comparacoes
nome *T; // declarando o vetor de strings necessário para a funcao Merge

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
    ent=fopen("C:\\Lab2\\entrada2.txt","r"); // abrindo arquivo de entrada
    saiBubble=fopen("C:\\Lab2\\LucasdoVale2bubble.txt ","w"); // abrindo arquivos de saida
    saiMerge=fopen("C:\\Lab2\\LucasdoVale2merge.txt ","w");
    saiQuick=fopen("C:\\Lab2\\LucasdoVale2quick.txt ","w");
    clock_t inicioB, fimB, inicioM, fimM, inicioQ, fimQ; // declarando as variaveis de tempo para calcular o tempo de ordenacao de cada algoritmo
    float tempoB, tempoM, tempoQ; // tempo de cada algoritmo
    int compB, compM, compQ; // declarando tamanho da entrada e numero de comparacoes de cada algoritmo
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
    contador=0; // zerando contador para nova ordenacao
    free(lista); // liberando a memoria alocada no ponteiro lista
    fclose(ent); // fechando arquivo para que seja relido para uma nova ordenacao
    ent=fopen("C:\\Lab2\\entrada2.txt","r"); // reabrindo arquivo
    fscanf(ent,"%d ", &n); // lendo novamente o numero de entradas
    lista=(nome*)malloc(n*sizeof(nome)); // alocando novamente
    T=(nome*)malloc(n*sizeof(nome)); // alocando a memoria no vetor de strings
    for(int i=0; i<n; i++) { // lendo cada entrada novamente
        fgets(entrada,52,ent);
        strcpy(lista[i],entrada);
    }
    inicioM=clock(); // inicio da contagem de tempo
    MergeSort(lista,0,n-1); // executando MergeSort
    fimM=clock(); // fim da contagem
    tempoM=(fimM - inicioM)/(float) CLOCKS_PER_SEC; // calculando tempo
    compM=contador;  // armazenando o numero de comparacoes do Merge
    fprintf(saiMerge,"Algoritmo: Merge-Sort\n\nTamanho da entrada: %d\nComparacoes feitas: %d\nTempo de execucao: %.7f segundos\n\n--------------------------------------------------\n", n, compM, tempoM); // printando no arquivo
    for(int i=0; i<n; i++) { // printando a lista ordenada no arquivo
        fprintf(saiMerge,"%s",lista[i]);
    }
    contador=0; // zerando contador para nova ordenacao
    free(lista); // liberando a memoria alocada no ponteiro lista
    fclose(ent); // fechando arquivo para que seja relido para uma nova ordenacao
    ent=fopen("C:\\Lab2\\entrada2.txt","r"); // reabrindo arquivo
    fscanf(ent,"%d ", &n); // lendo novamente o numero de entradas
    lista=(nome*)malloc(n*sizeof(nome));  // alocando novamente
    for(int i=0; i<n; i++) {  // lendo cada entrada novamente
        fgets(entrada,52,ent);
        strcpy(lista[i],entrada);
    }
    inicioQ=clock(); // inicio da contagem de tempo
    QuickSort(lista,0,n-1); // executando QuickSort
    fimQ=clock(); // fim da contagem
    tempoQ=(fimQ - inicioQ)/(float) CLOCKS_PER_SEC; // calculando tempo
    compQ=contador; // armazenando o numero de comparacoes do Quick
    fprintf(saiQuick,"Algoritmo: Quick-Sort\n\nTamanho da entrada: %d\nComparacoes feitas: %d\nTempo de execucao: %.7f segundos\n\n--------------------------------------------------\n", n, compQ, tempoQ); // printando no arquivo
    for(int i=0; i<n; i++) { // printando a lista ordenada no arquivo
        fprintf(saiQuick,"%s",lista[i]);
    }
    fclose(ent); // fechando arquivo de entrada pela ultima vez
    fclose(saiBubble); // fechando arquivo de saida do Bubble
    fclose(saiMerge); // fechando arquivo de saida do Merge
    fclose(saiQuick); // fechando arquivo de saida do Quick
    return 0;
}
