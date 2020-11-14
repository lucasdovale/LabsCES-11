/* Lucas do Vale Bezerra                    */
/* Turma 3                                  */
/* Exerc�cio 8: PERT (Segunda �poca)        */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Prof. Armando                            */
/* Janeiro  de 2019                         */
/* Programa compilado com CodeBlocks 13.12  */

#include <stdio.h> // declarando bibliotecas
#include <stdlib.h>
#include <string.h>

FILE *ent, *sai; // declarando os arquivos de entrada e saida

typedef struct tarefa tarefa;

struct tarefa { // declarando a struct tarefa
    char letra; // letra relacionada � tarefa
    char tarefa[32]; // string do nome da tarefa
    int duracao; // duracao da tarefa
    int vizinhos[51]; // vizinhos de saida de cada noh do grafo
    int dependencia[51]; // vizinhos de entrada de cada noh do grafo
    int grausai; // grau de saida do noh
    int grauent; // grau de entrada do noh
    int visitado; // variavel que ser� utilizada quando o grafo for percorrido
};

tarefa T[51]; // declarando vetor de structs tarefas

int achouCiclo, elementoRepetido, ant[51], TMT[51]={0}, grafo[51][51]={0};
// achouCiclo: vari�vel que determina se algum ciclo foi achado na PreOrdem
// elementoRepetido: o elemento q possivelmente sera repetido na pilha de ciclo (PreOrdem)
// ant: vetor de antecedentes, para que o caminho critico seja montado
// TMT: vetor de TMT's
// grafo: matriz de adjac�ncia
typedef struct pilha pilha;

struct pilha { // declarando a struct pilha
    int vet[51];
    int topo;
};

pilha p,P,ciclo; // declarando pilhas que ser�o posteriormente utilizadas:
// p: pilha que armazena a PosOrdem
// P: pilha que armazena o Caminho Critico
// ciclo: pilha que armazena o ciclo na PreOrdem

void Empilha (pilha *p, int elemento) { // funcao para empilhar elemento na pilha
    p->topo++;
    p->vet[p->topo]=elemento;
}

void Desempilha (pilha *p) { // funcao para desempilhar elemento da pilha
    p->topo--;
}

int ExisteNaPilha (int noh, pilha P) { // fun��o que verifica se algum noh do grafo est� na pilha constru�da (facilita para o teste de aciclicidade)
    int achou=0;
    for (int k=P.topo;k!=0 && achou==0;k--) {
        if (P.vet[k]==noh)
            achou=1;
        else achou=0;
    }
    return achou;
}

int Max (int noh) { // fun��o que verifica qual o maior valor entre os TMT's das depend�ncias de algum noh
    int maior=0;
    for(int i=1;i<=T[noh].grauent;i++) {
        if (TMT[T[noh].dependencia[i]]>maior) {
            maior=TMT[T[noh].dependencia[i]];
            ant[noh]=T[noh].dependencia[i];
        }
    }
    return maior;
}

void TempoMin (int noh, tarefa T[], int n) { //fun��o que calcula os TMT's de cada noh
    if (T[noh].grauent<1) // caso em que s� existe o noh
        TMT[noh]=T[noh].duracao;
    else if (T[noh].grauent==1) { // caso em que o noh s� tem uma depend�ncia
        TMT[noh]=T[noh].duracao+TMT[T[noh].dependencia[1]];
        ant[noh]=T[noh].dependencia[1];
    }
    else // caso em que o noh tem mais de uma depend�ncia
        TMT[noh]=T[noh].duracao+Max(noh);
}

void PreOrdem (int noh, int n) { // DFS: Pr�-Ordem
    int k;
    T[noh].visitado=1; // o noh � visitado assim que � encontrado
    Empilha(&ciclo,noh); // empilhando o noh, para no futuro verificar se h� alguem repetido
    for (int j=1;j<=T[noh].grausai && achouCiclo==0;j++) { // chamando a PreOrdem para todos os vizinhos (de saida) que ainda nao foram visitados
        if (T[T[noh].vizinhos[j]].visitado==0)
            PreOrdem (T[noh].vizinhos[j],n);
        else if (ExisteNaPilha(T[noh].vizinhos[j],ciclo)==1) { // caso o elemento j� exista na pilha, achamos um ciclo
            achouCiclo=1;
            elementoRepetido=T[noh].vizinhos[j]; // armazenando elemento repetido
        }
    }
    if (achouCiclo==0 && n>1) // terminou a PreOrdem relacionada � algum noh, desempilha (caso n�o tenha formado ciclo ainda)
        Desempilha(&ciclo);
}

void PosOrdem (int noh, int n) { // DFS: P�s-Ordem
    for (int j=1;j<=T[noh].grausai;j++) // chamando a PosOrdem para todos os vizinhos (de saida) que ainda nao foram visitados
        if (T[T[noh].vizinhos[j]].visitado==0)
            PosOrdem (T[noh].vizinhos[j],n);
    T[noh].visitado=1; // o noh � visitado no final da PosOrdem dele
    Empilha(&p,noh); // assim que acabar a PosOrdem de um noh, empilha (para que, no futuro, apare�a a Ordem Topol�gica (P�s-Ordem inversa))
}

