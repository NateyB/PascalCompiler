#ifndef PRODUCTIONS_H
#define PRODUCTIONS_H
#include "../../tokenizer/tokens.h"

// The production type
typedef void (*production)(Token* handle);

production program;
production id_list;
production id_list_tail;
production declarations;
production type;
production standard_type;
production subprogram_declarations;
production subprogram_declaration;
production subprogram_head;
production arguments;
production parameter_list;
production parameter_list_tail;
production compound_statement;
production optional_statements;
production statement_list;
production statement_list_tail;
production statement;
production else_tail;
production variable;
production array_access;
production procedure_statement;
production optional_expressions;
production expression_list;
production expression_list_tail;
production experssion;
production related_expression;
production simple_expression;
production simple_expression_tail;
production term;
production term_tail;
production factor;
production sign;

#endif // PRODUCTIONS_H
