/* Lucas do Vale Bezerra                    */
/* Turma 3                                  */
/* Exercício 4: Banco                       */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Prof. Armando                            */
/* Outubro de 2018                          */
/* Programa compilado com CodeBlocks 13.12  */

#include <stdio.h> // declarando bibliotecas
#include <stdlib.h>
#include <string.h>

FILE *ent, *sai; // declarando os arquivos de entrada e saida

int MAX; // declarando a variavel que armazena o numero maximo de contas lido no arquivo

typedef struct conta conta;

typedef struct listaCirc lista;

struct conta { // declarando a struct conta de cada cliente, onde contém o nome e o saldo
    char nome[22];
    float saldo;
};

struct listaCirc { // declarando a lista circular sendo uma struct com um vetor e com indicadores de inicio, fim e quant
    conta *vet;
    int ini,fim,quant;
};

void InicializaLista (lista *L, int MAX) { // função que inicializa a lista circular
    L->vet=(conta *)malloc(MAX*sizeof(conta)); // alocando a memoria no vetor
    if((conta *)malloc(MAX*sizeof(conta))==NULL) { // caso em que MAX é muito grande
        fprintf(sai,"Banco com numero de contas limitado!\n\nTá de sacanagem, né?");
        exit(0);
    }
    L->ini=0; // definindo as variaveis da struct
    L->fim=0;
    L->quant=0;
}

int Busca(char nome[], lista *L, int MAX) { // função que busca um cliente e retorna sua posição na lista
    if (L->quant==0) // caso em que lista vazia
        return -1;
    int i, med;
    med=(L->ini+(L->quant-1)/2)%MAX; // posição do meio do vetor
    if(strcmp(nome,L->vet[med].nome)>=0) { // caso o nome a ser inserido seja maior (ordem alfabetica) do que o do meio
        i=L->fim;
        while (strcmp(L->vet[i].nome,nome)!=0 && i!=med) // achando a posicao do nome
            i=(i-1+MAX)%MAX;
    }
    else { // caso contrario
        i=L->ini;
        while (strcmp(L->vet[i].nome,nome)!=0 && i!=med) // achando a posicao do nome
            i=(i+1)%MAX;
    }
    if (strcmp(L->vet[i].nome,nome)==0) // caso o i tenha saido do while por que achou o nome, retorna a posicao
        return i;
    else return -1; // caso contrario, nao existe
}

void AbreConta (char nome[], lista *L, int MAX) { // função que abre uma nova conta
    int med,i=L->ini;
    if (L->quant==MAX) // caso em que lista cheia
        fprintf(sai,"ERRO: Lista lotada. Impossível abrir conta!\n");
    else if (L->quant==0) { // caso em que lista vazia
            strcpy(L->vet[0].nome,nome);
            L->ini=0;
            L->fim=0;
            L->vet[0].saldo=0;
            L->quant++;
        }
        else if (Busca(nome,L,MAX)!=-1) { // caso em que já existe cliente com esse nome
            fprintf(sai,"ERRO: Já existe cliente com nome %s",nome);
        }
            else {
                med=(L->ini+(L->quant-1)/2)%MAX; // posicao media do vetor
                while (strcmp(nome,L->vet[i].nome)>0 && i!=(L->fim+1)%MAX) // achando a posicao a ser inserido o nome (na ordem alfabetica)
                    i=(i+1)%MAX;
                if (strcmp(nome,L->vet[med].nome)>0) { // caso a posicao seja maior que o med
                    if(i!=(L->fim+1)%MAX) // caso em que a posição não é a última
                        for(int j=L->fim+1;j!=i;j=(j-1+MAX)%MAX) // shiftando
                            L->vet[j]=L->vet[(j-1+MAX)%MAX];
                    strcpy(L->vet[i].nome,nome); // criando nova conta com esse nome
                    L->vet[i].saldo=0;
                    L->fim=(L->fim+1)%MAX; // atualizando indicador fim
                }
                else { // caso em que a posicao é menor que o med
                    if (i!=L->ini) // caso em que a posicao nao é o inicio
                        for(int j=(L->ini-1+MAX)%MAX;j!=(i-1+MAX)%MAX;j=(j+1)%MAX) // shiftando
                            L->vet[j]=L->vet[(j+1)%MAX];
                    strcpy(L->vet[(i-1+MAX)%MAX].nome,nome); // criando nova conta com esse nome
                    L->vet[(i-1+MAX)%MAX].saldo=0;
                    L->ini=(L->ini-1+MAX)%MAX; //atualizando indicador ini
                }
                L->quant++; // atualizando o contador quant
            }
}

void FechaConta (char nome[], lista *L, int MAX) { // função que fecha uma conta já existente
    int posic,med;
    if (L->quant==0) // caso em que lista vazia
        fprintf(sai,"ERRO: A lista está vazia!\n");
    else {
        posic=Busca(nome,L,MAX); // achando posição do cliente que quer fechar a conta
        if (posic==-1) // caso em que nao existe ninguem com esse nome para fechar a conta
            fprintf(sai,"ERRO: Não encontrado cliente com nome %s",nome);
        else {
            med=(L->ini+(L->quant-1)/2)%MAX; // posicao media do veotr
            if (strcmp(L->vet[posic].nome,L->vet[med].nome)>=0) { // caso em que o nome da posicao achada vem depois do que o da posicao med (ordem alfabetica)
                if (L->quant%2!=0) { // caso em que temos uma quantidade ímpar de clientes
                    for(int i=posic;i!=L->fim;i=(i+1)%MAX) // shiftando
                        L->vet[i]=L->vet[(i+1)%MAX];
                    L->fim=(L->fim-1+MAX)%MAX; // atualizando fim
                }
                else { // caso em que temos uma quantidade par de clientes
                    for(int i=posic;i!=L->ini;i=(i-1+MAX)%MAX) // shiftando
                        L->vet[i]=L->vet[(i-1+MAX)%MAX];
                    L->ini=(L->ini+1)%MAX; // atualizando inicio
                }
            }
            else {
                for(int i=posic;i!=L->ini;i=(i-1+MAX)%MAX) // shiftando
                    L->vet[i]=L->vet[(i-1+MAX)%MAX];
                L->ini=(L->ini+1)%MAX; // atualizando inicio
            }
            L->quant--; // atualizando contador quant
        }
    }
}

