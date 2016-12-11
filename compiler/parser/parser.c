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
        next = &eof_tok;
    }

    return next;
}

void require_sync(const Token* sync_set[], int size,
                  const Token* first_set[], int first_size)
{
    if (should_print_synerr)
        throw_syn_error(current_tok, first_set, first_size);

    while (true) {
        for (int i = 0; i < size; i++)
            if (tokens_equal(sync_set[i], current_tok, sync_set[i] -> start))
                 return;

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
        throw_syn_error(current_tok, &source, 1);
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
