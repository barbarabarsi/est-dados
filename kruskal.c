#include <stdio.h>
#include <stdlib.h>
#define TAM 100000
typedef struct _art{
    int peso, vert1, vert2;
} art;

art arestas[100];
int pai[100];
int rank[100];

void init(int num_arestas, int num_vert){

    int i,j;
    for(i=0;i<num_arestas;i++){
        arestas[i].peso = 0;
        arestas[i].vert1 = 0;
        arestas[i].vert2 = 0;
    }
    for(j=1;j<num_vert;j++){
        pai[j]=j;
        rank[j]=0;
    }

}
int find(int vert){
    if (pai[vert] == vert) return vert;
    else return find(pai[vert]);
}

void uniao(int vert1, int vert2){
    int pai_v1 = find(vert1);
    int pai_v2 = find(vert2);
    if (rank[pai_v1] == rank[pai_v2]){
        pai[pai_v1] = pai_v2;
        rank[pai_v2]++;
    }
    else if(rank[pai_v1] > rank[pai_v2]) pai[pai_v2] = pai_v1;
    else pai[pai_v1] = pai_v2;
}

art montaAresta(int v1, int v2, int peso){
    art aresta;
    aresta.peso = peso;
    aresta.vert1 = v1;
    aresta.vert2 = v2;
    return aresta;
}


void ordena(int num_art){
    art temp;
    int i,j;
    int tam = num_art+1;
    for (i=1; i<tam; i++) {
        for (j=0; j<tam-1; j++) {
            if(arestas[j].peso>arestas[j+1].peso){
                temp=arestas[j];
                arestas[j]=arestas[j+1];
                arestas[j+1]=temp;
            }
        }
    }
}

int kruskal(int num_art){
    int j, peso_final =0, tam = num_art;
    for (j=0; j<tam-1; j++) {
        if( find(arestas[j].vert1) != find(arestas[j].vert2) ){ 
            uniao(arestas[j].vert1, arestas[j].vert2);
            peso_final += arestas[j].peso;
        }
    }
    return peso_final;
}
int main(){
    int num_vert, num_arest, resultado, i, v1, v2, peso;

    scanf("%d %d", &num_vert, &num_arest);

    init(num_arest,num_vert);

    for(i=1;i<num_arest;i++){
        scanf("%d %d %d", &v1, &v2, &peso);
        arestas[i] = montaAresta(v1,v2,peso);
    }
    ordena(num_arest);
    resultado = kruskal(num_arest);
    printf("%d",resultado);

    return 0;
}