void Extrato (char nome[], lista *L) { // função que printa no arquivo o extrato de um cliente (seu saldo)
    int p;
    p=Busca(nome, L, MAX); // achando a posição do cliente
    if (p==-1) // caso em que não existe esse cliente
        fprintf(sai,"ERRO: Nao encontrado cliente com nome %s",nome);
    else fprintf(sai,"Saldo  %8.2f  %s",L->vet[p].saldo,nome); // caso em que existe o cliente
}

void Saque (char nome[], float saque, lista *L) { // função que executa um saque na conta de algum cliente
    int p;
    p=Busca(nome, L, MAX); // achando a posição do cliente
    if (p!=-1) // caso em que existe cliente
        L->vet[p].saldo-=saque; // sacando
    else fprintf(sai,"ERRO: Nao encontrado cliente com nome %s",nome); // caso em que não existe esse cliente
}

void Deposito (char nome[], float deposito, lista *L) { // função que executa um deposito na conta de algum cliente
    int p;
    p=Busca(nome,L,MAX); // achando a posição para depositar
    if (p!=-1) // caso em que existe cliente
        L->vet[p].saldo+=deposito; // depositando
    else fprintf(sai,"ERRO: Nao encontrado cliente com nome %s",nome); // caso em que nao existe esse cliente
}

int main () { // função main
    ent=fopen("C:\\Lab4\\entrada4.txt","r"); // abrindo arquivo de entrada
    sai=fopen("C:\\Lab4\\LucasdoVale4.txt","w"); // abrindo arquivo de saida
    int i; // variavel inteira para iterações
    float deposito,saque; // variaveis para deposito e saque
    lista L; // declarando a lista L que iremos trabalhar
    char lixo [52],mensagem[13],nome[22]; // strings do arquivo que serão lidas
    fprintf(sai,"Werneck Bank\n"); // printando o começo do arquivo de saida
    fprintf(sai,"============\n");
    fprintf(sai," Relatório\n\n");
    fprintf(sai,"RESULTADO DAS CONSULTAS\n\n");
    for(i=0;i<6;i++) { // armazenando strings das 7 primeiras linhas no lixo (com exceção do numero max de contas que será armazenada)
        if (i==5)
            fscanf(ent,"%d ", &MAX); // lendo o numero maximo de contas
        fgets(lixo,52,ent); // lendo strings nao importantes
    }
    if (MAX==0) { // caso em que o MAX é 0
        fprintf(sai, "Nao existe nenhum cliente!\n\n");
        return 0;
    }
    InicializaLista(&L,MAX); // inicializando a lista L
    fscanf(ent,"%s ", mensagem); // lendo a primeira mensagem
    while (strcmp(mensagem,"FIM")!=0) { // ler as mensagens até que se chegue no FIM
        if (strcmp(mensagem,"ABRE_CONTA")==0) { // caso em que a mensagem seja ABRE_CONTA
            fgets(nome,22,ent); // lendo o nome do novo cliente
            AbreConta(nome,&L,MAX); // abrindo conta pra ele
        }
        if (strcmp(mensagem,"FECHA_CONTA")==0) { // caso em que mensagem seja FECHA_CONTA
            fgets(nome,22,ent); // lendo o nome cliente que quer fechar conta
            FechaConta(nome,&L,MAX); // fechando conta do cliente
        }
        if (strcmp(mensagem,"DEPOSITO")==0) { // caso em que há um deposito em alguma conta
            fscanf(ent,"%f ", &deposito); // lendo a quantidade a ser depositada
            fgets(nome,22,ent); // lendo o nome de quem receberá o deposito
            Deposito(nome,deposito,&L); // depositando o valor na conta
        }
        if (strcmp(mensagem,"SAQUE")==0) { // caso em que há um saque de alguma coisa
            fscanf(ent,"%f ", &saque); // lendo a quantidade a ser sacada
            fgets(nome,22,ent); // lendo o nome de quem fará o saque
            Saque(nome,saque,&L); // sacando a grana
        }
        if (strcmp(mensagem,"EXTRATO")==0) { // caso em que se pede extrato de algum cliente
            fgets(nome,22,ent); // lendo o nome do cliente que pede extrato
            Extrato(nome,&L); // mostrando o extrato
        }
        fscanf(ent,"%s ", mensagem); // lendo a nova mensagem para que se continue o ciclo
    }
    fprintf(sai,"\nRELATORIO FINAL\n\n"); // printando as mensagens finais no arquivo
    fprintf(sai,"Tamanho maximo da lista:   %5d\n", MAX);
    fprintf(sai,"Total de correntistas:     %5d\n",L.quant);
    fprintf(sai,"Posicoes ocupadas:  inicio:%5d\n                       fim:%5d\n",L.ini, L.fim);
    fprintf(sai,"\nCORRENTISTAS ATUAIS\n\n");
    for(int cont=0;cont<L.quant;cont++) // printando os correntistas atuais
        fprintf(sai,"%8.2f  %s",L.vet[(L.ini+cont)%MAX].saldo,L.vet[(L.ini+cont)%MAX].nome);
    fclose(ent); // fechando os arquivos
    fclose(sai);
    return 0;
}
