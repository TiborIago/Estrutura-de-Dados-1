#include <stdio.h>
#include <stdlib.h>

// DECLARAÇAO DAS STRUCTS

enum boolean{
    true = 1 , false = 0
};
typedef enum boolean bool;

typedef struct Conteudo{
    char nome;
}conteudo;

typedef struct Listadupla{
    struct Conteudo *pagina;
    struct Listadupla *prox;
    struct Listadupla *ant;
}Listadupla;

typedef struct Listasimples{
    struct Conteudo *pagina;
    struct Listasimples *prox;
}Listasimples;

typedef struct Marcador{
    struct Listasimples *inicioSimples;
    struct Listasimples *fimSimples;
    struct Listadupla *inicioDuplo;
    struct Listadupla *fimDuplo;
    struct Listadupla *atual;
    int cont;
}Marcador;

//FUNCAO INCIAR e TESTE DE CHEIO E VAZIO

void iniciaMarcador(Marcador *M){
    M->fimDuplo = NULL;
    M->fimSimples = NULL;
    M->inicioDuplo = NULL;
    M->inicioSimples = NULL;
    M->atual = NULL;
    M->cont = 0;
}

bool ListaSimplesCheia(Marcador *M){
    if(M->cont >=5){
        return true;
    }else{
        return false;
    }
}

bool ListaSimplesVazia(Marcador *M){
    if(M->cont <=0){
        return true;
    }else{
        return false;
    }
}

bool ListaDuplaVazia(Marcador *M){
    if(M->inicioDuplo == NULL){
        return true;
    }else{
        return false;
    }
}

//FUNCAO INSERIR, REMOVER, MOSTRAR O HISTORICO

void removeInicio(Marcador *M){
    Listasimples *aux;
    aux = M->inicioSimples;
    M->inicioSimples = aux->prox;
    free(aux);
}

void insereFim(Marcador *M, Listasimples *L){
    M->fimSimples->prox = L;
    L->prox = NULL;
    M->fimSimples = L;
}

void removeMeio(Marcador *M, Listasimples *L){

    Listasimples *aux, *aux2;
    aux = M->inicioSimples;

    while(aux != NULL){
        if(aux->prox == L){
            aux2 = L;
            aux->prox = aux2->prox;
            free(aux2);
            return;
        }
        aux = aux->prox;
    }
}

void mostraHistorico(Marcador *M){
    if(ListaSimplesVazia(M)){
        printf("    LISTA ESTA VAZIA!\n");
        system("pause");
        return;
    }

    Listasimples*aux;
    aux = M->inicioSimples;
    printf("\n  HISTORICO DAS PAGINAS ->");
    while(aux != NULL){
        printf(" [ %c ] " ,aux->pagina->nome);
        aux = aux->prox;
    }
    printf("\n\n");
}

void insereHistorico(Marcador *M, conteudo *C){

    Listasimples *novo =(Listasimples *) malloc(sizeof(Listasimples));
    novo->pagina = C;
    novo->prox = NULL;
    if(!novo){
        printf("    ERRO AO ALOCAR MEMORIA! \n");
        system("pause");
    }else{
        if(ListaSimplesVazia(M)){
            //insere na primeira posição quando lista está vazia
            M->inicioSimples = novo;
            M->fimSimples = novo;
            M->cont++;
        }else{
            if(M->inicioSimples->pagina->nome == novo->pagina->nome){ //verifica se o link é repetido
                insereFim(M,novo);
                removeInicio(M);
                return;
            }
            if(M->fimSimples->pagina->nome == novo->pagina->nome){ //insetir no final
                return;
            }
            Listasimples *aux; //verificar se o link do meio é repetido
            aux = M->inicioSimples;
            while(aux != NULL){
                if(aux->pagina->nome == novo->pagina->nome){
                    removeMeio(M,aux);
                    insereFim(M,novo);
                    return;
                }
                aux = aux->prox;
            }

            if(ListaSimplesCheia(M)){
                removeInicio(M);
                insereFim(M,novo);
            }else{
                insereFim(M,novo);
                M->cont++;
            }
        }
    }
}
//FUNCOES DE INSERIR, AVANCAR, VOLTAR, APAGAR DA LISTA DUPLA

