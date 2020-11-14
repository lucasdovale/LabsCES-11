/* Lucas do Vale Bezerra                    */
/* Turma 3                                  */
/* Exercício 6: Agenda                      */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Prof. Armando                            */
/* Novembro de 2018                          */
/* Programa compilado com CodeBlocks 13.12  */

#include <stdio.h> // declarando bibliotecas
#include <stdlib.h>
#include <string.h>

typedef struct noh noh;

struct noh { // definindo struct noh, contendo a tarefa e a prioridade dela
    char tarefa [72];
    int prioridade;
};

typedef struct heap heap;

struct heap { // struct heap explicada no enunciado do exercício
    noh *vet;
    int quant;
    int MAX;
};

void Insert (heap *H, char nome[], int p) { // função que insere um noh no heap
    int i=H->quant+1; // proxima posição não ocupada
    noh aux; // noh auxiliar
    strcpy(H->vet[H->quant+1].tarefa,nome); // inserindo as informações no noh
    H->vet[H->quant+1].prioridade=p;
    while (i!=1) { // enquanto não chegar na raiz
        if(H->vet[i].prioridade>H->vet[i/2].prioridade) { // caso em que filho tem prioridade maior que o pai
            aux=H->vet[i]; // trocando filho com pai
            H->vet[i]=H->vet[i/2];
            H->vet[i/2]=aux;
        }
        i=i/2; // i vai pro pai
    }
    H->quant++; // aumentando o quant do heap
}

void RemoveMax (heap *H) { // função que remove um noh do heap
    int i=1,pai=1,esq,dir,maior;
    noh aux;
    H->vet[pai]=H->vet[H->quant]; // removendo o primeiro elemento, de modo que o ultimo elemento passe a ser o primeiro
    H->vet[H->quant].prioridade=0; // colocando prioridade 0 no ultimo elemento que passou a ser a "raiz"
    H->quant--; // diminuindo o quant do heap
    while(i<=(H->quant)/2) { // enquanto nao chegar no ultimo pai
        pai=i; // definindo o pai e seus filhos
        esq=2*i;
        dir=2*i+1;
        if (H->vet[esq].prioridade<H->vet[dir].prioridade) // caso em que filho direito é maior que esquerdo
            maior=dir;
        else maior=esq; // caso contrario
        if (H->vet[pai].prioridade<H->vet[maior].prioridade) { // trocando o noh que esta na raiz com o filho maior
            aux=H->vet[pai];
            H->vet[pai]=H->vet[maior];
            H->vet[maior]=aux;
        }
        i++; // continuacao do ciclo
    }
}

noh Max (heap *H) { // consultar a "raiz"
    return H->vet[1];
}

void Inicializar (heap *H, int num) { // Inicializando o vetor do heap
    H->MAX=num; // numero lido na main
    H->vet=(noh*)malloc((num+1)*sizeof(noh)); // alocando memoria no vetor
    H->quant=0; // definindo quant=0
    int i=1;
    while(i<=H->quant) { // definindo todo noh que não está preenchido com prioridade 0
        H->vet[i].prioridade=0;
        i++;
    }
}

void Finalizar (heap *H) { // dando free em todo o vetor do heap
    free(H->vet);
}

bool HeapVazio (heap *H) { // função que verifica se heap vazio
    if(H->quant==0)
        return 1;
    else return 0;
}

bool HeapCheio (heap *H,int MAX) { // função que verifica se heap cheio
    if(H->quant==MAX)
        return 1;
    else return 0;
}

int main () {
    FILE *ent, *sai; // declarando os arquivos de entrada e saida
    ent=fopen("C:\\Lab6\\entrada6.txt","r"); // abrindo arquivo de entrada
    sai=fopen("C:\\Lab6\\LucasdoVale6.txt","w"); // abrindo arquivo de saida
    noh q; // declarando struct noh que será utilizada como auxiliar
    int i,num; // variavel inteira para iterações e variavel que armazena o numero maximo de elementos do vetor
    char lixo[72],mensagem[9],nome[72]; // strings do arquivo que serão lidas
    fprintf(sai,"Werneck's Schedule\n"); // printando o começo do arquivo de saida
    fprintf(sai,"A agenda mais\n");
    fprintf(sai,"INSANA\n");
    fprintf(sai,"que esse H8 ja viu!\n");
    fprintf(sai,"\n");
    heap raiz; // declarando o heap
    for(i=0;i<9;i++)  { // armazenando strings das 9 primeiras linhas no lixo
        if (i==5) // linha que fornece o numero maximo de elementos do vetor
            fscanf(ent,"%d ", &raiz.MAX);
        else fgets(lixo,72,ent); // lendo strings nao importantes
    }
    fscanf(ent,"%s ", mensagem); // lendo a mensagem
    Inicializar(&raiz,raiz.MAX); // inicializando o heap
    if((noh*)malloc((num+1)*sizeof(noh))==NULL) { // caso em que MAX é muito grande
        fprintf(sai,"Agenda com numero de tarefas limitado!\n\n");
        exit(0);
    }
    fprintf(sai, "--------------------------------------------------\n"); // printando no arquivo de saida
    fprintf(sai, "RESPOSTAS DAS CONSULTAS\n");
    fprintf(sai, "--------------------------------------------------\n");
    while (strcmp(mensagem,"FIM")!=0) { // enquanto o arquivo nao acaba, continuar lendo mensagem
        if(strcmp(mensagem,"NOVA")==0) { // caso para inserir tarefa
            if (HeapCheio(&raiz,raiz.MAX)) // caso em que agenda cheia
                fprintf(sai,"ERRO     Agenda cheia. Impossivel inserir.\n");
            else { // caso contrário
                fscanf(ent,"%2d ",&num); // lendo prioridade do elemento a ser inserido
                fgets(nome,72,ent);
                Insert(&raiz,nome,num);
            }
        }
        if (strcmp(mensagem,"PROXIMA")==0) { // caso para remover o elemento de maior prioridade
            if (HeapVazio(&raiz)) // caso em que agenda vazia
                fprintf(sai,"AVISO    Nao ha tarefas na agenda  :-)\n");
            else { // caso contrario
                q=Max(&raiz); // struct q recebe o elemento de maior prioridade q sera removido
                fprintf(sai,"%2d       ",q.prioridade); // printando tal elemento
                fprintf(sai, "%s", q.tarefa);
                RemoveMax(&raiz); // removendo tal elemento
            }
        }
        fscanf(ent,"%s ", mensagem); // lendo a nova mensagem para que se continue o ciclo
    }
    fprintf(sai,"\n--------------------------------------------------\n"); // printando o final do arquivo de saida
    fprintf(sai,"FICA PARA O DIA SEGUINTE\n");
    fprintf(sai,"--------------------------------------------------\n");
    if (HeapVazio(&raiz)) // caso em que agenda vazia após as consultas
        fprintf(sai,"Agenda vazia! Nao restam tarefas para o dia seguinte.");
    else { // caso contrario
        while(raiz.quant!=0) { // enquanto ainda houver elemento
            q=Max(&raiz); // descobrindo elemento de maior prioridade
            fprintf(sai,"%2d       ",q.prioridade); // printando ele
            fprintf(sai,"%s",q.tarefa);
            RemoveMax(&raiz); // removendo ele
        }
    }
    Finalizar(&raiz); // dando free em todo o vetor
    fclose(ent); // fechando os arquivos
    fclose(sai);
    return 0;
}
