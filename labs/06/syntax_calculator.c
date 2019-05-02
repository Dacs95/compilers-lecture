#define _GNU_SOURCE 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
 
#define MAXSTRING 255 
 
//Declare Functions
bool initialState(); 
bool reserveTok(); //Reserve tokens production
bool A(); //Assign production
bool O(); //Operations production
bool T(); //Type production
bool match(char*); 
void nextToken();  

int lineCounter = 1; 
char line[MAXSTRING];
char *save = NULL; 
char *current = NULL; 
char *graph = "";  
char *saveline; 
bool newLine; 
 
int main(int argc, char **argv){ 
    FILE *file; 
 
    file = fopen(argv[1], "r"); 
    
    if(file == NULL){ 
        perror("Error null file\n Usage: a.out file.txt\n"); 
        exit(EXIT_FAILURE);  
    } 
 
    while(fgets(line,MAXSTRING,file) != NULL){ 
        
        newLine = false; 
        asprintf(&graph,"%sdigraph N",graph); 
        asprintf(&graph,"%s%d",graph,lineCounter); 
        asprintf(&graph,"%s {\n\n",graph); 
        asprintf(&saveline,"%s",line); 
        graph = ""; 
        current = strtok(line," "); 
        bool result = initialState(); 
        
        if(result){ 
            asprintf(&graph,"%s\n}\n\n",graph); 
            printf("Line %d{\n%s",lineCounter-1,graph); 
    
        }
        
    } 
    return 0; 
} 
 
void nextToken(){ 

    if(newLine){ 
        current = "\n"; 
    } 
    else { 
        save = current; 
        current = strtok(NULL," "); 
        if(current[strlen(current)-1] == '\n'){ 
            current[strlen(current)-1] = 0; 
            newLine = true; 
            lineCounter++; 
        } 
    } 
    
    if(current == NULL){
        nextToken();
    } 
} 
 
bool match(char* token){ 
    bool result = false; 
    
    if (strcmp(token, current) == 0){ 
       result = true; 
    } 
    
    nextToken(); 

    return result; 
} 
 
bool initialState(){ 
    return A() && match("\n") || reserveTok() && match("\n"); 
} 
 
bool reserveTok(){ 
    bool result = false; 
 
    if(strcmp(current,"intdcl") == 0){ 
        asprintf(&graph,"%s  S -> {R,newline}\n",graph); 
        asprintf(&graph,"%s  R -> {intdcl,id}\n",graph); 
        result = match("intdcl") && match("id"); 
    } 
    else if(strcmp(current,"print") == 0){ 
        asprintf(&graph,"%s  S -> {R,newline}\n",graph); 
        asprintf(&graph,"%s  R -> {print,id}\n",graph); 
        result = match("print") && match("id"); 
    } 
    else if(strcmp(current,"floatdcl") == 0){ 
        asprintf(&graph,"%s  S -> {R,newline}\n",graph); 
        asprintf(&graph,"%s  R -> {floatdcl,id}\n",graph); 
        result = match("floatdcl") && match("id"); 
    } 
 
    return result; 
} 
 
bool A(){ 
    bool result = false; 
 
    if(strcmp(current,"id") == 0){ 
        asprintf(&graph,"%s  S -> {A,newline}\n",graph); 
        asprintf(&graph,"%s  A -> {id,assign,T,O}\n",graph); 
        result = match("id") && match("assign") && T() && O(); 
    } 
 
    return result; 
} 
 
bool T(){ 
    bool result = false; 
 
    if(strcmp(current,"id") == 0){ 
        asprintf(&graph,"%s  T -> {id}\n",graph); 
        result = match("id"); 
    } 
    else if(strcmp(current,"inum") == 0){ 
        asprintf(&graph,"%s  T -> {inum}\n",graph); 
        result = match("inum"); 
    } 
    else if(strcmp(current,"fnum") == 0){ 
        asprintf(&graph,"%s  T -> {fnum}\n",graph); 
        result = match("fnum"); 
    } 
 
    return result; 
} 

bool O(){ 
    bool result = false; 
 
    if(strcmp(current,"plus") == 0){ 
        asprintf(&graph,"%s  O -> {plus,T,O}\n",graph); 
        result = match("plus") && T() && O(); 
    } 
    else if(strcmp(current,"minus") == 0){ 
        asprintf(&graph,"%s  O -> {minus,T,O}\n",graph); 
        result = match("minus") && T() && O(); 
    } 
    else if(strcmp(current,"multiplication") == 0){ 
        asprintf(&graph,"%s  O -> {multiplication,T,O}\n",graph); 
        result = match("multiplication") && T() && O(); 
    } 
    else if(strcmp(current,"division") == 0){ 
        asprintf(&graph,"%s  O -> {division,T,O}\n",graph); 
        result = match("division") && T() && O(); 
    }else { 
        asprintf(&graph,"%s  O -> {ε}\n",graph); 
        result = true; 
    } 
    return result; 
} 