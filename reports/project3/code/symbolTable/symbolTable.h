#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

int initSymbolTable();
char* checkSymbolTable(char* name);
char* pushToSymbolTable(char* name, size_t length);

#endif // SYMBOL_TABLE_H
