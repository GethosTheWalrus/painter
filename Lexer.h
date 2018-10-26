list_token Lex(char *stream) {

    printf("Analyzing your source code...\n");

    list_token tokens = {
        (node_token*)malloc(sizeof(node_token)),
        (node_token*)malloc(sizeof(node_token)),
        0
    };
    
    // initializing the token number, line number, and character number (per line)
    int char_num = 0;
    int line_num = 1;
    int token_num = 1;

    for(int i = 0; stream[i] != '\0'; i++) {

        // reserve memory for token type and token value pointers
        char *token_type = malloc(17 * sizeof(char));
        char *token_value = malloc(17 * sizeof(char));

        // reserve memory for the current_token string (16 char maximum token length)
        char *current_token = malloc(17 * sizeof(char));
        
        // increment line num if we encounter a newline character
        // do not add newlines as tokens
        if( stream[i] == '\n' ) {

            // new line, so increment line_num and reset char_num
            line_num += 1;
            char_num = 0;

            token_type = "newline";
            token_value[0] = stream[i];
            token_value[1] = '\0';

        // spaces are a token
        } else if( stream[i] == ' ' ) {

            token_type = "space";
            token_value[0] = stream[i];
            token_value[1] = '\0';

        // operators are a token = : + - * /
        } else if( stream[i] == '=' || stream[i] == ':' || stream[i] == '+' || stream[i] == '-' || stream[i] == '*' || stream[i] == '/') {

            token_type = "operator";
            token_value[0] = stream[i];
            token_value[1] = '\0';

        // separators are a token ( ) ,
        } else if( stream[i] == ')' || stream[i] == '(' || stream[i] == ',') {

            token_type = "separator";
            token_value[0] = stream[i];
            token_value[1] = '\0';

        // variables, keywords, etc
        } else if( isalpha(stream[i]) || isdigit(stream[i]) ) {
            
            // build the next token_value out of the string of consecutive alpha characters
            int was_a_word = 0;
            int current_token_tracker = 0;
            for( int current_token_count = 0; isalpha(stream[i]); current_token_count++ ) {

                was_a_word = 1;
                token_type = "word";
                current_token[current_token_count] = stream[i];
                current_token_tracker += 1;
                i += 1;

            }

            // build the next token_value out of the string of consecutive numeric characters
            for( int current_token_count = 0; was_a_word != 1 && isdigit(stream[i]); current_token_count++ ) {

                token_type = "number";
                current_token[current_token_count] = stream[i];
                current_token_tracker += 1;
                i += 1;

            }

            // add the null character to the end of the current_token string and set the token_value
            // of our next token equal to current_token
            current_token[current_token_tracker] = '\0';
            token_value = current_token;
            i -= 1;
            
        } else {
            
            // For each character that isn't a space, build the next token string
            int current_token_tracker = 0;
            for( int current_token_count = 0; stream[i] != ' ' && stream[i] != '\0'; current_token_count++ ) {

                // printf("%c\n", stream[i]);
                token_type = "unknown";
                current_token[current_token_count] = stream[i];
                current_token_tracker += 1;
                i += 1;

            }

            current_token[current_token_tracker] = '\0';

            token_value = current_token;
            i -= 1;

        }

        // check if any word tokens are special tokens
        if( token_type == "word" ) {

            if( strcmp(token_value, "paint") == 0 ) {

                token_type = "instruction";

            } else if( strcmp(token_value, "rectangle") == 0 ) {

                token_type = "object";

            } else if( strcmp(token_value, "at") == 0 ) {

                token_type = "function";

            } else if( strcmp(token_value, "x") == 0 || strcmp(token_value, "y") == 0 ) {

                token_type = "coordinate";

            } else if( strcmp(token_value, "width") == 0 || strcmp(token_value, "height") == 0 ) {

                token_type = "dimension";

            }

        // check if any operator tokens are assignment operators
        } else if( token_type == "operator" ) {

            if( strcmp(token_value, "=") == 0 ) {

                token_type = "assigner";

            }

        // check if any separators are containers
        } else if( token_type == "separator" ) {

            if( strcmp(token_value, "(") == 0 ) {

                token_type = "container_left";

            } else if( strcmp(token_value, ")") == 0 ) {

                token_type = "container_right";

            }

        } 


        // add the token to the list of tokens
        if( strcmp(token_type, "space") != 0 ) {

            push(&tokens, token_type, token_value, line_num, char_num, token_num);

        }

        // increment the character number by the length of token_value
        char_num += strlen(token_value);

        // increment the token number after adding token to the list
        token_num += 1;

        // free all reserved memory for this iteration
        free(token_type);
        free(token_value);
        free(current_token);

    }

    return tokens;

}