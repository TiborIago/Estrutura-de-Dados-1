#include <stdio.h>
#include <stdlib.h>

enum boolean {
    true = 1, false = 0
};
typedef  enum boolean  bool;

typedef struct Conteudo{

    int id;
    bool chefe;
    int quant;

}Conteudo;

typedef struct Impressao{

    struct Conteudo *conteudo;
    struct Impressao *prox;

}Impressao;

typedef struct Fila{

    struct Impressao *primeiro;
    struct Impressao *ultimo;
    int cont;
    int idGerador;

}fila;

void removerNoFila();
void iniciaFila();
void mostrarFila();
bool filaVazia();
bool filaCheia();
void mostrarFila();
void menu();
Impressao * buscarId();
void cancelarImpressao();

void cancelarImpressao(fila *F, int id){
    Impressao *aux,*aux2;
    aux = buscarId(F,id);
    aux2 = F->primeiro;

    if(aux != NULL){
        while(aux2 != NULL){
            if(aux2->prox == aux){
                aux2->prox = aux->prox;
                free(aux);
                printf("\n  A IMPRESSAO FOI REMOVIDA DA LISTA \n");
                system("pause");
            }

        }
	    }

}

Impressao * buscarId(fila *F, int id){

        Impressao *aux;
        aux = F->primeiro;
        //percore a fila toda ate achar o no que tem o id informado
        while(aux != NULL){
            // testa se o id é igual ao informado e mostra ele

            if(aux->conteudo->id == id){
                printf(" \n   IMPRESSAO ENCONTRADA: \n    ID: %d \n    - QUANTIDADE DE PAG: %d \n    - CHEFE: ", aux->conteudo->id, aux->conteudo->quant);
                if(aux->conteudo->chefe)
                    printf("sim \n");
                else
                    printf("nao\n");
                system("pause");
                //  return retorna o no que foi achado e finaliza a funçao
                return aux;
                }
            aux = aux->prox;

        }
        //caso nao encontre nada e o return acima nao foi ativado  a
        //mensagem abaixo e exibida
        system("pause");
        printf("\n  O ID INFORMADO NAO FOI ENCONTRADO \n");
        return NULL;
}

void removerNoFila(fila *F){
    //testa se esta vazia caso sim informa
    //caso nao remove o primeiro no;
    if(filaVazia(F)){
        printf("\n   FILA ESTA VAZIA !\n\n ");
    }else{
        Impressao *aux;
        aux = F->primeiro;
        F->primeiro = aux->prox;

        printf(" \n   IMPRESSAO REALIZADA\n    ID: %d \n    - QUANTIDADE DE PAG: %d \n    - CHEFE: ", aux->conteudo->id, aux->conteudo->quant);
        if(aux->conteudo->chefe)
            printf("sim \n");
        else
            printf("nao\n");

        system("pause");
        free(aux);
        F->cont--;
    }
}

void insereImpressao(fila *F, Conteudo *conteudo){

    // verifica se lista esta cheia
    if(filaCheia(F)){
        printf("\n A QUANTIDADE MAXIMA DE IMPRESSOES FOI INSERIDA !\n:");
        return;
    }

    Impressao *novo = (Impressao *) malloc(sizeof(Impressao));
    Impressao *aux ,*aux2;
    //testa se ha memoria disponivel
    if(!novo){
        printf("\n\n   SEM MEMORIA DISPONIVEL !\n");
    }else{
        // atribui os valores ao no

        novo->conteudo = conteudo;
        novo->prox = NULL;
        //Impressao *aux;
        //aux = F->primeiro;

        //testa se fila esta vazia se estiver insere primeiro no
        //se nao estiver insere no final da fila
        if(filaVazia(F)){
            F->primeiro = novo;
            F->ultimo = novo;
            F->cont++;
        }else{
            // testa se o novo e chefe
            //caso nao fpr insere novo no fim da fila
            if(novo->conteudo->chefe){
                //testa se o primeiro da fila e chefe se sim insere na primeira posicao
                //se nao percore a lista ate achar a ultima impressao de chefe e insere novo depo
                aux = F->primeiro;
                if(aux->conteudo->chefe){

                    while(aux != NULL){

                        if(aux->prox == NULL){
                            aux->prox = novo;
                            F->cont++;
                            return;
                        }else{
                            aux2 = aux->prox;
                            if((aux2->conteudo->chefe == false)){
                                novo->prox = aux2;
                                aux->prox = novo;
                                F->cont++;
                                return;
                            }
                        }
                        aux = aux->prox;
                    }
                }else{
                    //iserir novo no inicio da fila
                    novo->prox = F->primeiro;
                    F->primeiro = novo;
                }

            }else{
                //inserir novo no fim da fila
                F->ultimo->prox = novo;
                F->ultimo = novo;
            }

        }
        F->cont++;
    }
}

