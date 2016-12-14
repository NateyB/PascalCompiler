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

// Attempts to match the source token with the current token;
// if it is found, it returns the previous token (for use in the RDP).
// If it is not found, then match returns null
Token* match(const Token* source, bool strict)
{
    if (tokens_equal(source, current_tok, strict))
    {
        Token* prev_tok = current_tok;
        should_print_synerr = true;
        current_tok = get_next_relevant_token();
        return prev_tok;
    }
    else
    {
        should_print_synerr = false;
        throw_syn_error(current_tok, &source, 1);
        current_tok = get_next_relevant_token();
        return NULL;
    }
}

bool generateParseTree()
{
    current_tok = malloc(sizeof(*current_tok));
    current_tok = get_next_relevant_token();
    program();
    return match(&eof_tok, false);
}
