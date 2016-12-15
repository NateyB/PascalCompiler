#include <stdlib.h>
#include <stdio.h>

#include "../../handler/handler.h"
#include "../../errorHandler/errorHandler.h"
#include "../../globals/globals.h"
#include "declarationsTree.h"

static int offset = 0;

static DeclarationsTree* d_tree = NULL;
static tree_node* bottom_node = NULL;

static LinkedList* green_node_stack = NULL;

static void initialize_d_tree() {
    d_tree = malloc(sizeof(*d_tree));
    green_node_stack = malloc(sizeof(*green_node_stack));
}

static int get_width(Token* val) {
    switch (val -> type) {
        case INT: return 4;
        case REAL: return 8;

        case AINT: return 4*(val -> array_length);
        case AREAL: return 8*(val -> array_length);

        default: return 1000000;
    }
}

static bool check_node(char* id, bool green) {
    tree_node* current_node = bottom_node;
    while (current_node != NULL) {
        // Already exists
        if (id == current_node -> lex)
            return true;

        if (!green && (current_node -> type == PROC || current_node -> type == PGNAME))
            return false;

        // We've passed the most recent green node, and this is a blue one
        if (!green && (current_node -> type == PROC || current_node -> type == PGNAME))
            break;

        current_node = current_node -> parent;
    }

    return false;
}

static bool check_add_green_node(Token* decl) {
    if (d_tree == NULL)
        initialize_d_tree();

    if (bottom_node == NULL)
    {
        tree_node* addition = malloc(sizeof(*addition));
        addition -> lex = decl -> id;
        addition -> type = decl -> type;
        addition -> add_right = false;

        // Add it to the top of the stack
        add(green_node_stack, &addition, sizeof(&addition));

        addition -> left = NULL;
        addition -> right = NULL;
        addition -> parent = NULL;
        bottom_node = addition;
        return true;
    }

    // Check if it's been declared at all
    if (check_node(decl -> id, true))
        return false;

    offset = 0;

    // It hasn't been declared; create it
    tree_node* addition = malloc(sizeof(*addition));
    addition -> lex = decl -> id;
    addition -> type = decl -> type;
    addition -> add_right = false;

    // Add it to the top of the stack
    add(green_node_stack, &addition, sizeof(&addition));

    addition -> left = NULL;
    addition -> right = NULL;
    addition -> parent = bottom_node;

    // Make it the new bottom node
    if (bottom_node -> add_right == true)
        bottom_node -> right = addition;
    else
        bottom_node -> left = addition;

    bottom_node = addition;

    return true;
}


static bool check_add_blue_node(Token* decl) {
    // If there's no scope, that's an error!
    if (d_tree == NULL)
        return false;

    // It's been declared in the scope already
    if (check_node(decl -> id, false))
        return false;

    // It hasn't been declared; create it
    tree_node* addition = malloc(sizeof(*addition));
    addition -> lex = decl -> id;
    //printf("%s\n", addition -> lex);
    addition -> type = decl -> type;
    addition -> param = decl -> param;

    if (!addition -> param)
    {
        outputWidth(addition -> lex, offset);
        offset += get_width(decl);
    }

    addition -> left = NULL;
    addition -> right = NULL;
    addition -> parent = bottom_node;

    bottom_node -> left = addition;
    bottom_node = addition;

    //printf("(%s, %s)\n", bottom_node -> lex, bottom_node -> parent -> lex);
    return true;
}

tree_node* start_param_matching(Token* id) {
    tree_node* current_node = bottom_node;
    while (current_node != NULL)
    {
        if (current_node -> type == PROC && current_node -> lex == id -> id)
            return current_node;
        current_node = current_node -> parent;
    }

    return NULL;
}

bool check_add_node(Token* decl) {
    char* errorMessage ;
    switch (decl -> type) {
        case PGNAME:
        case PROC: if (!check_add_green_node(decl)) {
                       errorMessage = calloc(100, sizeof(*errorMessage));
                       sprintf(errorMessage,
                            "A program or procedure named '%.*s' is already defined in this scope!",
                            decl -> length, &BUFFER[decl -> start]);
                        throw_sem_error(errorMessage);
                        return false;
                   }
                   return true;

        default: if (!check_add_blue_node(decl)) {
                       errorMessage = calloc(100, sizeof(*errorMessage));
                       sprintf(errorMessage,
                            "A variable named '%.*s' is already defined in the local scope!",
                            decl -> length, &BUFFER[decl -> start]);
                        throw_sem_error(errorMessage);
                        return false;
                   }
                   return true;
        }
}

void reached_end_of_scope() {
    bottom_node = (*(tree_node**) pop(green_node_stack));
    bottom_node -> add_right = true;
}


LangType get_type(Token* id) {
    if (id == NULL)
        return ERR;
        
    tree_node* current_node = bottom_node;
    while (current_node != NULL)
    {
        if (current_node -> lex == id -> id)
            return current_node -> type;

        current_node = current_node -> parent;
    }

    return NULL;
}
