%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex(void);
    int yyerror(char* s);
    int valid=1;
%}

%token a b c

%%
A: c B;
B: |a B|b B

%%

int main(){
    printf("Enter the string:");
    yyparse();
    if(valid){printf("Valid String");}
    return 0;
}

int yyerror(char* s)
{
 printf("\nExpression invalid");
 exit(0);
}