bool filaCheia(fila *L){

    if(L->cont >= 10)
        return true;
    else
        return false;

}

bool filaVazia(fila *L){

	if(L->cont <= 0)
		return true;
	else
		return false;
}

void mostrarFila(fila *F){

    if(filaVazia(F)){
        printf("\n\n   FILA ESTA VAZIA !\n\n");
    }else{
        Impressao *aux;
        aux = F->primeiro;
        printf("----------------------------------------------------------------\n\n   LISTA A SER IMPRESSA:\n\n" );
        int i = 1;
        while(aux != NULL){

            printf("- Posicao: %d  -  Id: %d -  Quantidade: %d -  ",i,aux->conteudo->id,aux->conteudo->quant );
            if(aux->conteudo->chefe){
                printf("Chefe : sim \n");
            }else{
                printf("Chefe : nao\n");
            }
            i++;
            aux = aux->prox;
        }
        printf("\n\n----------------------------------------------------------------\n\n" );

    }
    system("pause");

}

void iniciaFila(fila *F){

    F->primeiro = NULL;
    F->ultimo = NULL;
    F->cont = 0;
    F->idGerador = 0;

}

void menu(fila *F){
    int a=0 ,b=0 ,c=0;
    Conteudo *novo;

    do{
        system("cls");
		
        printf("\n ESCOLHA UMA DAS OPCOES: \n");
        printf("   1 - INSERIR IMPRESSAO \n");
        printf("   2 - IMPRIMIR \n");
        printf("   3 - MOSTRAR LISTA DE IMPRESSAO \n");
        printf("   4 - BUSCAR ID  \n");
        printf("   5 - CANCELAR IMPRESSAO \n   Digite uma opcao: ");
        scanf(" %d", &a);

        system("cls");
        switch(a){
            case 0:
                printf("\n  FILA ENCERRADA \n");

            case 1:

                novo = (Conteudo *) malloc(sizeof(Conteudo));
                printf("\n A IMPRESSAO E DE UM CHEFE:\n 0- NAO\n 1-SIM \n:");
                scanf(" %d", &b);
                printf("\n INFORME A QUANTIDADE DE PAGINAS \n:");
                scanf(" %d", &c);
                novo->chefe = b;
                novo->quant = c;
                novo->id = F->idGerador;
                F->idGerador++;

                insereImpressao(F,novo);
            break;

            case 2:
                removerNoFila(F);
            break;

            case 3:
                mostrarFila(F);
            break;

            case 4:
                printf("\n  INFORME O ID: \n");
                scanf(" %d", &b);
                buscarId(F,b);
            break;

            case 5:
                mostrarFila(F);
                printf("\n  INFORME O ID: \n");
                scanf(" %d", &b);
                cancelarImpressao(F,b);
            break;

            default:
                printf("\n  VALOR INVALIDO\n");

        }

    }while(a!=0);

}

int main(){

    fila F;
    iniciaFila(&F);
    menu(&F);
    return 0;

}

