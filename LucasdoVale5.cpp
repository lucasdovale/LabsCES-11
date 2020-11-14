/* Lucas do Vale Bezerra                    */
/* Turma 3                                  */
/* Exercício 5: Livro                       */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Prof. Armando                            */
/* Outubro de 2018                          */
/* Programa compilado com CodeBlocks 13.12  */

#include <stdio.h> // declarando bibliotecas
#include <stdlib.h>
#include <string.h>

FILE *ent, *sai; // declarando os arquivos de entrada e saida

typedef struct secao secao; //chamando toda a struct secao de secao

int cont=0,itemi[9]={0},altura=0; // declarando variaveis globais para a função lista

secao *raiz; // declarando a raiz da arvore

struct secao { //declarando a struct que sera cada noh da nossa arvore
    char nome [22];
    secao *pai,*filhoesq,*irmaodir;
};

secao* Busca (char nome[], secao *A) { // funcao recursiva que Busca elemento na arvore (passada em sala pelo Armando)
    secao *resposta;
    secao *p;
    if (strcmp(nome,A->nome)==0)
        return A;
    else {
        resposta=NULL;
        p=A->filhoesq;
        while (p!=NULL && resposta==NULL) {
            resposta=Busca(nome,p);
            p=p->irmaodir;
        }
        return resposta;
    }
}

void InserirTitulo(secao **A) { // funcao para inserir titulo
    char titulo[22];
    fscanf(ent,"%s ",titulo);
    if (*A==NULL) { // caso em que ainda não há titulo
        *A=(secao*)malloc(sizeof(secao));
        strcpy((*A)->nome,titulo);
        (*A)->filhoesq=NULL;
        (*A)->irmaodir=NULL;
        (*A)->pai=NULL;
    }
    else { // caso em que ja existe titulo e queremos substituir
        secao *aux;
        aux=(secao*)malloc(sizeof(secao));
        strcpy(aux->nome,titulo);
        aux->pai=NULL;
        aux->irmaodir=NULL;
        aux->filhoesq=*A;
        *A=aux;
    }

}

void Inserir (char nome[], secao *A) { // funcao que insere elemento na arovre
    secao *p,*q,*aux; // declarando ponteiros que serao utilizados nas manipulaçoes
    char tipo[12], pai[22]; // declarando strings que serao lidas
    fscanf(ent,"%s ",tipo); // lendo strings
    fscanf(ent,"%s ",pai);
    p=Busca(pai,A); // buscando o pai do elemento a ser inserido
    if (p==NULL) // caso em que elemento nao é achado pela Busca
        fprintf(sai,"ERRO: nao encontrado item %s\n--------------------------------------------------\n", pai);
    else { // caso em que pai é achado
        aux=p;
        if (strcmp(tipo,"SUB")==0) { // caso em que queremos inserir como subarvore do pai achado
            q=p->filhoesq;
            p->filhoesq=(secao*)malloc(sizeof(secao));
            p=p->filhoesq;
            p->pai=aux;
            p->irmaodir=q;
        }
        if(strcmp(tipo,"SEGUINTE_A")==0) { // caso em que queremos inserir como irmao direito do pai achado
            if (p->pai!=NULL) {
                q=p->irmaodir;
                p->irmaodir=(secao*)malloc(sizeof(secao));
                p=p->irmaodir;
                p->pai=aux->pai;
                p->irmaodir=q;
            }
        }
        p->filhoesq=NULL;
        strcpy(p->nome,nome);
    }
}

void Remover (char nome[], secao *A) { // funcao que remove elemento da arvore
        secao *p,*q; // declarando ponteiros a serem utilizados
        p=Busca(nome,A); // buscando elemento a ser removido
        if (p==NULL) // caso em que busca nao acha o elemento
            fprintf(sai,"ERRO: nao encontrado item %s\n--------------------------------------------------\n", nome);
        else { // caso em que há elemento
            q=p->pai;
            if (q->filhoesq==p) {
                q->filhoesq=p->irmaodir;
            }
            else {
                q=q->filhoesq;
                while (q->irmaodir!=p)
                q=q->irmaodir;
                q->irmaodir=p->irmaodir;
            }
            while(p->filhoesq !=NULL)
                Remover(p->filhoesq->nome, p); // chamando recursivamente para o filho esquerdo para das free todos
            free(p); // dando free
       }
}

void Lista (secao *A) { // funcao que imprime no arquivo o sumario do livro
        secao *p;
        p=A;
        if (raiz==NULL) {
            fprintf(sai,"Lista Vazia!!!\n");
            return;
        }
        if(p==NULL) // caso p for NULL, acaba a funcao
            return;
        else { // caso contrario
            for (int i=1;itemi[i]!=0;i++) // printa o vetor criado
                fprintf(sai,"%d.",itemi[i]);
            fprintf(sai,"      %s\n",p->nome); // printa o nome do indice do livro
            if (p->filhoesq!=NULL) { // caso haja filho esquerdo
                altura++; // aumenta a altura, pois vamos chamar recursivamente para filho esquerdo
                itemi[altura]++;  // aumenta o item com indice altura
                p=p->filhoesq;
                Lista(p); // chama recursivamente para filho esquerdo
                while (p->irmaodir!=NULL) { // enquanto irmao direito nao for o ultimo
                    p=p->irmaodir;
                    itemi[altura]++; // aumenta o item de indice altura
                    Lista(p); // chama recursivamente para o irmao direito
                }
            }
            else { // caso em que nao ha filho esquerdo
                altura++; // aumenta a altura, mas será subtraido no final da funcao
                itemi[altura]++; // aumenta o item, mas será subtraido no final da funcao
            }
        }
        if (p->irmaodir!=NULL) { // caso em que irmao direito nao é NULL
            itemi[altura]--;
            altura--;
        }
        else { // caso em que irmao direito é NULL, a funcao deve sair da recursao e zerar o item de indice altura
            itemi[altura]=0;
            altura--;
        }
}

