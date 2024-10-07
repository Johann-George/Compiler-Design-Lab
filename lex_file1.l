%{
#include <stdio.h>
int lines=0, chars=0, words=0;
%}

%%
\n  { lines++;chars++;}
[ \t]+ {chars+=yyleng;}
[^ \t\n]+ {words++;chars+=yyleng;}
. {chars++;}
%%

int main(){
    printf("Enter the input:\n");
    yylex();
    printf("The number of lines is %d\n",lines);
    printf("The number of words is %d\n",words);
    printf("The number of characters is %d\n",chars);
    return 0;
}

int yywrap(){
    return 1;
}