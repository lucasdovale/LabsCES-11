/* Lucas do Vale Bezerra                    */
/* Turma 3                                  */
/* Exercício 7: Fibra Ótica                 */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Prof. Armando                            */
/* Novembro de 2018                         */
/* Programa compilado com CodeBlocks 13.12  */

#include <stdio.h> // declarando bibliotecas
#include <stdlib.h>
#include <string.h>

typedef struct { // declarando struct para armazenar as informaçoes de cada vertice (predio) do grafo
    int num; // numero correspondente ao vertice
    char nome[12]; // nome do predio
    int grau=0; // quantidade de arestas ligadas ao vertice
    int arestas[1000]; // vetor para armazenar quais arestas estão ligadas ao vertice
} Predios;

Predios p[150]; // vetor de predios (vertices), nosso grafo

struct PCM { // struct utilizada para ordenar o vetor pai após o algoritmo de Prim
    int pai;
    int filho;
};

int grafo [150][150]={0}; // matriz de adjacência

void BubbleSort (PCM v[], int n) { // BubbleSort nao otimizado para structs especificas
    int i,p;
    PCM aux; // struct auxiliar para fazer a troca
    p=n-2;
    while (p>=0) {
        i=0;
        while (i<=p) {
            if (grafo[v[i].filho][v[i].pai]>grafo[v[i+1].filho][v[i+1].pai]) { // comparando custos consecutivas
                aux=v[i]; // ordenando
                v[i]=v[i+1];
                v[i+1]=aux;
            }
            i++;
        }
        p--;
    }
}

void algPrim (int orig, int *pai, int vertices) { // algoritmo de Prim, adaptado da internet para matrizes
    int i, j, dest, primeiro; // variaveis de iteração e de verificação
    double menorPeso; // variavel que armazena o menor custo de aresta para um dado grafo
    for(i=0;i<vertices;i++) // inicio, ninguem tem pai, inserindo -1 em todo o vetor
        pai[i]=-1;
    pai[orig]=orig; // o pai da origem é a propria origem
    while (1) { // enquanto ainda existir vertice
        primeiro=1; // variavel primeiro recebe "TRUE"
        for (i=0;i<vertices;i++) { // para cada vertice, verificar menor custo
            if (pai[i]!=-1) { // caso em que ainda nao há pai desse vertice
                for (j=0;j<p[i].grau;j++) { // para cada vizinho desse vertice
                    if (pai[p[i].arestas[j]]==-1) { // caso em que vizinho nao tem pai
                        if (primeiro) { // caso em que vizinho é o primeiro visitado
                            menorPeso=grafo[i][p[i].arestas[j]]; // armazenando na variavel, por ser o primeiro ainda (nao ter comparado com ninguem)
                            orig=i; // esse vertice passa a ser a origem
                            dest=p[i].arestas[j]; // variavel destino: o vertice vizinho no qual o vertice original está ligado
                            primeiro=0; // nao é mais o primeiro
                        }
                        else { // caso em que vizinho tem pai
                            if (menorPeso>grafo[i][p[i].arestas[j]]) { // caso tenha ligação menor do que a variavel "menorPeso"
                                menorPeso=grafo[i][p[i].arestas[j]]; // armazena valor
                                orig=i; // esse vertice passa a ser a origem
                                dest=p[i].arestas[j]; // variavel destino: o vertice vizinho no qual o vertice original está ligado
                            }
                        }
                    }
                }
            }
        }
        if (primeiro==1) // se primeiro continua 1 depois de toda a iteração, nao achou ninguem, logo, sai do while
            break;
        pai[dest]=orig; // caso contrario, o pai do vertice vizinho vai ser o vertice original
    }
}