int TodosVisitados (tarefa T[], int n) { // fun��o que verifica se todos os n�s foram visitados
    int i=1;
    while (T[i].visitado==1 && i<=n)
        i++;
    if (i==n+1)
        return 1;
    else return 0;
}

int ExisteNoGrafo (char letra, int n) { // fun��o que busca no grafo se o elemento com tal letra existe
    int k=1;
    while(letra!=T[k].letra && k<=n)
        k++;
    if (k==n+1)
        return 0;
    else return 1;
}

void percorrerPre (tarefa T[], int n) { // fun��o auxiliar "percorrer" do caderno, especifica para a PreOrdem (voltada para buscar o ciclo)
    int i;
    achouCiclo==0; // atribuindo "FALSE" ao achouCiclo
    for (i=1;i<=n;i++) // atribuindo "FALSE" a todos os n�s, pois nao foram visitados ainda
        T[i].visitado=0;
    while (TodosVisitados(T,n)==0 && achouCiclo==0) { // enquanto houver alguem que nao for visitado e nao tiver achado ciclo, chama a PreOrdem
        i=1;
        while (T[i].visitado==1 && i<n)
            i++;
        if (T[i].visitado==0)
            PreOrdem (i,n);
    }
}


void percorrerPos (tarefa T[], int n) { // fun��o auxiliar "percorrer" do caderno, especifica para a PosOrdem (voltada para a achar a Ordem Topologica)
    int i;
    for (i=1;i<=n;i++) // analogo � fun��o acima
        T[i].visitado=0;
    while (TodosVisitados(T,n)==0) {
        i=1;
        while (T[i].visitado==1 && i<n)
            i++;
        if (T[i].visitado==0)
            PosOrdem (i,n);
    }
}