void apagar(Listadupla *L){

    Listadupla *aux;
    while(L != NULL){
        aux = L;
        L = L->prox;
        free(aux);
    }
    L = NULL;
}

void abrePagina(Marcador *M, conteudo *pagina){

    Listadupla *novo = (Listadupla *) malloc(sizeof(Listadupla)); //alocando espaço
    if(!novo){
        printf("Nao foi possivel alocar");
    }else{
        novo->pagina = pagina; // recebendo os parametros
        novo->ant = NULL;
        novo->prox = NULL;
        //  se lista esta vazia
        if(ListaDuplaVazia(M)){ // testa se está vazia, se sim insere no inicio
            M->atual = novo;
            M->fimDuplo = novo;
            M->inicioDuplo = novo;
        }else{
            if(M->atual->prox != NULL){ // testar se o proximo é diferente de NULL
                apagar(M->atual->prox); // se for diferente de NULL tem algum valor
            }                           //manda tudo daquele valor pro fim ser apagado e insere no fim
                novo->ant = M->atual;
                M->atual->prox = novo;
                M->atual = novo;
                novo->prox = NULL;
        }
        insereHistorico(M,novo->pagina);
    }
}

void avancar(Marcador *M){
    if(!M->atual->prox){
        printf("    NAO E POSSIVEL AVANCAR, PROXIMA PAGINA NAO EXISTE !\n");
        system("pause");
    }else{
        M->atual = M->atual->prox;
    }
}

void voltar(Marcador *M){
    if(M->atual->ant == NULL){
        printf("    NAO E POSSIVEL VOLTAR, PAGINA ANTERIOR NAO EXISTE !\n");
        system("pause");
    }else{
        M->atual = M->atual->ant;
    }
}

//MAIN , MENU E MOSTRAR

void mostraPaginas(Marcador *M){

    if(ListaDuplaVazia(M)){
        printf("    LISTA ESTA VAZIA!\n");
        system("pause");
        return;
    }

    Listadupla *aux;
    aux = M->inicioDuplo;

    while(aux != NULL){
        printf("\n-------------------------------------------\n");
        printf("Pagina : %c" ,aux->pagina->nome);
        aux = aux->prox;
    }
    printf("\n-------------------------------------------\n");
    system("pause");

}

void menu(Marcador *M){
    int a=0;
    char nome;
    conteudo *novo;

    do{

        system("cls");
        printf("\n");
        if(M->atual != NULL){
            printf("\n  ---------------------------------\n");
            printf("  |        PAGINA ATUAL : %c       |",M->atual->pagina->nome);
            printf("\n  ---------------------------------\n");
        }

        if( M->cont > 0){
            mostraHistorico(M);
        }

        printf("\n ESCOLHA UMA DAS OPCOES: \n");

        printf("   1 - ABRIR PAGINA \n");
        printf("   2 - AVANCAR\n");
        printf("   3 - VOLTAR\n");
        printf("   0 - LIMPAR E SAIR\n  :");


        scanf(" %d", &a);

        switch(a){
        case 0:
            apagar(M->inicioDuplo);
            printf("\n  FILA ENCERRADA \n");
            break;

        case 1:
            printf("\n\n    INFORME O NOME DA PAGINA: ");
            scanf(" %c",&nome);
            novo = (conteudo *) malloc(sizeof(conteudo));
            novo->nome = nome;
            abrePagina(M , novo);

            break;

        case 2:
            avancar(M);
            break;

        case 3:
            voltar(M);
            break;

        case 4:
            mostraPaginas(M);
            break;

        default:
            printf("\n  VALOR INVALIDO\n");
            system("pause");
        }
    }
    while(a!=0);
}

int main(){

    Marcador M;
    iniciaMarcador(&M);
    menu(&M);
    return 0;
}
