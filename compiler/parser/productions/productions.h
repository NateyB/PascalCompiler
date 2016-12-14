#ifndef voidS_H
#define voidS_H
#include <stdio.h>
#include <stdlib.h>

#include "../../globals/globals.h"
#include "../../tokenizer/tokens.h"
#include "../../dataStructures/declarationsTree/declarationsTree.h"
#include "../../errorHandler/errorHandler.h"

extern Token* current_tok;

// All of these must have their follows added to the sync set
void program();
void id_list();
void id_list_tail();
void declarations();
LangType type();
LangType standard_type();
void subprogram_declarations();
void subprogram_declaration();
bool subprogram_head();
void arguments();
void parameter_list();
void parameter_list_tail();
void compound_statement();
void optional_statements();
void statement_list();
void statement_list_tail();
void statement();
void else_tail();
LangType variable();
LangType array_access(LangType id_type);
void procedure_statement();
void optional_expressions();
void expression_list();
void expression_list_tail();
LangType expression();
LangType related_expression();
LangType simple_expression();
LangType simple_expression_tail();
LangType term();
LangType term_tail();
LangType factor();
LangType factor_tail();
void sign();

#endif // voidS_H
