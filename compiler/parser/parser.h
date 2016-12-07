#ifndef PARSER_H
#define PARSER_H
#include<stdbool.h>

int generateParseTree();
bool match(int cat, int aspect, bool strict);
void requireSync(const Token* syncSet[], int size);

#endif // PARSER_H
