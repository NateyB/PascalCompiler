#include<string.h>

#include "tokens.h"

const char* catNames[] = {"NOOP", "FILEEND", "ASSIGNOP", "RELOP", "ID",
                         "CONTROL", "ADDOP", "MULOP", "WS", "ARRAY", "TYPE",
                         "VAR", "NUM", "PUNC", "GROUP", "INVERSE",
                         "LEXERR", "SYNERR", "SEMERR"};

const Token eof_tok = {
    FILEEND, 0, false, 0, 0
};
const Token lparen_tok = {
    GROUP, 0, true, 0, 0
};
const Token rparen_tok = {
    GROUP, 1, true, 0, 0
};
const Token plus_tok = {
    ADDOP, 0, true, 0, 0
};
const Token comma_tok = {
    PUNC, 0, true, 0, 0
};
const Token minus_tok = {
    ADDOP, 1, true, 0, 0
};
const Token semic_tok = {
    PUNC, 1, true, 0, 0
};
const Token colon_tok = {
    TYPE, 0, true, 0, 0
};
const Token dotdot_tok = {
    ARRAY, 1, true, 0, 0
};
const Token period_tok = {
    PUNC, 2, true, 0, 0
};
const Token lbrac_tok = {
    GROUP, 2, true, 0, 0
};
const Token rbrac_tok = {
    GROUP, 3, true, 0, 0
};
const Token addop_tok = {
    ADDOP, 0, false, 0, 0
};
const Token array_tok = {
    ARRAY, 0, true, 0, 0
};
const Token assignop_tok = {
    ASSIGNOP, 0, true, 0, 0
};
const Token begin_tok = {
    CONTROL, 0, true, 0, 0
};
const Token call_tok = {
    CONTROL, 10, true, 0, 0
};
const Token do_tok = {
    CONTROL, 1, true, 0, 0
};
const Token else_tok = {
    CONTROL, 2, true, 0, 0
};
const Token end_tok = {
    CONTROL, 3, true, 0, 0
};
const Token id_tok = {
    ID, 0, false, 0, 0
};
const Token if_tok = {
    CONTROL, 5, true, 0, 0
};
const Token integer_tok = {
    TYPE, 1, true, 0, 0
};
const Token integer_val_tok = {
    NUM, 0, true, 0, 0
};
const Token of_tok = {
    ARRAY, 2, true, 0, 0
};
const Token real_val_tok = {
    NUM, 1, true, 0, 0
};
const Token mulop_tok = {
    MULOP, 0, false, 0, 0
};
const Token not_tok = {
    INVERSE, 0, true, 0, 0
};
const Token num_tok = {
    NUM, 0, false, 0, 0
};
const Token procedure_tok = {
    CONTROL, 6, true, 0, 0
};
const Token program_tok = {
    CONTROL, 7, true, 0, 0
};
const Token real_tok = {
    TYPE, 2, true, 0, 0
};
const Token relop_tok = {
    RELOP, 0, false, 0, 0
};
const Token then_tok = {
    CONTROL, 8, true, 0, 0
};
const Token var_tok = {
    VAR, 0, true, 0, 0
};
const Token while_tok = {
    CONTROL, 9, true, 0, 0
};

static const char* lexes[] = {"(", ")", "+", ",", "-", ";", ":", "[", "]", "addop",
                              "array", "assignop", "begin", "call", "do", "else",
                              "end", "ID", "if", "integer", "mulop", "not",
                              "num", "procedure", "program", "real", "relop",
                              "then", "var", "while", "EOF", "..", ":", ".",
                               "int value", "of", "real value"};

static const Token* tokens[] = {&lparen_tok, &rparen_tok, &plus_tok, &comma_tok, &minus_tok, &semic_tok,
                                &colon_tok, &lbrac_tok, &rbrac_tok, &addop_tok, &array_tok, &assignop_tok,
                                &begin_tok, &call_tok, &do_tok, &else_tok, &end_tok, &id_tok,
                                &if_tok, &integer_tok, &mulop_tok, &not_tok, &num_tok,
                                &procedure_tok, &program_tok, &real_tok, &relop_tok, &then_tok,
                                &var_tok, &while_tok, &eof_tok, &dotdot_tok,
                                &colon_tok, &period_tok, &integer_val_tok,
                                &of_tok, &real_val_tok};

const Token* getTokenFromLex(char* lex) {
    for (int i = 0;  i < sizeof(lexes); i++) {
        if (strcmp(lexes[i], lex) == 0)
            return tokens[i];
    }

    return NULL;
}

