#ifndef PARSER_H
#define PARSER_H
#include<stdbool.h>

int generateParseTree();
bool match(const Token* source, bool strict);
void require_sync(const Token* sync_set[], int size,
                  const Token* first_set[], int first_size);

#endif // PARSER_H
