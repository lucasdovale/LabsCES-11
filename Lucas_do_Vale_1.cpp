/* Lucas do Vale Bezerra                    */
/* Turma 3                                  */
/* Exerc�cio 1: Produto de Matrizes         */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Prof. Armando                            */
/* Agosto de 2018                           */
/* Programa compilado com CodeBlocks 13.12  */

#include <stdio.h>
#include <stdlib.h>

FILE *ent, *sai; // declarando os arquivos de entrada e saida

#define max 22 // declarando o numero maximo possivel para N+1 globalmente (pois utilizei a constante max para o vetor de dimens�es e para a matriz de melhor corte
// dim: vetor que armazena as dimens�es das matrizes, no caso, (N+1) dimens�es. mc: matriz que armazena os melhores cortes
int dim[max],chamadas=0,mc[max][max]={0}; // declarando algumas variaveis globais que ser�o utilizadas por varias funcoes

void melhorCorte (int i, int j) { // funcao recursiva necessaria para printar as melhores ordens
    if(j==i) // caso em que n�o faz sentido, pois i deve ser > j, no entanto, s�o casos que aparecem na recurs�o
        return;
    if(j==i+1) // caso em que s� existe uma op��o de corte (duas matrizes apenas)
        fprintf(sai,"%4d x %2d\n", i, j);
    else {
            melhorCorte(i,mc[i][j]); // recurs�o dividida em dois ramos
            melhorCorte(mc[i][j]+1,j);
            if (i==mc[i][j])   // caso em que o indice da matriz inicial � o mesmo do melhor corte
                fprintf(sai,"%4d x %2d-%2d\n",i,mc[i][j]+1,j);
            if (i==mc[i][j]+1) // caso em que esse indice � o consecutivo do melhor corte
                fprintf(sai,"%4d x %2d-%2d\n",i,mc[i][j],j);
            if (j==mc[i][j]) // caso em que o indice da ultima matriz � o mesmo do melhor corte
                fprintf(sai,"%d-%2d x %2d\n",i,mc[i][j]-1,j);
            if (j==mc[i][j]+1) // caso em que esse indice � o consecutivo do melhor corte
                fprintf(sai,"%d-%2d x %2d\n",i,mc[i][j],j);
            if (i!=mc[i][j] && i!=mc[i][j]+1 && j!=mc[i][j] && j!=mc[i][j]+1) // caso em que o melhor corte se encontra entre os indices i e j (matriz inicial e final)
                fprintf(sai,"%d-%2d x %2d-%d\n",i,mc[i][j],mc[i][j]+1,j);
    }
}

int calcularMinimo (int i, int j) { // funcao recursiva para calcular o numero minimo de multiplica��es escalares
    chamadas++; // adicionando uma unidade � vari�vel chamadas a cada vez que a fun��o recursiva � chamada
    int menor,n,k; // declarando variaveis necessarias
    if (i==j) // caso em que n�o existe opera��es
        return 0;
    else {
        for(k=i;k<j;k++) { // testando todos os cortes possiveis
            n=calcularMinimo(i,k)+calcularMinimo(k+1,j)+dim[i]*dim[k+1]*dim[j+1];
            if (k==i || n<=menor) {
                menor=n; // armazenando o menor valor de opera��es com a variavel auxiliar
                mc[i][j]=k; // armazenando o melhor corte para cada i e j
            }
        }
        return menor;
    }
}

int main () {
    ent=fopen("C:\\Lab1\\entrada1.txt","r");
    sai=fopen("C:\\Lab1\\Lucas_do_Vale_1.txt","w");
    int i,N,lixoo; // declarando o i para uso em itera��es, o N para ser o numero de matrizes lido no arquivo e lixoo para armazenar inteiros do arquivo que n�o ser�o utilizados
    char lixo [72]; // strings do arquivo que nao ser�o utilizadas
    for(i=0;i<8;i++) { // armazenando strings das 8 primeiras linhas no lixo
        if (i==5)
            fscanf(ent,"%d", &N);
        fgets(lixo,72,ent);
    }
    for(i=1;i<N+1;i++) { // armazenando as dimens�es das matrizes
        fscanf(ent,"%d",&dim[i]);
        if (i==N)
            fscanf(ent,"%d",&dim[i+1]);
        else fscanf(ent,"%d",&lixoo);
    }
    fprintf(sai,"Exemplo de arquivo de saida\nExercicio 1\nProduto de Matrizes\n\n");
    fprintf(sai,"Total de multiplicacpes escalares = %d\n\n", calcularMinimo(1,N)); // chamando a fun��o calcularMinimo
    fprintf(sai,"Chamadas aa funcao: %d\n\n", chamadas);
    fprintf(sai,"Melhor ordem para realizar o produto:\n");
    for (int i=1;i<N+1;i++) // preenchendo alguns valores necess�rios de melhor corte na matriz mc[N][N]
        for(int j=1;j<N+1;j++)
            if (j==i+1)
                mc[i][j]=i;
    melhorCorte(1,N); // chamando a fun��o recursiva melhorCorte
    fclose(ent);
    fclose(sai);
    return 0;
}
