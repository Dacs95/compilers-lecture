/* Compilers Lectures Jan - May 2019
   Laboratory Number 2
   Daniel Contreras Segura
   Detect unbalanced: parentheses, brackets, braces, quotes, comments */

#include<stdio.h>

int main(int argc, char* argv[]){

    //Reading the file
    FILE* file = fopen(argv[1], "r");

    if(file == NULL){
        printf("Error: Missing file \n Usage: ./compiler testFile.c");
        return 0;
    }

    int c;
    int braces = 0;
    int brackets = 0;
    int parentheses = 0;
    int comments = 0;
    int strings = 0;
    int lineCount = 0;

    while((c = getc(file)) != EOF){
        if(c == '\n')
            lineCount++;
            
        if (c == '/') {
            //Identify double slash as a comment
            if ((c = getc(file)) != '/') {  
                comments++;
            }
          //Count the number of parentheses, brackets, and braces    
        } else if (c == '(') { 
            parentheses++;
        } else if (c == ')') {
            parentheses--;
        } else if (c == '{') {
            brackets++;
        } else if (c == '}') {
            brackets--;
        } else if (c == '[') {
            braces++;
        } else if (c == ']') {
            braces--;
        } else if (c == '\'' || c == '"') {
            int temp;
            while((temp = getc(file)) != c) {
                if (temp = '\\') {
                    strings++;
                    break;
                }
            }
        }
    }
    //Print detected errors
    if (braces > 0) {
        printf("Missing %d ]\n", braces);
    }

    if (braces < 0) {
        printf("Missing %d [\n", braces);
    }

    if (brackets > 0) {
        printf("Missing %d }\n", brackets);
    }

    if (brackets < 0) {
        printf("Missing %d {\n", brackets * -1);
    }

    if (parentheses > 0) {
        printf("Missing %d )\n", parentheses);
    }

    if (parentheses < 0) {
        printf("Missing %d (\n", parentheses);
    }

    if (comments > 0) {
        printf("Missing %d /\n", comments);
    }

    if (strings > 0) {
        printf("%d incomplete string declaration\n", strings);
    }

    if(braces == 0 && brackets == 0 && parentheses == 0){
        printf("There is no errors");
    }

    return 0;
}