int program(node_token *current);
int statement(node_token **current);
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
    while( current != NULL ) {

        printf("{number: %d\ttype: %s\tvalue: %s\tline: %d\tchar: %d}\n", current->token_num, current->token_type, current->token_value, current->line_num, current->char_num);

        current = current->next;

    }

    if( program(current) ) {

        printf("Your program has been successfully validated!\n");

    }

}

int program(node_token *current) {

    if( !statement(&current) ) {

        printf("There is an error in your on line %d character number %d:\nUnexpected %s encountered: %s", current->line_num, current->char_num, current->token_type, current->token_value);
        return 0;

    }

    // printf("%d\n", current->token_num);

    return 1;

}

int statement(node_token **current) {

    if( !draw_command(&current) ) {

        // printf("not a statement\n");
        return 0;

    }

    if( !function(&current) ) {

        return 0;

    }

    if( !location(&current) ) {

        return 0;

    }

    return 1;

}

int draw_command(node_token ***current) {

    if( !instruction(&current) ) {

        // printf("not a instruction\n");
        return 0;

    }

    if( !object(&current) ) {

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
    
    if( !container_left(&current) ) {

        // printf("not a container_right\n");
        return 0;

    }

    if( !coord_val(&current) ) {

        // printf("not a coord_val\n");
        return 0;

    }

    if( !separator(&current) ) {

        // printf("not a separator\n");
        return 0;

    }

    if( !coord_val(&current) ) {

        // printf("not a coord_val\n");
        return 0;

    }

    if( !separator(&current) ) {

        // printf("not a separator\n");
        return 0;

    }

    if( !dim_val(&current) ) {

        // printf("not a dim_val\n");
        return 0;

    }

    if( !separator(&current) ) {

        // printf("not a separator\n");
        return 0;

    }

    if( !dim_val(&current) ) {

        // printf("not a dim_val\n");
        return 0;

    }

    if( !container_right(&current) ) {

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

    if( !coordinate(&current) ) {

        // printf("not a coordinate\n");
        return 0;

    }

    if( !assigner(&current) ) {

        // printf("not a assigner\n");
        return 0;

    }

    if( !number(&current) ) {

        // printf("not a number\n");
        return 0;

    }

    return 1;

}

int dim_val(node_token ****current) {

    if( !dimension(&current) ) {

        // printf("not a dimension\n");
        return 0;

    }

    if( !assigner(&current) ) {

        // printf("not a assigner\n");
        return 0;

    }

    if( !number(&current) ) {

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