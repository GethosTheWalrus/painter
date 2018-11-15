int program(node_token *current);
int statement(node_token **current);
int newline(node_token **current);
int draw_command(node_token ***current);
int function(node_token ***current);
int location(node_token ***current);
int object(node_token ****current);
int instruction(node_token ****current);
int container_left(node_token ****current);
int container_right(node_token ****current);
int coord_val(node_token ****current);
int separator(node_token ****current);
int dim_val(node_token ****current);
int coordinate(node_token *****current);
int dimension(node_token *****current);
int assigner(node_token *****current);
int number(node_token *****current);

void Parse(list_token tokens) {

    /*
    PROGRAM -> STATEMENT | PROGRAM NEWLINE STATEMENT
    STATEMENT -> DRAW_COMMAND FUNCTION LOCATION
    DRAW_COMMAND -> INSTRUCTION OBJECT
    LOCATION -> CONTAINER_LEFT COORD_VAL SEPARATOR COORD_VAL SEPARATOR DIM_VAL SEPARATOR DIM_VAL CONTAINER_RIGHT
    COORD_VAL -> COORDINATE ASSIGNER NUMBER
    DIM_VAL -> DIMENSION ASSIGNER NUMBER
    NUMBER = DIGIT | NUMBER DIGIT
    DIGIT -> 0 | 1 | ... | 9
    ASSIGNER -> =
    DIMENSION -> width | height
    COORDINATE -> x | y
    SEPARATOR -> ,
    CONTAINER_LEFT -> (
    CONTAINER_RIGHT -> )
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

    int valid = 0;
    if( program(current) == 1 ) {

        printf("Your program has been successfully validated!");

    }

}

int program(node_token *current) {

    // There are no more tokens to parse
    if( current == NULL ) {

        return 1;

    }

    // Validate that we are given a statement
    if( statement(&current) == 0 ) {

        printf("There is an error in your program on line %d character number %d token number %d:\nUnexpected %s encountered: %s", current->line_num, current->char_num, current->token_num, current->token_type, current->token_value);
        return 0;

    }


    // If we encounter a newline after a statement, check for another statement
    if( newline(&current) == 1 ) {

        return program(current);

    }

    return 1;

}

int statement(node_token **current) {

    if( draw_command(&current) == 0 ) {

        // printf("not a draw_command\n");
        return 0;

    }

    if( function(&current) == 0 ) {

        // printf("not a function\n");
        return 0;

    }

    if( location(&current) == 0 ) {

        // printf("not a location\n");
        return 0;

    }

    return 1;

}

int newline(node_token **current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token *current_node_value = *current;

    // return if the current node value is null
    if( current_node_value == 0 ) {

        return 0;

    }
    
    if( strcmp(current_node_value->token_type, "newline") != 0 ) {

        printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    *current = current_node_value->next;

    return 1;

}

int draw_command(node_token ***current) {

    if( instruction(&current) == 0 ) {

        // printf("not a instruction\n");
        return 0;

    }

    if( object(&current) == 0 ) {

        // printf("not a object\n");
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

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
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

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
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

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    **current = current_node_value->next;

    return 1;

}

int location(node_token ***current) {
    
    if( container_left(&current) == 0 ) {

        // printf("not a container_right\n");
        return 0;

    }

    if( coord_val(&current) == 0 ) {

        // printf("not a coord_val\n");
        return 0;

    }

    if( separator(&current) == 0 ) {

        // printf("not a separator\n");
        return 0;

    }

    if( coord_val(&current) == 0 ) {

        // printf("not a coord_val\n");
        return 0;

    }

    if( separator(&current) == 0 ) {

        // printf("not a separator\n");
        return 0;

    }

    if( dim_val(&current) == 0 ) {

        // printf("not a dim_val\n");
        return 0;

    }

    if( separator(&current) == 0 ) {

        // printf("not a separator\n");
        return 0;

    }

    if( dim_val(&current) == 0 ) {

        // printf("not a dim_val\n");
        return 0;

    }

    if( container_right(&current) == 0 ) {

        // printf("not a container_right\n");
        return 0;

    }

}

int container_left(node_token ****current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token ***current_node_pointer_pointer = *current;
    node_token **current_node_pointer = *current_node_pointer_pointer;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "container_left") != 0 ) {

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    ***current = current_node_value->next;

    return 1;

}

int container_right(node_token ****current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token ***current_node_pointer_pointer = *current;
    node_token **current_node_pointer = *current_node_pointer_pointer;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "container_right") != 0 ) {

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    ***current = current_node_value->next;

    return 1;

}

int coord_val(node_token ****current) {

    if( coordinate(&current) == 0 ) {

        // printf("not a coordinate\n");
        return 0;

    }

    if( assigner(&current) == 0 ) {

        // printf("not a assigner\n");
        return 0;

    }

    if( number(&current) == 0 ) {

        // printf("not a number\n");
        return 0;

    }

    return 1;

}

int dim_val(node_token ****current) {

    if( dimension(&current) == 0 ) {

        // printf("not a dimension\n");
        return 0;

    }

    if( assigner(&current) == 0 ) {

        // printf("not a assigner\n");
        return 0;

    }

    if( number(&current) == 0 ) {

        // printf("not a number\n");
        return 0;

    }

    return 1;

}

int separator(node_token ****current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token ***current_node_pointer_pointer = *current;
    node_token **current_node_pointer = *current_node_pointer_pointer;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "separator") != 0 ) {

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    ***current = current_node_value->next;

    return 1;

}

int coordinate(node_token *****current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token ****current_node_pointer_pointer_pointer = *current;
    node_token ***current_node_pointer_pointer = *current_node_pointer_pointer_pointer;
    node_token **current_node_pointer = *current_node_pointer_pointer;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "coordinate") != 0 ) {

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    ****current = current_node_value->next;

    return 1;

}

int assigner(node_token *****current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token ****current_node_pointer_pointer_pointer = *current;
    node_token ***current_node_pointer_pointer = *current_node_pointer_pointer_pointer;
    node_token **current_node_pointer = *current_node_pointer_pointer;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "assigner") != 0 ) {

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    ****current = current_node_value->next;

    return 1;

}

int number(node_token *****current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token ****current_node_pointer_pointer_pointer = *current;
    node_token ***current_node_pointer_pointer = *current_node_pointer_pointer_pointer;
    node_token **current_node_pointer = *current_node_pointer_pointer;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "number") != 0 ) {

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    ****current = current_node_value->next;

    return 1;

}

int dimension(node_token *****current) {

    // set a temporary value equal to the value referenced by the double pointer
    node_token ****current_node_pointer_pointer_pointer = *current;
    node_token ***current_node_pointer_pointer = *current_node_pointer_pointer_pointer;
    node_token **current_node_pointer = *current_node_pointer_pointer;
    node_token *current_node_value = *current_node_pointer;
    
    if( strcmp(current_node_value->token_type, "dimension") != 0 ) {

        // printf("token %d is a %s\n", current_node_value->token_num, current_node_value->token_type);
        return 0;

    }

    // set the value of the current node equal to the next node (referencing the double pointer)
    ****current = current_node_value->next;

    return 1;

}