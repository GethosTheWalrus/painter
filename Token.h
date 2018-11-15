#include <stdlib.h>

// object for individual tokens
typedef struct node {
    char *token_type;
    char *token_value;
    struct node *next;
    int line_num;
    int char_num;
    int token_num;
} node_token;

// object for list of tokens
typedef struct list {
    struct node *head;
    struct node *tail;
    int length;
} list_token;

// add a token to the list
void push(list_token *l, char *token_type, char *token_value, int line_num, int char_num, int token_num) {

    node_token *n = malloc(sizeof(node_token));

    if( l->length == 0 ) {

        l->head = l->tail = n;

    } else {

        l->tail->next = n;
        l->tail = n;
        n->next = NULL;

    }

    n->token_type = token_type;
    n->token_value = token_value;
    n->line_num = line_num;
    n->char_num = char_num;
    n->token_num = token_num;
    l->length += 1;

    // free(n);

}