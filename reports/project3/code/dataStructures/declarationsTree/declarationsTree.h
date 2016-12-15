#ifndef DECLARATIONS_TREE_H
#define DECLARATIONS_TREE_H

#include <stdbool.h>

#include "../../tokenizer/tokens.h"

typedef struct tree_node {
    char* lex; // The lexeme
    LangType type; // The type
    union {
        bool param; // True if param
        bool add_right; // True if add right to green node
    };

    struct tree_node* left;
    struct tree_node* right;
    struct tree_node* parent;
} tree_node;

typedef struct LinkedTree {
    struct node* head;
} DeclarationsTree;

// Green nodes designate scopes, and blue nodes designate variables
bool check_add_node(Token* decl);
tree_node* get_last_green_node();
tree_node* start_param_matching(Token* id);
void reached_end_of_scope();
LangType get_type(Token* id);

#endif // DECLARATIONS_TREE_H
