// standard dependencies
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// custom dependencies
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

int main() {

    char *filename = "example.painter";

    /* declare a file pointer */
    FILE    *infile;
    char    *buffer;
    long    numbytes;
    
    /* open an existing file for reading */
    infile = fopen(filename, "r");
    
    /* quit if the file does not exist */
    if(infile == NULL)
        return 1;
    
    /* Get the number of bytes */
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    
    /* reset the file position indicator to 
    the beginning of the file */
    fseek(infile, 0L, SEEK_SET);	
    
    /* grab sufficient memory for the 
    buffer to hold the text */
    buffer = (char*)calloc(numbytes, sizeof(char));	
    
    /* memory error */
    if(buffer == NULL)
        return 1;
    
    /* copy all the text into the buffer */
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);
    
    // lexically analyze the source code
    list_token tokens = Lex(buffer);

    /* free the memory we used for the buffer */
    free(buffer);

    // parse the instruction set
    Parse(tokens);

    return 0;

}