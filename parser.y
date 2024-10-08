%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%%

expr:
    expr '+' expr          { printf("Addition\n"); }
  | expr '-' expr          { printf("Subtraction\n"); }
  | expr '*' expr          { printf("Multiplication\n"); }
  | expr '/' expr          { printf("Division\n"); }
  | '(' expr ')'           { /* Parenthesized expression */ }
  | '-' expr %prec UMINUS  { printf("Unary minus\n"); }
  | NUMBER                 { printf("Number\n"); }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}
