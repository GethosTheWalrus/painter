// standard dependencies
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// custom dependencies
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

int main() {

    // define a test program
    char *program = "paint rectangle at (x=10 y=10, width=20, height=20)\n";

    // lexically analyze the source code
    list_token tokens = Lex(program);

    // parse the instruction set
    Parse(tokens);

    return 0;

}