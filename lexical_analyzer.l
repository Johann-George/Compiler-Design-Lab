%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int k=0;
    struct symbal{
        char id[10];
        int pos;
    }n[20];
    void identifier(char *yytext){
        int flag=0;
        for(int i=0;i<k;i++){
            if(strcmp(n[i].id,yytext)==0){
                flag=1;
                printf("<identifier,%d>",n[i].pos);
                break;
            }
        }
        if(flag==0){
            strcpy(n[k].id,yytext);
            n[k].pos=k+1;
            printf("<identifier,%d>",n[k].pos);
            k++;
        }
    }

%}

%%
"int"|"float"|"double"|"if"|"else"|"char"|"void"|"main"|"printf" {printf("\n<keyword,%s>",yytext);}
[a-zA-Z_][a-zA-Z0-9_]* {identifier(yytext);}
["][a-zA-Z0-9 ][a-zA-Z0-9 ]*["] {printf("\n<string,%s>",yytext);}
[0-9]+ {printf("\n<number,%s>",yytext);}
"+"|"-"|"*"|"/"|"<"|">"|"<="|">="|"=="|"!=" {printf("\n<operator,%s>",yytext);}
","|"."|"("|")"|";"|"="|"{"|"}" {printf("\n<symbol,%s>",yytext);}
[ \t] {;}
[\n] {;}
. {printf("\nInvalid tokens");}
%%

void main(){
    FILE *fp=fopen("input.txt","r");
    yyin=fp;
    yylex();
    fclose(fp);
}

int yywrap(){
    return 1;
}