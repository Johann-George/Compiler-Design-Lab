%{
    #include <stdio.h>
%}

%%
abc {printf("ABC");}
.   {printf("%c",yytext[0]);}
%%

int main(){
    printf("Enter the input:");
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}