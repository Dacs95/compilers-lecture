%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYSTYPE char *
extern FILE * yyin;
extern FILE * yyout;
extern int yylineno;

%}

%start program
%token inum fnum floatdcl intdcl asig print id newline
%token plus min mult division
%left plus min 
%left mult division

%%

program: /* empty */
    | program line /* dont do anything*/
    ;
line: assign newline { fprintf(yyout , "digraph line%d {\n\tAssign -> %s\n}\n\n", yylineno - 1 , $$);}
    | declaration newline { fprintf(yyout , "digraph line%d {\n\tDeclaration -> %s\n}\n\n", yylineno - 1 , $$);}
    | output newline { fprintf(yyout , "digraph line%d {\n\tOutput -> %s\n}\n\n", yylineno - 1 , $$);}    
    ;
assign: id asig id operators num{
        char string[200];
        strcpy (string, "id1, asig, id2, operators, num\n\toperators -> ");
        strcat (string ,$4);
        strcat (string, "\n\tnum -> ");
        strcat (string, $5);
        $$ = string;
    }
    | id asig id operators id{
        char string[250];
        strcpy (string, "id1, asig , id2, operators, id\n\toperators -> ");
        strcat (string ,$4);
        $$ = string;
    }
    | id asig num {
        char string[100];
        strcpy (string, "id, asig , num\n\tnum -> ");
        strcat (string, $3);
        $$ = string; 
    };

declaration: type id {
        char string[100];
        strcpy (string, "type, id \n\ttype -> ");
        strcat (string, $$);
        $$ = string;
    };

output: print num{
        char string[100];
        strcpy (string, "print, num\n\tnum -> ");
        strcat (string, $2);
        $$ = string;
    }
    | print id {
        $$ = "print id";
    };

type: intdcl { $$ = "intdcl";}
    | floatdcl { $$ = "floatdcl";}
    ;

num: inum { $$ = "inum";}
    | fnum { $$ = "fnum";}
    ;

operators: plus { $$ = "plus";} 
    | min { $$ = "minus";}
    | mult { $$ = "mult";}
    | division { $$ = "division";}
    ;
%%

int main (int argc, char **argv){
    FILE *file;

    //Validate the input file is pass like a parameter to the program
    if( argc != 2) {
        printf("To run the code please use the next format: source inputFile \n");
        exit(1);
    }
    //check if the file can be read using flex input yyin
    if ( !(yyin = fopen(argv[1], "r"))){
        printf("Sorry, wrong file\n");
        exit(1);
    }

    //Use flex to output the parse tree 
    yyout = fopen("derivationTree.dot", "w");
    
    return yyparse( );
}
int yyerror (char *s) {
    fprintf(stderr, "%s\n", s);
}