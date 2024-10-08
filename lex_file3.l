%{
    #include <stdio.h>
    int v=0,c=0;
%}

%%
[a,e,i,o,u,A,E,I,O,U]   {v++;}
[^ \t\n]                {c++;}
%%

int main(){
    printf("Enter the sentence:");
    yylex();
    printf("The number of vowels is %d\n",v);
    printf("The number of consonants is %d\n",c);
    return 0;
}

int yywrap(){
    return 1;
}

