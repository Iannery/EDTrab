#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pilhachar.h"
#include "pilhadouble.h"

int priority(char op){
    if(op == '*' || op == '/'){
        return 2;
    }
    if(op == '+' || op == '-'){
        return 1;
    }
    else{
        return 0;
    }
}

int is_operand(char op){
    if( (op >= '0' && op <= '9') ||
        (op >= 'a' && op <= 'z') ||
        (op >= 'A' && op <= 'Z') ||
        op == ' ' || op == '.' || op == ','){

        return 1;
    }
    else{
        return 0;
    }
    
}

int is_operator(char op){
    if(op == '*' || op == '/' || op == '+' || op == '-'){
        return 1;
    }
    else{
        return 0;
    }
}


int converter(char op){
    switch(op){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }
}

double strtolf(char* expr){
    int i, m = 0, j, auxconv, tamstr;
    double tot;
    tamstr = strlen(expr);
    for(i = 0; i < tamstr; i++){
        if(expr[i] == '.' || expr[i] == ','){
            m = i;
        }
    }
    if(m){
        for(i = (m - 1), j = 0; j < m; i--, j++){
            auxconv = converter(expr[j]);
            tot += pow(auxconv, i);
        }
        for(i = 0, j = m + 1; j < tamstr; i++, j++){
            auxconv = converter(expr[j]);
            tot += auxconv / pow(10, i + 1);
        }
    }
    else{
        for(i = (tamstr - 1), j = 0; j < tamstr; i--, j++){
            auxconv = converter(expr[j]);
            tot += auxconv * pow(10, i);
        }
    }
    return tot;


}

double eval_exp(char* expr){
    Pilha* double_stack;
    char aux_str[50];
    int i, j, k;
    double_stack = cria_pilha(50);
    double aux_operand1, aux_operand2, aux_operand_tot, tot;
    puts("TUDO BEM ATE AQUI2");
    for(i = 0; i < strlen(expr); i++){
        if(is_operand(expr[i]) && expr[i] != ' '){
            puts("TUDO BEM ATE AQUIO");
            for(j = i, k = 0; expr[j] != ' '; j++, k++){
                aux_str[k] = expr[j];
            }
            puts("TUDO BEM ATE AQUIO2");
            aux_str[k] = '\0';
            i = j;
            puts("TUDO BEM ATE AQUIO3");
            empilhar_pilha(strtolf(aux_str), double_stack);
        }
        puts("TUDO BEM ATE AQUIOOOO");
        printf("e operador??%d\n", is_operator(expr[i]));
        if(is_operator(expr[i])){
            aux_operand1 = desempilhar_pilha(double_stack); // Ultimo numero a ser empilhado
            aux_operand2 = desempilhar_pilha(double_stack); // Penultimo a ser empilhado
            switch(expr[i]){
                case '+':
                    puts("ENTROU ADICAO");
                    aux_operand_tot = aux_operand1 + aux_operand2;
                    printf("%lf %lf %lf ", aux_operand_tot, aux_operand1, aux_operand2);
                    break;
                case '-':
                    aux_operand_tot = aux_operand1 - aux_operand2;
                    break;
                case '*':
                    aux_operand_tot = aux_operand1 * aux_operand2;
                    break;
                case '/':
                    if(aux_operand2 == 0){
                        puts("DIVISAO POR 0!!!!");
                        destroi_pilha(double_stack);
                        return 0;
                    }
                    else{
                        aux_operand_tot = aux_operand1 / aux_operand2;
                        break;
                    }
            }
            empilhar_pilha(aux_operand_tot, double_stack);
        }
    }
    tot = desempilhar_pilha(double_stack);
    destroi_pilha(double_stack);
    return tot;
}




void inf_to_postf(char* exp_infix, char* exp_postfix){
    Pilha_char* itp_stack;
    int i, j;
    itp_stack = cria_pilha_char(strlen(exp_infix));
    for(i = 0, j = 0; i < strlen(exp_infix); i++){
        if(is_operand(exp_infix[i])){
            exp_postfix[j] = exp_infix[i];
            j++;
        }
        else if(is_operator(exp_infix[i])){
            while((!pilha_vazia_char(itp_stack)) && (priority(topo_pilha_char(itp_stack)) >= priority(exp_infix[i]))){
                exp_postfix[j] = desempilhar_pilha_char(itp_stack);
                j++;
            }
            empilhar_pilha_char(exp_infix[i], itp_stack);
        }
        else if(exp_infix[i] == '('){
            empilhar_pilha_char(exp_infix[i], itp_stack);
        }
        else if(exp_infix[i] = ')'){
            while(topo_pilha_char(itp_stack) != '('){
                exp_postfix[j] = desempilhar_pilha_char(itp_stack);
                j++;
            }
        }
        else{
            puts("Expressao invalida");
        }
    }
    while(!pilha_vazia_char(itp_stack)){
        exp_postfix[j] = desempilhar_pilha_char(itp_stack);
        j++;
    }
    exp_postfix[j] = '\0';
    destroi_pilha_char(itp_stack);
}

int validate_exp(char* expression){
    Pilha_char* val_stack;
    int exp_size, i, validvar = 1;
    exp_size = strlen(expression);
    val_stack = cria_pilha_char(exp_size);
    for(i = 0; i < exp_size; i++){
        switch(expression[i]){
            case '(':
                empilhar_pilha_char('(', val_stack);
                break;
            case ')':
                if(pilha_vazia_char(val_stack)){
                    puts("Equacao invalida");
                    validvar = 0;
                }
                else if(desempilhar_pilha_char(val_stack) == '('){
                }
                break;
        }
    }
    if(!pilha_vazia_char(val_stack)){
        puts("Equacao invalida");
        validvar = 0;
    }
    destroi_pilha_char(val_stack);
    return validvar;
}

int resprob(){
    char expression[101], exp_postfix[101];
    double topper;
    puts("Digita uma string");
    getchar();
    gets(expression);
    if(!validate_exp(expression)){
        return 0;
    }
    inf_to_postf(expression, exp_postfix);
    puts("Expressoes:::::");
    puts(expression);
    puts(exp_postfix);
    puts("TUDO BEM ATE AQUI1");
    topper = eval_exp(exp_postfix);
    printf("%lf\n", topper);

}

// ---------------------------MISC------------------------------------------

void printmenu(){
    printf("Escolha uma opcao:\n");
    printf("1.\tResolucao de expressao\n2.\tCalculadora\n3.\tSair\n\n>>");
}
int main(){
    int menusel, flagrun = 1;
    while(flagrun){    
        printmenu();
        scanf("%d", &menusel);
        switch(menusel){
            case 1:
                resprob();
                break;
            case 2:
                // calc();
                break;
            case 3:
                flagrun = 0;
                break;
        }
    }
    return 0;
}