%{
    #include <stdio.h>
    #include "y.tab.h"
    int yyerror(char* s);
%}

%%
[a-zA-Z]+ {return a;}
[0-9]+  {return b;}
\n        {return 0;}
[ \t]+       {;}
.           {return c;}
%%