int main () {
    ent=fopen("C:\\Lab8\\entrada8.txt","r"); // abrindo arquivo de entrada
    sai=fopen("C:\\Lab8\\LucasdoVale8.txt","w"); // abrindo arquivo de saida
    int aux,n=0,i=0,j,k,dur,tempoMin=0; // variaveis iterativas, auxiliares ou que serao lidas do arquivo
    char letra,lixo[72],tarefa[32],prec='\n'; // strings ou letras do arquivo que ser�o lidas, como lixo ou nao
    for (j=0;j<7;j++) // lendo os lixos
        fgets(lixo,72,ent);
    while (prec=='\n') { // enquanto o arquivo nao acaba, continuar lendo
        n++; // aumenta o n
        fscanf(ent," %c", &letra); // lendo o nome do primeiro predio
        fgets(tarefa,32,ent); // lendo a tarefa
        fscanf(ent,"%d ", &dur); // lendo a duracao da tarefa
        if (!ExisteNoGrafo(letra,n)) { // caso em que a letra lida nao corresponde a um n� j� existente no grafo
            T[n].letra=letra; // atribuindo todos os dados lidos � struct
            strcpy(T[n].tarefa,tarefa);
            T[n].duracao=dur;
            aux=n;
        }
        else { // caso em que a letra lida corresponde a alguem j� existente no grafo
            n--; // diminui o n, pois nao deveria ter aumentado
            k=1;
            while (letra!=T[k].letra && k<=n) // buscando o elemento relacionado � letra lida
                k++;
            if (T[k].duracao==-1) { // atribuindo � struct correspondente todos os dados lidos
                strcpy(T[k].tarefa,tarefa);
                T[k].duracao=dur;
            }
            aux=k;
        }
        fscanf(ent,"%c", &prec); // lendo o precendente
        if (prec=='.') // caso em que o prec nao existe
            fscanf(ent,"%c", &prec); // nesse caso, ser� lido um \n, para continuar no while
        else { // caso em que nao � ".", ou seja, � letra
            if (ExisteNoGrafo(prec,n)) { // caso em que o precedente lido ja existe no grafo
                k=1;
                while(prec!=T[k].letra && k<=n) // achando o precedente no grafo
                    k++;
                grafo[k][aux]=1; // atribuindo na matriz de adjac�ncia
            }
            else { // caso em que o precedente nao est� no grafo
                    k=aux;
                    n++; // aumenta o n, pois estamos adicionando um n� no grafo
                    T[n].letra=prec; // atribuindo a letra � struct
                    T[n].duracao=-1; // aqui, fixamos -1 para que, no futuro, seja substituido pela dura��o correta
                    grafo[n][k]=1; // atribuindo na matriz de adjac�ncia
            }
            fscanf(ent,"%c", &prec); // lendo mais um precedente
            while (prec==',') { // caso em que ha mais de um precedente
                fscanf(ent,"%c", &prec); // lendo o proximo precedente
                if (ExisteNoGrafo(prec,n)) { // caso em que o precedente j� existe no grafo
                    k=1;
                    while (prec!=T[k].letra && k<=n) // achando o precedente no grafo
                        k++;
                    grafo[k][n]=1; // atribuindo na matriz de adjacencia
                }
                else { // caso em que precedente nao est� no grafo
                    k=aux;
                    n++; // aumenta o n, pois estamos adicionando um n� no grafo
                    T[n].letra=prec; // atribuindo a letra � struct
                    T[n].duracao=-1; // aqui, fixamos -1 para que, no futuro, seja substituido pela dura��o correta
                    grafo[n][k]=1; // atribuindo na matriz de adjacencia
                }
                fscanf(ent,"%c", &prec); // lendo mais uma letra, que ser� ou ',' ou '\n'
            }
        }
    }
    n--; // n vai sair como x+1, onde x � o numero de vertices do grafo, logo, devemos diminuir 1
    for(k=1;k<=51;k++) { // atribuindo 0 a cada grau de saida e de entrada, apenas para eliminar o lixo, pois ser�o atribuidos de acordo com a matriz de adjac�ncia
        T[k].grauent=0;
        T[k].grausai=0;
    }
    for(k=1;k<=n;k++) { // armazenando grau (de entrada e de saida) e vizinhos (de entrada e de saida) de cada vertice
        for(j=1;j<=n;j++) {
            if (grafo[j][k]!=0) {
                T[k].grauent++;
                T[k].dependencia[T[k].grauent]=j;
            }
            if (grafo[k][j]!=0) { // caso em que existe liga��o entre vertices
                T[k].grausai++;
                T[k].vizinhos[T[k].grausai]=j; // armazenando o vertice ligado ao vertice k
            }
        }
    }
    p.topo=0; // inicializando as pilhas
    P.topo=0;
    ciclo.topo=0;
    fprintf(sai,"Algoritmo do Werneck\n"); // printando no arquivo de saida
    fprintf(sai,"PERT/CPM\n");
    fprintf(sai,"O mais insano para achar o\nCAMINHO CRITICO\n\n");
    fprintf(sai,"------------------------------------------------------------\n\n");
    if (n<1) { // caso em que o arquivo nao fornece nenhum n� para o grafo
        fprintf(sai,"NAO EXISTE NENHUM NOH, LOGO, NAO HA GRAFO! MUITO MENOS CAMINHO CRITICO!!!");
        return 0;
    }
    else if (n>2) // caso em que n>2, ou seja, � poss�vel existir ciclo (por isso, chama a PreOrdem...do contr�rio, n�o precisaria verificar se h� ciclo, pois � impossivel com menos de 3 elementos)
        percorrerPre(T,n); // chama PreOrdem
    if (achouCiclo==1) { // caso em que se achou algum ciclo
        fprintf(sai,"O GRAFO NAO EH ACICLICO! EH IMPOSSIVEL BUSCAR O CAMINHO CRITICO!\n");
        fprintf(sai,"\n\nCICLO ENCONTRADO:");
        k=1;
        while (ciclo.vet[k]!=elementoRepetido && k<=ciclo.topo) // achando o elemento inicial do ciclo achado
            k++;
        while (k!=ciclo.topo+1) {
            fprintf(sai," %c", T[ciclo.vet[k]].letra); // printando o ciclo de acordo com a pilha construida e o elemento achado
            k++;
        }
    }
    else { // caso em que n�o h� ciclo
        fprintf(sai,"UMA ORDENACAO TOPOLOGICA:\n\n");
        percorrerPos(T,n); // chama a PosOrdem
        i=0;
        while (p.topo!=0) { // imprimindo no arquivo a ordem topologica
            k=0;
            while (p.vet[p.topo]!=k && k<51)
                k++;
            TempoMin(p.vet[p.topo],T,n); // utilizando a Ordem Topol�gica para calcular o tempo minimo do projeto
            if (T[k].grausai==0) {
                if (i==0) {
                    i=1;
                    tempoMin=TMT[k];
                    j=k;
                }
                else {
                    if (TMT[k]>tempoMin) {
                        tempoMin=TMT[k];
                        j=k;
                    }
                }
            }
            fprintf(sai,"%c ", T[k].letra); // printando no arquivo a ordem topol�gica
            Desempilha(&p);
        }
        fprintf(sai,"\n\n------------------------------------------------------------\n");
        fprintf(sai,"\nCAMINHO CRITICO:\n");
        fprintf(sai,"\nTAREFA        DESCRICAO           DURACAO\n\n");
        for(k=j;T[k].grauent!=0;k=ant[k]) // descobrindo qual � o caminho cr�tico invertido, que ser�, depois, desinvertido
            Empilha(&P,k);
        fprintf(sai,"  %c%s %4d\n", T[k].letra, T[k].tarefa, T[k].duracao);
        while (P.topo!=0) {
            k=0;
            while (P.vet[P.topo]!=k && k<51)
                k++;
            fprintf(sai,"  %c%s %4d\n", T[k].letra, T[k].tarefa, T[k].duracao); // imprimindo o caminho cr�tico correto
            Desempilha(&P);
        }
        fprintf(sai,"                                   ----\n");
        fprintf(sai,"TEMPO MINIMO PARA O PROJETO:         %2d semanas\n", tempoMin);
    }
    fclose(ent); // fechando os arquivos
    fclose(sai);
    return 0;
}


