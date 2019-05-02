%{
#include <stdio.h>
%}

%%
i                               fprintf(yyget_out(), "intdcl");
f                               fprintf(yyget_out(), "floatdcl");
p                               fprintf(yyget_out(), "print");
([0-9]+)                        fprintf(yyget_out(), "inum");
([0-9]+"."[0-9]+)               fprintf(yyget_out(), "fnum");
[a-eghj-oq-z]                   fprintf(yyget_out(), "id");
=                               fprintf(yyget_out(), "assign");
\+                              fprintf(yyget_out(), "plus");
\-                              fprintf(yyget_out(), "minus");
\*                              fprintf(yyget_out(), "mult");
\/                              fprintf(yyget_out(), "div");
\n                              fprintf(yyget_out(), "\n");
\/\/.*[\n]                      { /* IGNORE COMMENTS */ }
%%

int main(int argc, char **argv) {
    FILE    *file;
    FILE    *yyout;

    if (argc == 2)
    {
        if (!(file = fopen(argv[1], "r")))
        {
            perror("Error: ");
            return (-1);
        }
        yyout = fopen("tokens.out", "w"); 
        yyset_in(file);
        yyset_out(yyout);
        yylex();
        fclose(file);
    }
    else
        printf("Error: Wrong number of parameters\n Usage: a.out filename\n");
    return (0);
}