#include<stdlib.h>
#include<stdbool.h>

#include "../tokenizer/tokens.h"
#include "productions/productions.h"
#include "../tokenizer/tokenizer.h"
#include "../handler/handler.h"
#include "../errorHandler/errorHandler.h"

Token* current_tok = NULL;

static bool should_print_synerr = true;
static bool sequence_running = true;

Token* get_next_relevant_token()
{
    const Token* next = malloc(sizeof(*next));
    if (sequence_running)
    {
        do {
            next = getNextToken();
            if (!handleToken(next))
            {
                sequence_running = false;
                next = &eof_tok;
                break;
            }
        } while (next -> attribute == WS || next -> attribute == NOOP
                 || next -> attribute >= LEXERR);
    } else {
        should_print_synerr = false;
        next = &eof_tok;
    }

    return next;
}

void require_sync(const Token* sync_set[], int size,
                  const Token* first_set[], int first_size)
{
    if (should_print_synerr) {
        printf("Found '%s'; expected ", getLexFromToken(current_tok, true));
        for (int i = first_size - 1; i >= 0; i--) {
            printf("'%s'", getLexFromToken(first_set[i], first_set[i] -> start));
            if (i > 0)
                printf(", ");
        }
        printf(" instead.\n");
    }
    while (true) {
        for (int i = 0; i < size; i++)
        {
            const Token* sync_token = sync_set[i];
            if (tokens_equal(sync_token, current_tok, sync_token -> start))
                 return;
        }
        current_tok = get_next_relevant_token();
    }
}

// Searches the array tokens (of size num); if a match is found, return true;
// else, return false. The strict flag dictates whether to match the aspect
// of the token, or just the attribute.
bool match(const Token* source, bool strict)
{
    if (tokens_equal(source, current_tok, strict))
    {
        should_print_synerr = true;
        current_tok = get_next_relevant_token();
        return true;
    }
    else
    {
        should_print_synerr = false;
        printf("Found '%s'; expected '%s' instead.\n", getLexFromToken(current_tok, strict),
                                    getLexFromToken(source, source -> start));
        throwError(SYNERR, 0, 0, 0);
        current_tok = get_next_relevant_token();
        return false;
    }
}

bool generateParseTree()
{
    current_tok = malloc(sizeof(*current_tok));
    current_tok = get_next_relevant_token();
    program();
    return match(&eof_tok, false);
}
