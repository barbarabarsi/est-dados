#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

typedef struct _stackInt { 
    int topo;
    int numero[TAM];
} stackInt;  

typedef struct _stackChar { 
    int topo;
    char caractere[TAM];
} stackChar;  

void initInt(stackInt *pilha){
    pilha->topo = -1;
}

void initChar(stackChar *pilha){
    pilha->topo = -1;
}

int verOper(char charLido){
    char operadores[] = "+-*/()";
    for(int i = 0; i<6; i++) if(charLido == operadores[i]) return 1;
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

char* removeEspaco(char *string){

    int tamanhoReal = 0;
    int j = 0;

    for(int i=0; i<strlen(string); i++) if(string[i] != ' ') tamanhoReal++;

    char *stringProv = (char*) calloc(tamanhoReal, sizeof(char));

    for(int i=0; i<strlen(string); i++){
        if(string[i] != ' '){
            stringProv[j] = string[i];
            j++;
        }
    }
    return stringProv;
}

void pushInt(stackInt *pilha, int input){
    pilha->topo++;
    pilha->numero[pilha->topo] = input;
}

void pushChar(stackChar *pilha, char input){  
    pilha->topo++;
    pilha->caractere[pilha->topo] = input;
}

int popInt(stackInt *pilha){
    if (pilha->topo == -1){
        printf("Erro! Ocorreu um underflow na pilha. Encerrando programa.");
        exit(1);
    } 
    return pilha->numero[(pilha->topo)--];
} 

int popChar(stackChar *pilha){
    if (pilha->topo == -1){
        printf("Erro! Ocorreu um underflow na pilha. Encerrando programa.");
        exit(1);
    } 
    return pilha->caractere[(pilha->topo)--];
} 

int buscaElem(char busca, stackChar *pilha){
    for(int i = pilha->topo; i>0; i--){
        if(pilha->caractere[i] == busca) return 1;
    } 
    return 0;
}


int main(){

    int leitura;
    int num1;
    int num2;
    char oper;
    int salto = 1;
    char *entrada = (char*) malloc (TAM * sizeof(char));
    char *teste = (char*) malloc (TAM * sizeof(char));

    fgets(entrada, TAM, stdin);

    stackInt *pilhaInt = (stackInt*) malloc (sizeof(stackInt));
    stackChar *pilhaChar = (stackChar*) malloc (sizeof(stackChar));
    initInt(pilhaInt);
    initChar(pilhaChar);
    
    entrada = removeEspaco(entrada);

    while(strlen(entrada)>0){

        if(!verOper(entrada[0])){
            sscanf(entrada, "%d", &leitura);
            if(pilhaChar->caractere[pilhaChar->topo] == '-'){
                leitura*=-1;
                pilhaChar->caractere[pilhaChar->topo] = '+';
            }
            pushInt(pilhaInt, leitura);
            salto = contaAlg(leitura);
            entrada = entrada+salto;
        }

        if(strlen(entrada)>0){

            if(entrada[0] == '(') pushChar(pilhaChar, entrada[0]);

            else if(entrada[0] == ')'){
                while (pilhaChar->caractere[pilhaChar->topo] != '('){   
                    oper = popChar(pilhaChar);
                    num1 = popInt(pilhaInt);
                    num2 = popInt(pilhaInt);
                    pushInt(pilhaInt, calcula(num2, num1, oper));
                }
                popChar(pilhaChar);
            }

            else if(pilhaInt->topo>=2 && (pilhaChar->caractere[pilhaChar->topo] =='*'|| pilhaChar->caractere[pilhaChar->topo]=='/')){
                oper = popChar(pilhaChar);
                num1 = popInt(pilhaInt);
                num2 = popInt(pilhaInt);
                pushInt(pilhaInt, calcula(num2, num1, oper));
                pushChar(pilhaChar, entrada[0]);
            }

            else pushChar(pilhaChar, entrada[0]);  

            entrada=entrada+1;   
        } 
    }

    while(pilhaInt->topo!=0){
        oper = popChar(pilhaChar);
        num1 = popInt(pilhaInt);
        num2 = popInt(pilhaInt);
        pushInt(pilhaInt, calcula(num2, num1, oper));
    }

    printf("Resultado: %d ", pilhaInt->numero[pilhaInt->topo]);

}