const char* getLexFromToken(Token* token, bool strict) {
    switch (token -> attribute) {
        case FILEEND: return "EOF";
        case ASSIGNOP: return ":=";

        case RELOP: if (strict)
            switch (token -> aspect) {
                case 0: return "<";
                case 1: return "<=";
                case 2: return "=";
                case 3: return ">";
                case 4: return ">=";
                case 5: return "<>";
            }
            else return "RELOP";

        case ID: return "ID";

        case CONTROL: if (!strict) return "CONTROL"; else
            switch (token -> aspect) {
                case 0: return "begin";
                case 1: return "do";
                case 2: return "else";
                case 3: return "end";
                case 4: return "function";
                case 5: return "if";
                case 6: return "procedure";
                case 7: return "program";
                case 8: return "then";
                case 9: return "while";
                case 10: return "call";
            }

        case ADDOP: if (!strict) return "ADDOP"; else
            switch (token -> aspect) {
                case 0: return "+";
                case 1: return "-";
            }

        case MULOP: if (!strict) return "MULOP"; else
            switch (token -> aspect) {
                case 0: return "*";
                case 1: return "/";
            }

        case ARRAY: if (!strict) return "ARRAY"; else
            switch (token -> aspect) {
                case 0: return "array";
                case 1: return "..";
                case 2: return "of";
            }

        case TYPE: switch (token -> aspect) {
            case 0: return ":";
            case 1: return "integer";
            case 2: return "real";
        }

        case VAR: switch (token -> aspect) {
            case 0: return "var";
        }

        case NUM: switch (token -> aspect) {
            case 0: return "an integer";
            case 1: return "a real";
        }

        case PUNC: switch (token -> aspect) {
            case 0: return ",";
            case 1: return ";";
            case 2: return ".";
        }

        case GROUP: switch (token -> aspect) {
            case 0: return "(";
            case 1: return ")";
            case 2: return "[";
            case 3: return "]";
        }

        case INVERSE: switch (token -> aspect) {
            case 0: return "not";
        }

        case NOOP:
        case WS:
        case LEXERR:
        case SYNERR:
        case SEMERR: return "An error in the compiler has occurred.";
    }
}

// Returns true if the tokens are equivalent, false otherwise
bool tokens_equal(const Token* p1, Token* p2, bool strict) {
    return p1 -> attribute == p2 -> attribute &&
            (!strict || p1 -> aspect == p2 -> aspect);
}

LangType convert_to_array(LangType type) {
    switch (type) {
        case INT: return AINT;
        case REAL: return AREAL;

        default: return ERR; // TODO: SEMERR!!
    }
}

LangType convert_from_array(LangType type) {
    switch (type) {
        case AINT: return INT;
        case AREAL: return REAL;

        default: return ERR; // TODO: SEMERR!!
    }
}

static LangType assignop_lookup(LangType first, LangType second) {
    if (first == ERR || second == ERR) // just an err
        // NOOP
        return ERR;
    else if (first != INT || second != REAL
            || first != INT || second != REAL)
        // SEMERR, type mismatch
        return ERR;
    else if (first != second)
        // SEMERR, type coercion attempted
        return ERR;

    return NULL;
}

static LangType relop_lookup(LangType first, LangType second) {
    if (first == second && (first == INT || first == REAL))
        return BOOL;
    else if (first != ERR && second != ERR)
        // SEMERR, type coercion attempted
        ;

    return ERR;
}

static LangType addop_lookup(LangType first, LangType second, int opcode) {
    switch (opcode) {
        case 0:
        case 1: if (first == second && (first == INT || first == REAL))
                    return first;
                else if (first != ERR && second != ERR)
                    // SEMERR: Type coercion
                    ;

                return ERR;


        case 2: if (first == second && first == BOOL)
                    return BOOL;
                else if (first != ERR && second != ERR)
                    // SEMERR: Type coercion
                    ;

                return ERR;

        default: return NULL;
    }
}

static LangType mulop_lookup(LangType first, LangType second, int opcode) {
    switch (opcode) {
        case 0:
        case 1: if (first == second && (first == INT || first == REAL))
                    return first;
                else if (first != ERR && second != ERR)
                    // SEMERR: Type coercion
                    ;

                return ERR;


        case 2: if (first == second && first == BOOL) // and
                    return BOOL;
                else if (first != ERR && second != ERR)
                    // SEMERR: Type coercion
                    ;

                return ERR;

        case 3: // div; mod
        case 4: if (first == second && first == INT)
                    return INT;
                else if (first != ERR && second != ERR)
                    // SEMERR: Type coercion
                    ;

                return ERR;

        default: return NULL;
    }
}

static LangType not_lookup(LangType first, LangType second) {
    if (first == second && first == BOOL) // and
        return BOOL;
    else if (first != ERR && second != ERR)
        // SEMERR: Type coercion
        ;

    return ERR;
}

static LangType array_lookup(LangType first, LangType second) {
    if (first == second && first == INT)
        return INT;
    else if (first != ERR && second != ERR)
        // SEMERR:
        ;

    return ERR;
}

LangType type_lookup(LangType first, LangType second, Token* op) {
    switch (op -> attribute) {
        // Operations which are meaninngless
        case NOOP:
        case LEXERR:
        case SYNERR:
        case SEMERR:
        case GROUP:
        case PUNC:
        case FILEEND:
        case ID:
        case CONTROL:
        case WS:
        case TYPE:
        case VAR:
        case NUM: return NULL;

        case ASSIGNOP: return assignop_lookup(first, second);
        case RELOP: return relop_lookup(first, second);
        case ADDOP: return addop_lookup(first, second, op -> aspect);
        case ARRAY: return array_lookup(first, second);
        case MULOP: return mulop_lookup(first, second, op -> aspect);
        case INVERSE: return not_lookup(first, second);

    }
}
