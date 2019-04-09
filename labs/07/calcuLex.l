%{
#include <stdio.h>
#include "y.tab.h"
%}

%option yylineno

%%
\/\/.*[\n]              /*ignora comentarios*/
[ \s]                   /*ignora espacios en blanco*/
i                       return (intdcl);
f                       return (floatdcl);
p                       return (print);
([0-9]+)                return (inum);
[0-9]+"."[0-9]+         return (fnum);
[a-eghj-oq-z]           return (id);
=                       return (asig);
\+                      return (plus);
\-                      return (min);
\*                      return (mult);
\/                      return (division);
\n                      return (newline);

%%

int yywrap(void)
{return 1;}