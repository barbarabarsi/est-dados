#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 1000

typedef union uniaoDados{
    char operador;  
    int numero; 
} uniaoDados;

typedef struct _noStack {  
    int tipoDado;
    uniaoDados dado;
} noStack;   

typedef struct _stack { 
    int topo;
    noStack *elementos;
} stack;  

int verOper(char charLido){
    char operadores[] = "+-*/()";
    for(int i = 0; i<4; i++) if(charLido == operadores[i]) return 1;
    if(charLido == operadores[4]) return 2;
    if(charLido == operadores[5]) return 3;
    return 0;
}


int contaAlg(int numero){
    int algarismos=0;
    while(numero!=0){  
       numero=numero/10;  
       algarismos++;  
    }       
    return algarismos;  
}  

int calcula(int num1, int num2, char oper){
    
    if(oper == '+') return num1 + num2;
    else if(oper == '-') return num1 - num2;
    else if(oper == '*') return num1 * num2;
    else if(oper == '/') return num1 / num2;
  
}


void init(stack *pilha){
    pilha->elementos = malloc (sizeof(uniaoDados));
    pilha->topo = -1;
}

void push(stack *pilha, uniaoDados input, int tipo){
    
    pilha->topo++;
    pilha->elementos[pilha->topo].dado = input;
    if(tipo == 1) pilha->elementos[pilha->topo].tipoDado = 1;
    else pilha->elementos[pilha->topo].tipoDado = 2;
}

uniaoDados pop(stack *pilha){
    if (pilha->topo == -1){
        printf("underflow");
        exit(1);
    } 
    return pilha->elementos[(pilha->topo)--].dado;
} 

stack* inverte(stack *pilha) {
    stack *outra = (stack*) malloc (sizeof(stack));
    init(outra);
    while (pilha->topo != -1) {
        
        outra->elementos[outra->topo] = pilha->elementos[pilha->topo];
        pilha->topo--;
        outra->topo++;
    }
    return outra;
}

int main(){
    stack *pilha = (stack*) malloc (sizeof(stack));
    stack *pilhaTemp = (stack*) malloc (sizeof(stack));
    init(pilha);
    init(pilhaTemp);
    uniaoDados leitura;
    int num1;
    int num2;
    int oper;
    char *entrada = "3*8";
    int salto = 1;
    int i = 0;

    printf("Entrada original: %s\n\n", entrada);

    while(strlen(entrada)>0){
        if(!verOper(entrada[0])){
            sscanf(entrada, "%d", &leitura.numero);
            push(pilha, leitura, 1);
            salto = contaAlg(leitura.numero);
            }
        else{
            if(entrada[0] == '+' ||entrada[0] == '-'){
                while(pilhaTemp->elementos[pilhaTemp->topo].dado.operador == '*' || pilhaTemp->elementos[pilhaTemp->topo].dado.operador == '/'){
                    leitura = pop(pilhaTemp);
                    push(pilha, leitura, 2);
                }
                leitura.operador = entrada[0];
                push(pilhaTemp, leitura, 2);
            }
            else if(entrada[0] == ')'){
                while(pilhaTemp->elementos[pilhaTemp->topo].dado.operador != '('){
                    leitura = pop(pilhaTemp);
                    push(pilha, leitura, 2);
                }
                pop(pilhaTemp);
            }
            else{
                leitura.operador = entrada[0];
                push(pilhaTemp, leitura, 2);
            }
            salto=1;
        }
        entrada = entrada+salto;
    }
    
    while(pilhaTemp->topo!=-1){
        push(pilha, pop(pilhaTemp), 2);
    }

    printf("\nPilha:\n\n");

    for(int i=pilha->topo; i>-1; i--){
        if(pilha->elementos[i].tipoDado == 1){
            printf("Topo %d: %d\n", i, pilha->elementos[i].dado);
        } 
        else{
            printf("Topo %d: %c\n", i, pilha->elementos[i].dado);
        } 
    } 

    pilha = inverte(pilha);
    printf("\nPilha invertida:\n\n");    

    for(int i=pilha->topo; i>-1; i--){
        if(pilha->elementos[i].tipoDado == 1){
            printf("Topo %d: %d\n", i, pilha->elementos[i].dado);
        } 
        else{
            printf("Topo %d: %c\n", i, pilha->elementos[i].dado);
        } 
    } 
    
    printf("o topo da pilha original eh %d\n", pilha->topo);

    /* while(pilha->topo!=-1){
        printf("elemento %d, tipo %d", pilha->elementos[pilha->topo].dado, pilha->elementos[pilha->topo].tipoDado);
        if(pilha->elementos[pilha->topo].tipoDado == 1){
            push(pilhaTemp, pop(pilha), 1);
            printf("coloquei %d\n", pilhaTemp->elementos[pilhaTemp->topo].dado);
        }
        else{
        }       
    }  */

    printf("\nTempultado: %d", pilhaTemp->elementos[pilhaTemp->topo].dado.numero); 


}

