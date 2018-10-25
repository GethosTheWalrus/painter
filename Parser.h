int program(node_token *current);
int statement(node_token **current);
int draw_command(node_token ***current);
int instruction(node_token ****current);
int object(node_token ****current);
int function(node_token ***current);
int location(node_token **current);

void Parse(list_token tokens) {

    /*
    PROGRAM -> STATEMENT | PROGRAM NEWLINE STATEMENT
    STATEMENT -> DRAW_COMMAND FUNCTION LOCATION
    DRAW_COMMAND -> INSTRUCTION OBJECT
    LOCATION -> CONTAINER COORD_VAL SEPARATOR COORD_VAL SEPARATOR DIM_VAL SEPARATOR DIM_VAL CONTAINER
    COORD_VAL -> COORDINATE ASSIGNER NUMBER
    DIM_VAL -> DIMENSION ASSIGNER NUMBER
    NUMBER = DIGIT | NUMBER DIGIT
    DIGIT -> 0 | 1 | ... | 9
    ASSIGNER -> =
    DIMENSION -> width | height
    COORDINATE -> x | y
    SEPARATOR -> ,
    CONTAINER -> ( | )
    FUNCTION -> at
    INSTRUCTION -> paint
    OBJECT -> rectangle
    NEWLINE -> \n
    */

    if( tokens.length < 1 ) {

        printf("Error %d: Program must contain at least one instruction\n", 1000);
        return;

    }

    printf("Validating your program containing %d instructions...\n", tokens.length);

    node_token *current = tokens.head;
    // while( current != NULL ) {

    //     printf("{number: %d\ttype: %s\tvalue: %s\tline: %d\tchar: %d}\n", current->token_num, current->token_type, current->token_value, current->line_num, current->char_num);

    //     current = current->next;

    // }

    if( program(current) ) {

        printf("Your program is valid!\n");

    } else {

        printf("Your program is invalid!\n");

    }

}

int program(node_token *current) {

    if( !statement(&current) ) {

        printf("note a program\n");
        return 0;

    }

    printf("%d\n", current->token_num);

    return 1;

}

int statement(node_token **current) {

    if( !draw_command(&current) ) {

        printf("not a statement\n");
        return 0;

    }

    if( !function(&current) ) {

        return 0;

    }

    // if( !location(&current) ) {

    //     return 0;

    // }

    return 1;

}

int draw_command(node_token ***current) {

    if( !instruction(&current) ) {

        printf("not a instruction\n");
        return 0;

    }

    if( !object(&current) ) {

        printf("not a object\n");
        return 0;

    }

    return 1;

}

int instruction(node_token ****current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token ***current_node_pointer_pointer = *current;
    node_token **current_node_pointer = *current_node_pointer_pointer;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "instruction") != 0 ) {

        printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    ***current = current_node_value->next;

    return 1;

}

int object(node_token ****current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token ***current_node_pointer_pointer = *current;
    node_token **current_node_pointer = *current_node_pointer_pointer;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "object") != 0 ) {

        printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    ***current = current_node_value->next;

    return 1;

}

int function(node_token ***current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token **current_node_pointer = *current;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "function") != 0 ) {

        printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    **current = current_node_value->next;

    return 1;

}