int main () {
    FILE *ent, *sai; // declarando os arquivos de entrada e saida
    ent=fopen("C:\\Lab7\\entrada7.txt","r"); // abrindo arquivo de entrada
    sai=fopen("C:\\Lab7\\LucasdoVale7.txt","w"); // abrindo arquivo de saida
    int i=0,j,k,custo,total=0; // i=numero de vertices-1; j,k= utilizados para iterações; custo=custo lido no arquivo; total= custo total minimo a ser calculado
    char lixo[50],predio[12]; // strings do arquivo que serão lidas, como lixo ou nao
    for (j=0;j<6;j++) // lendo os lixos
        fgets(lixo,50,ent);
    fscanf(ent,"%s ", predio); // lendo o nome do primeiro predio
    strcpy(p[i].nome,predio); // armazenando nome do primeiro predio
    p[i].num=i; // armazenando o numero do primeiro vertice
    i++; // proximo vertice
    fscanf(ent,"%s ", predio);
    strcpy(p[i].nome,predio);
    p[i].num=i;
    fscanf(ent,"%d ", &custo); // lendo o custo da aresta
    grafo[0][1]=custo; // armazenando na matriz de adjacência
    grafo[1][0]=custo;
    while (!feof(ent)) { // enquanto o arquivo nao acaba, continuar lendo
        fscanf(ent,"%s ", predio); // lendo o primeiro predio
        j=0;
        while (strcmp(p[j].nome,predio)!=0 && j<=i) // procurando se ja existe o vertice lido em primeiro
            j++;
        if (j>i) { // caso em que nao existe tal vertice
            i=j;
            strcpy(p[i].nome,predio);
            p[i].num=i;
            fscanf(ent,"%s ", predio); // lendo o proximo predio
            j=0;
            while (strcmp(p[j].nome,predio)!=0 && j<=i)
                j++;
            if (j>i) { // caso em que nao existe nem o primeiro nem o segundo predio
                i=j;
                strcpy(p[i].nome,predio); // armazenando vertice
                p[i].num=i;
                fscanf(ent,"%d ", &custo); // lendo o custo
                grafo[j][j-1]=custo; // armazenando na matriz de adjacência
                grafo[j-1][j]=custo;
            }
            else { // caso em que nao existe o primeiro predio, mas o segundo sim
                fscanf(ent,"%d ", &custo); // lendo o custo
                grafo[j][i]=custo; // armazenando na matriz de adjacência
                grafo[i][j]=custo;
            }
        }
        else { // caso em que existe esse vertice
            k=j;
            fscanf(ent,"%s ", predio); // lendo o proximo predio do arquivo
            j=0;
            while (strcmp(p[j].nome,predio)!=0 && j<=i) // procurando se ja existe esse predio
                j++;
            if (j>i) { // caso em que existe o primeiro predio, mas nao existe o segundo
                i=j;
                strcpy(p[i].nome,predio); // armazenando o novo vertice
                p[i].num=i;
                fscanf(ent,"%d ", &custo); // lendo o custo
                grafo[k][i]=custo; // armazenando na matriz de adjacência
                grafo[i][k]=custo;
            }
            else { // caso em que já existem o primeiro e o segundo predio lidos
                fscanf(ent,"%d ", &custo); // lendo o custo
                grafo[j][k]=custo; // armazenando na matriz de adjacência
                grafo[k][j]=custo;
            }
        }
    }
    for(k=0;k<i+1;k++) {
        for (j=0;j<i+1;j++) {
            if (grafo[k][j]!=0) { // caso em que existe ligação entre vertices
                p[k].arestas[p[k].grau]=j; // armazenando o vertice ligado ao vertice k
                p[k].grau++; // aumentando um grau do vertice k
            }
        }
    }
    int pai[i+1]; // criando vetor que armazenara os "pais" de cada vertice para o custo minimo
    algPrim(0,pai,i+1); // chamando o algoritmo
    for(j=0;j<i+1;j++) {
        total+=grafo[j][pai[j]]; // calculando custo total minimo
    }
    PCM v[150]; // declarando o vetor de structs para ser ordenado
    for (k=0;k<i+1;k++) { // armazenando as informaçoes do vetor pai na struct
        v[k].pai=pai[k];
        v[k].filho=k;
    }
    fprintf(sai,"Algoritmo do Werneck\n"); // printando no arquivo de saida
    fprintf(sai,"O mais cabuloso para achar o custo minimo\n");
    fprintf(sai,"Relatorio\n\n");
    fprintf(sai,"---------------------------------------\n");
    fprintf(sai,"Ordem de selecao pelo algoritmo\n");
    fprintf(sai,"---------------------------------------\n");
    for(j=1;j<i+1;j++) { // printando as arestas de acordo com a selecao do algoritmo
        fprintf(sai,"%-10s %-10s %3d\n", p[pai[j]].nome, p[j].nome, grafo[j][pai[j]]);
    }
    fprintf(sai,"\nCusto total: %d\n\n",total);
    fprintf(sai,"---------------------------------------\n");
    fprintf(sai,"Ordem crescente de custos\n");
    fprintf(sai,"---------------------------------------\n");
    BubbleSort(v,i+1); // ordenando o vetor de structs
    for(j=1;j<i+1;j++) { // printando o vetor ordenado
        fprintf(sai,"%-10s %-10s %3d\n", p[v[j].pai].nome, p[v[j].filho].nome, grafo[v[j].filho][v[j].pai]);
    }
    fclose(ent); // fechando os arquivos
    fclose(sai);
    return 0;
}

