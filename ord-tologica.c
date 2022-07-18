#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 1000

typedef struct _vertice vertice;

typedef struct _vertice{
    int numero;
    int contador;
    vertice* prox;
} vertice;

typedef struct _grafo grafo;

typedef struct _grafo{
    vertice **vert;
    int tam;
} grafo;

vertice* iniciar(){
    vertice* pt = (vertice*) malloc(sizeof(vertice));
    pt->prox = NULL;
    pt->contador = 0;
    return pt;
}

void iniciarGrafo(grafo *grf, int numVertices){
    grf->vert =calloc(numVertices+1, sizeof(vertice*));
    grf->tam = numVertices;
    for(int i = 1; i<grf->tam+1; i++){
      grf->vert[i] = iniciar();
    }

}

void insere(vertice* ptlista, int num){
    vertice* novo = (vertice*) malloc(sizeof(vertice));
    novo->numero = num;
    novo->prox = ptlista->prox;
    ptlista->prox = novo;
}

void imprimeLista(vertice* ptlista){
    vertice* aux = ptlista->prox;
    if(aux==NULL) printf("ninguem!");
    while(aux!=NULL){
        printf("%d  ", aux->numero);
        aux = aux->prox;
    }
}

void imprimeGrafo(grafo* grf){
    for(int i = 1; i<grf->tam+1; i++){
        printf("%d eh pai de ", i);
        imprimeLista(grf->vert[i]);
        printf("\n");
    }
}

void adicionaVertice(grafo *grf, vertice *pai, int filho){
    insere(pai, filho);
    grf->vert[filho]->contador++;  
}

void removeVertice(grafo *grf, int indice){
    
    vertice *aux = grf->vert[indice]->prox;
    while(aux!=NULL){
        grf->vert[aux->numero]->contador--;
        aux= aux->prox;
    }
    free(grf->vert[indice]->prox);
    grf->vert[indice]->prox = NULL;
    grf->vert[indice]->contador = -1;
}

int grafoVazio(grafo *grf){
    for (int i = 1; i<grf->tam+1; i++){
        if(grf->vert[i]->contador >-1) return 0;
    }
    return 1;
}

void ordTop(grafo *grf){

    while(!grafoVazio(grf)){
        for (int i = 1; i<grf->tam+1; i++){
            if(grf->vert[i]->contador == 0){
                printf("%d ", i);
                removeVertice(grf, i);
                break;
            }
        }
    }

}


void ordTopAlt(grafo *grf){

    while(!grafoVazio(grf)){
        for (int i = 1; i<grf->tam+1; i++){
            if(grf->vert[i]->contador == 0){
                printf("%d ", i);
                removeVertice(grf, i);
            }
        }
    }

}

int main(){

    grafo grf, grfCopia;
    int i = 1, numVertices;
    char *entrada, *resultado;
    char *delimitadores = " \n";

    fgets(entrada, TAM, stdin);
    numVertices = atoi(strtok(entrada, delimitadores));

    iniciarGrafo(&grf, numVertices);
    iniciarGrafo(&grfCopia, numVertices);

    for(int i = 1; i<numVertices+1; i++){
        fgets(entrada, TAM, stdin);
        resultado = strtok(entrada, delimitadores);

        while(resultado!=NULL){
            if(strcmp(resultado, "\\n")==0){
                resultado = strtok(NULL, delimitadores);
                break;
            }
            adicionaVertice(&grf, grf.vert[i], atoi(resultado));
            adicionaVertice(&grfCopia, grfCopia.vert[i], atoi(resultado));
            resultado = strtok(NULL, delimitadores);
        }
    }
    
    ordTop(&grf);

    return 0;
}
