#ifndef PROCESSOR_H_
#define PROCESSOR_H_
#include<stdio.h>
#include "tokens.h"

Token* getNextToken();
int initializeTokens(FILE* resFile);

#endif // PROCESSOR_H_
