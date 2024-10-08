%{
    #include "y.tab.h"
    void yyerror(const char *s);  /* Declaration of yyerror */
%}

%% 
[0-9]+              { yylval = atoi(yytext); return NUMBER; }
[\t\n ]             { /* Ignore whitespace */ }
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"("                 { return '('; }
")"                 { return ')'; }

.                   { yyerror("Invalid character"); }
%%

int yywrap() {
    return 1;
}
