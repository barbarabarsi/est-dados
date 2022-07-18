#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
//Inseri a string.h para checar as strings do argv[] e verificar se o usuário digitou corretamente.

void bubbleSort(int *vetor, int tam);
void selectSort(int *vetor, int tam);
void merge(int *vetor, int inicio, int meio, int fim);
void mergeSort(int *vetor, int inicio, int fim);
int particiona(int *vetor, int inicio, int fim);
void quickSort(int *vetor, int inicio, int fim);
void troca(int *vetor, int i, int j);

int main(int argc, char *argv[]){

    int *vetor = (int *) malloc(atoi(argv[2]) * sizeof(int));

    srand(time(NULL));
    for(int k=0; k<atoi(argv[2]); k++) vetor[k] = rand()%100;

    clock_t tempoInicio;
    
    printf("\nVetor original:\n");
    for(int k=0; k<atoi(argv[2]); k++) printf("%d ", vetor[k]);
    
    if(argc > 4 || argc < 3 || strcmp(argv[1], "-n") != 0){
        printf("Os parametros nao foram passados corretamente.");
        return 1;
    }
    if(argc == 3){
        printf("\n\n----Usando BubbleSort----\n\n");
        tempoInicio = clock();
        bubbleSort(vetor, atoi(argv[2]));
    }
    else if (strcmp(argv[3], "-m")== 0){            
        printf("\n\nUsando MergeSort\n\n");
        tempoInicio = clock();
        mergeSort(vetor, 0, atoi(argv[2])-1);
    }
    else if (strcmp(argv[3], "-q") == 0 ){
        printf("\n\n----Usando QuickSort----\n\n");
        tempoInicio = clock();
        quickSort(vetor, 0, atoi(argv[2])-1);
    }
    else {
        printf("Os parâmetros não foram passados corretamente.\nInsira uma letra que indique um metodo valido de ordenacao.");
        return 1;
    }

    clock_t tempoFim = clock();
    
    printf("Vetor ordenado:\n");
    for(int k=0;k<atoi(argv[2]); k++) printf("%d ", vetor[k]);
    
    printf("\n\nO tempo gasto para a execucao foi de %f segundos\n", (double)(tempoFim - tempoInicio) / CLOCKS_PER_SEC);

    return 0;
}

void bubbleSort(int *vetor, int tam) {
    
    int temp;
    for (int i=1; i<tam; i++) {
        for (int j=0; j<tam-1; j++) {
            if (vetor[j]>vetor[j+1]){
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

void selectSort(int *vetor, int tam){

    int temp;
    for(int i=0; i<tam; i++){
        for(int j=i+1; j<tam; j++){
            if(vetor[i]>vetor[j]){
                temp = vetor[j];
                vetor[j] = vetor[i];
                vetor[i] = temp;
            }
        }
    }
}

void mergeSort(int *vetor, int inicio, int fim){

    if(inicio<fim){
        int meio = (inicio+fim)/2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, inicio, meio, fim);
    }
    
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
    while(i<=meio) temp[pos++] = vetor[i++];
    while(j<=fim) temp[pos++] = vetor[j++];

    for(int k=inicio; k<=fim; k++) vetor[k]=temp[k-inicio];
    free(temp);
}

void quickSort(int *vetor, int inicio, int fim){
    if (fim>inicio){
        int posPivot = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, posPivot-1);
        quickSort(vetor, posPivot+1, fim);
    }
}

int particiona(int *vetor, int inicio, int fim){
    
    int posPivot = inicio + rand()%(fim-inicio+1);
    int pivot = vetor[posPivot];
    troca(vetor, inicio, posPivot);
    int i = inicio;
    int j = fim;
    while(i<j){
        while(vetor[i]<=pivot && i<fim) i++;
        while(vetor[j]>pivot && j>inicio) j--;
        if(i<j) troca(vetor, i, j);       
    }
    troca(vetor, inicio, j);
    return j;
}

void troca(int *vetor, int pos1, int pos2){
    int temp = vetor[pos1];
    vetor[pos1] = vetor[pos2];
    vetor[pos2] = temp;
}