void Transferir (char nome[], secao *A) { // funcao que transfere um elemento da arvore
    secao *p,*q,*aux; // declarando ponteiros necessarios para manipulação
    char tipo[12], pai[22]; // declarando strings que serao lidas
    fscanf(ent,"%s ",tipo); // lendo strings
    fscanf(ent,"%s ",pai);
    p=Busca(pai,A); // buscando as strings lidas
    q=Busca(nome,A);
    if (p==NULL) // caso em que a Busca retorna NULL, ou seja, não encontrou a string procurada
        fprintf(sai,"ERRO: nao encontrado item %s\n--------------------------------------------------\n", pai);
    else { // caso em que existe a string procurada
        if (strcmp(tipo,"SUB")==0) { // caso em que transferimos para subarvore (filho esquerdo)
            aux=q->pai;
            if (aux->filhoesq==q) { // caso em que o elemento é filho esquerdo do seu pai
                aux->filhoesq=q->irmaodir; // temos que mudar o ponteiro filho esquerdo do pai para o novo elemento que transferimos
                q->irmaodir=p->filhoesq;
                p->filhoesq=q;
            }
            else if (q->irmaodir==NULL) { // caso em que queremos transferir no ultimo irmao direito
                    q->irmaodir=p->filhoesq;
                    p->filhoesq=q;
                    aux=aux->filhoesq;
                    while (aux->irmaodir!=q)
                        aux=aux->irmaodir;
                    aux->irmaodir=NULL;
                }
                else { // caso em que queremos transferir para um outro elemento qualquer que nao seja um dos outros dois casos
                    aux=aux->filhoesq;
                    while (aux->irmaodir!=q)
                        aux=aux->irmaodir;
                    aux->irmaodir=q->irmaodir;
                    q->irmaodir=p->filhoesq;
                    p->filhoesq=q;
                }
            }
        if(strcmp(tipo,"SEGUINTE_A")==0) { // caso em que transferimos para seguinte arvore (irmao direito)
            if (q->pai!=NULL) {
                aux=q->pai;
                if (aux->filhoesq==q) { // analogo
                    aux->filhoesq=q->irmaodir;
                    q->irmaodir=p->irmaodir;
                    p->irmaodir=q;
                }
                else if (q->irmaodir==NULL) { // analogo
                        q->irmaodir=p->irmaodir;
                        p->irmaodir=q;
                        aux=aux->filhoesq;
                        while (aux->irmaodir!=q)
                            aux=aux->irmaodir;
                        aux->irmaodir=NULL;
                    }
                    else { // analogo
                        aux=aux->filhoesq;
                        while (aux->irmaodir!=q)
                            aux=aux->irmaodir;
                        aux->irmaodir=q->irmaodir;
                        q->irmaodir=p->irmaodir;
                        p->irmaodir=q;
                    }
            }
        }
    }
}

int main () { // função main
    ent=fopen("C:\\Lab5\\entrada5.txt","r"); // abrindo arquivo de entrada
    sai=fopen("C:\\Lab5\\LucasdoVale5.txt","w"); // abrindo arquivo de saida
    int i; // variavel inteira para iterações
    char lixo[72],mensagem[13],nome[22]; // strings do arquivo que serão lidas
    fprintf(sai,"Werneck's Book\n"); // printando o começo do arquivo de saida
    fprintf(sai,"O livro mais cabuloso que voce vai ler\n");
    fprintf(sai,"Sumario\n");
    fprintf(sai,"--------------------------------------------------\n");
    for(i=0;i<4;i++) // armazenando strings das 3 primeiras linhas no lixo
        fgets(lixo,72,ent); // lendo strings nao importantes
    fscanf(ent,"%s ", mensagem);
    raiz=NULL;
    while (strcmp(mensagem,"FIM")!=0) { // enquanto o arquivo nao acaba, continuar lendo mensagem
        if(strcmp(mensagem,"TITULO")==0) // caso para inserir titulo
            InserirTitulo(&raiz);
        if (strcmp(mensagem,"INSERIR")==0) { // caso para inserção
            fscanf(ent,"%s ",nome);
            Inserir(nome,raiz);
        }
        if (strcmp(mensagem,"REMOVER")==0) { // caso para remoção
            fscanf(ent,"%s ",nome);
            if (strcmp(raiz->nome,nome)==0) { // caso em que remove a raiz
                free(raiz);
                raiz=NULL;
            }
            else Remover(nome,raiz);
        }
        if (strcmp(mensagem,"TRANSFERIR")==0) { // caso para trasnferência
            fscanf(ent,"%s ",nome);
            Transferir(nome,raiz);
        }
        if (strcmp(mensagem,"LISTA")==0) {
            cont++;
            fprintf(sai,"LISTA %d\n\n",cont);// caso para Listar os elementos do livro
            Lista(raiz);
            fprintf(sai,"--------------------------------------------------\n");
        }
        fscanf(ent,"%s ", mensagem); // lendo a nova mensagem para que se continue o ciclo
    }
    fclose(ent); // fechando os arquivos
    fclose(sai);
    return 0;
}
