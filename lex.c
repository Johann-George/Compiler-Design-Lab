#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ID_NUM 10
#define MAX_SYMBOL_NUM 20
#define MAX_INPUT 20

struct symbolTable{
    char id[MAX_ID_NUM];
    int pos;
}symbol[MAX_SYMBOL_NUM];
int symno=0;
void printSymbolTable(){
    printf("Symbol Table\n");
    for(int i=0;i<symno;i++){
        printf("%s\t%d\n",symbol[i].id,symbol[i].pos);
    }
}

void main(){
    FILE *fp=fopen("input1.txt","r");
    char input_char;
    input_char=fgetc(fp);
    int state=1,j=0;
    while(input_char!=EOF){
        switch(state){
            case 1:
                if(input_char=='<') state=2;
                else if(input_char=='>') state=3;
                else if(input_char=='=') state=4;
                else if(strchr("+-*/%",input_char)) state=5;
                else if(strchr(";,()':",input_char)) state=6;
                else if(isdigit(input_char) || isalpha(input_char) || input_char=='_'){
                    state=7;
                } 
                else if (input_char=='"') state=8;
                else{
                    input_char=fgetc(fp);
                }
                break;
            case 2:
                if(input_char=='='){
                    printf("<operator,<= >\n");
                }
                else{
                    printf("<operator,< >\n");
                }
                state=1;
                input_char=fgetc(fp);
                break;
            case 3:
                if(input_char=='='){
                    printf("<operator,>= >\n");
                }
                else{
                    printf("<operator,> >\n");
                }
                state=1;
                input_char=fgetc(fp);
                break;
            case 4:
                input_char=fgetc(fp);
                if(input_char=='='){
                    printf("<operator,== >\n");
                    input_char=fgetc(fp);
                }
                else{
                    printf("<symbol,= >\n");
                }
                state=1;                
                break;
            case 5:
                printf("<operator,%c>\n",input_char);
                state=1;
                input_char=fgetc(fp);
                break;
            case 6:
                printf("<symbol,%c>\n",input_char);
                state=1;
                input_char=fgetc(fp);
                break;
            case 7:
                int k=0;
                char identifier[MAX_INPUT];
                while(isdigit(input_char) || isalpha(input_char)){
                    identifier[k++]=input_char;
                    input_char=fgetc(fp);
                }
                identifier[k]='\0';
                if(strcmp(identifier,"int")==0 || strcmp(identifier,"char")==0 || 
                strcmp(identifier,"float")==0 || strcmp(identifier,"main")==0 
                || strcmp(identifier,"int")==0){
                    printf("<keyword, %s>\n",identifier);
                }
                else{     
                    int flag=0,z=0;           
                    if(isdigit(identifier[0])){
                        for(int i=0;i<strlen(identifier);i++){
                            if(isalpha(identifier[i])){
                                z=1;
                            }
                        }
                        if(z==1){
                            printf("Error: Invalid token %s\n",identifier);
                        }
                        else{
                            printf("<number,%s>\n",identifier);
                        }
                    }
                    else{
                        for(int i=0;i<symno;i++){
                            if(strcmp(symbol[i].id,identifier)==0){
                                printf("<id,%d>\n",symbol[i].pos);
                                flag=1;
                            }
                        }
                        if(!flag){
                            strcpy(symbol[symno].id,identifier);
                            symbol[symno].pos=symno+1;
                            printf("<id,%d>\n",symno+1);
                            symno++;
                        }
                    }
                }
                state=1;
                break;
            case 8:
                char string[MAX_INPUT];
                int j=0;
                if(input_char=='"'){
                    printf("<symbol,%c>\n",input_char);
                    input_char=fgetc(fp);
                    while(isalpha(input_char)){
                        string[j++]=input_char;
                        input_char=fgetc(fp);
                    }
                    string[j]='\0';
                    
                    printf("<string,%s>\n",string);
                    printf("<symbol,%c>\n",input_char);
                }
                state=1;
                input_char=fgetc(fp);
                break;
            default:
                printf("Invalid token");
        }
        
    }
    printSymbolTable();
}