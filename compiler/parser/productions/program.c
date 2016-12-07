#include<stdbool.h>
#include<stdlib.h>

#include "productions.h"
#include "../parser.h"
#include "../../tokenizer/tokens.h"

const Token endOfFile = {
    FILEEND, false, 0, 0
};

static const Token* syncSet[] = {&endOfFile};
static const int sync_size = sizeof(syncSet)/sizeof(syncSet[0]);

static void synch()
{
    requireSync(syncSet, sync_size);
}

// Needs implementing: None
void program()
{
    // Production 1
    if (curTok -> category == CONTROL && curTok -> type == 7)
        if (match(CONTROL, 7, true)) // program
            if (match(ID, 0, false))
                if (match(GROUP, 0, true)) // (
                {
                    id_list();
                    if (match(GROUP, 1, true)) // )
                        if (match(PUNC, 1, true)) // ;
                        {
                            declarations();
                            subprogram_declarations();
                            compound_statement();
                            if (match(PUNC, 2, true)) // .
                                return;
                        }
                }

    synch();
}
