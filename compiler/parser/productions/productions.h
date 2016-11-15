#ifndef voidS_H
#define voidS_H
#include "../../tokenizer/tokens.h"

extern Token* queuedToken;

void program();
void id_list();
void id_list_tail();
void declarations();
void type();
void standard_type();
void subprogram_declarations();
void subprogram_declaration();
void subprogram_head();
void arguments();
void parameter_list();
void parameter_list_tail();
void compound_statement();
void optional_statements();
void statement_list();
void statement_list_tail();
void statement();
void else_tail();
void variable();
void array_access();
void procedure_statement();
void optional_expressions();
void expression_list();
void expression_list_tail();
void experssion();
void related_expression();
void simple_expression();
void simple_expression_tail();
void term();
void term_tail();
void factor();
void sign();

#endif // voidS_H
