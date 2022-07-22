#include <stdio.h>
#include <stdlib.h>
#define TAM 100000
typedef struct _art{
    int peso, vert1, vert2;
} art;
typedef struct _grf{
    art* arestas;
    int* pais;
    int* ranks;
} grf;
art initAresta(){
    art aresta;
    aresta.peso = 0;
    aresta.vert1 = 0;
    aresta.vert2 = 0;
    return aresta;
}
art montaAresta(int v1, int v2, int peso){
    art aresta;
    aresta.peso = peso;
    aresta.vert1 = v1;
    aresta.vert2 = v2;
    return aresta;
}
grf* initGrafo(int num_vert, int num_arestas){

    int i;
    grf* grafo = malloc(sizeof(grf));
    grafo->ranks = calloc((num_vert+1),sizeof(int));
    grafo->pais = calloc((num_vert+1),sizeof(int));
    for(i=1; i<(num_vert+1);i++){
        grafo->pais[i]=i;
        grafo->ranks[i]=0;
    }   
}
    }   
            }
    }   
    grafo->arestas = malloc(num_arestas*sizeof(art));
    for(int i = 0; i<num_arestas; i++){
      grafo->arestas[i] = initAresta();
    }
    return grafo;
}
int find(grf* grafo, int vert){
    
    if (grafo->pais[vert] = vert) return vert;
    else return find(grafo, grafo->pais[vert]);
}

int uniao(grf* grafo, int vert1, int vert2){
    int pai_v1 = find(grafo, vert1);
    int pai_v2 = find(grafo, vert2);
    if (grafo->ranks[pai_v1] == grafo->ranks[pai_v1]){
        grafo->pais[pai_v1] = pai_v2;
        grafo->ranks[pai_v2]++;
    }

void merge(int *vetor, int inicio, int meio, int fim){

    int i = inicio;
    int j = meio+1;
    int pos = 0;
    int *temp = (int *) malloc((fim-inicio+1)*sizeof(int)); 

    while(i<=meio && j<=fim){
        if(vetor[i]<=vetor[j]) temp[pos++] = vetor[i++];
        else temp[pos++] = vetor[j++];
    }
void ordena(grf* grafo, int num_art){
    art temp;
    int i,j;
    int tam = num_art;
    art* resultado = malloc(num_art*sizeof(art));
    for (i=0; i<tam-1; i++) {
        printf("%d",grafo->arestas[i]);
    }
}
int kruskal(grf* grafo, int num_art){
    int j, peso_final =0, tam = num_art;
    for (j=1; j<tam; j++) {
        art aresta = grafo->arestas[j];
        if( find(grafo, aresta.vert1) != find(grafo, aresta.vert2) ){ // se estiverem em componentes distintas
            uniao(grafo, aresta.vert1, aresta.vert2);
            peso_final += aresta.peso;
        }
    }
    return peso_final;
}
int main(){
    grf* grafo = initGrafo(10,13);
    grafo->arestas[0] = montaAresta(0,0,0);
    grafo->arestas[1] = montaAresta(1,2,1);
    grafo->arestas[2] = montaAresta(2,3,3);
    grafo->arestas[3] = montaAresta(3,4,1);
    grafo->arestas[4] = montaAresta(4,5,1);
    grafo->arestas[5] = montaAresta(5,6,4);
    grafo->arestas[6] = montaAresta(6,7,2);
    grafo->arestas[7] = montaAresta(7,8,1);
    grafo->arestas[8] = montaAresta(4,8,3);
    grafo->arestas[9] = montaAresta(8,9,2);
    grafo->arestas[10] = montaAresta(9,3,1);
    grafo->arestas[11] = montaAresta(9,10,1);
    grafo->arestas[12] = montaAresta(1,10,3);
    printf("%d %d",grafo->arestas[1].peso,grafo->arestas[2].peso);
    ordena(&grafo,12);
    int resultado = kruskal(grafo,12);
}