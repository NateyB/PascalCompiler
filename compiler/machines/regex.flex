/*
 * Description: The machines that I will need to use to recognize symbols in
 * my lexical analyzer.
 */


digit		[0-9]
letter		[a-zA-Z]
whitespace  [\n \t]
RELOP       (<(=|>)?)|=|>=?
ASSIGNOP    :=
IDRES       {letter}({letter}|{digit})*
WS          {whitespace}+
LONGREAL    {digit}+\.{digit}+\E(\+|\-)?{digit}+
REAL        {digit}+\.{digit}+
INT         {digit}+
UNREC       [^\n \t]

%{
// The constant file paths.
static const char TOKEN_PATH[] = "out/tokens.dat";
static const char RESWORD_PATH[] = "compiler/reswords.dat";

// The token file pointer; opened at initialization
FILE* tokenFile = NULL;
char ** reservedWords;

// The valid token types in our subset of Pascal
enum TokenType {ASSIGNOP, RELOP, IDRES, LONGREAL, REAL, INT, UNREC};
// The token data type (essentially a tuple :: (TokenType, int))
typedef struct T_Type {
    enum TokenType category;
    int type;
} Token;

// Creates and writes the token to file.
void applyToken(int cat, int kind)
{
    Token* token = malloc(sizeof(*token));
    token -> category = cat;
    token -> type = kind;

    fprintf(tokenFile, "%2d %2d\n", token -> category, token -> type);
}

// ASSIGNOP management
void manageAssignOp(char* op)
{
    applyToken(ASSIGNOP, 0);
}

// RELOP management
void manageRelOp(char* op)
{
    int kind;
    // Alternatively, I can use a switch statement based on the sum of the chars
    if (strcmp(op, "<>") == 0)
        kind = 0;
    else if (strcmp(op, "<") == 0)
        kind = 1;
    else if (strcmp(op, "<=") == 0)
        kind = 2;
    else if (strcmp(op, "=") == 0)
        kind = 3;
    else if (strcmp(op, ">=") == 0)
        kind = 4;
    else if (strcmp(op, ">") == 0)
        kind = 5;

    applyToken(RELOP, kind);
}

//IDRES management
void manageIdRes(char* symbol)
{
    // TODO Implement
    // Check reserve word table first; then,
    // check the symbol table. If it isn't there,
    // add it and create a new symbol.
}



%}

%%
{ASSIGNOP}  manageAssignOp(yytext);
{RELOP}     manageRelOp(yytext);
{IDRES}     printf("Found an ID! It's %s. ", yytext);

{LONGREAL}  printf("Found a long real! It's %s. ", yytext);
{REAL}      printf("Found a real! It's %s. ", yytext);
{INT}       printf("Found an int! It's %s. ", yytext);

{UNREC}     printf("Symbol '%s' not recognized. ", yytext);
.           printf("");
%%


// Returns 0 on success, 1 on failure.
int run()
{
//    extern FILE* yyin;
//    yyin=fopen("fileYouWantOpen","r");
    yylex();

    return 0;
}

int initResWords(FILE* resFile)
{
    int numWords = 0;
    int ln = 0;
    fscanf(resFile, "%d", &numWords);

    reservedWords = malloc(numWords * sizeof(char*));
    if (reservedWords == NULL)
    {
        fprintf(stderr, "%s\n", "Out of memory exception initializing reserve words! Aborting.");
        return 1;
    }
    for (ln = 0; ln < numWords; ln++)
    {
        reservedWords[ln] = malloc(10*sizeof(char));
        if (reservedWords[ln] == NULL)
        {
            fprintf(stderr, "%s\n", "Error allocating memory initializing reserve words! Aborting.");
            return 1;
        }
    }
    if (ln != numWords)
    {
        fprintf(stderr, "%s\n", "Could not allocate memory initializing reserve words! Aborting.");
        return 1;
    }

    ln = 0;
    while (!feof(resFile))
    {
        fscanf(resFile, "%10s", reservedWords[ln++]);
    }


    return 0;

}

// Returns 0 on success, 1 on failure
int init()
{
    tokenFile = fopen(TOKEN_PATH, "w+");
    if (tokenFile == NULL) {
        fprintf(stderr, "%s%s%s\n", "Could not create token file at ", TOKEN_PATH, " - aborting.");
        return 1;
    }

    FILE* resFile = fopen(RESWORD_PATH, "r");
    if (resFile == NULL) {
        fprintf(stderr, "%s%s%s\n", "Could not locate reserved word file at ", RESWORD_PATH, " - aborting.");
        return 1;
    }
    initResWords(resFile);
    fclose(resFile);

    printf("%s\n", "Beginning machine parsing...");
    return 0;
}

int deinit()
{
    fclose(tokenFile);
    for (int i = 0; i < sizeof(reservedWords); i++) // TODO verify that sizeof behaves this way
    {
        free(reservedWords[i]);
    }

    free(reservedWords);

    return 0;
}

int main()
{
    if (init() == 0)
    {
        run();
        deinit();
    } else {
        fprintf(stderr, "%s\n", "Initialization process failed in machine processor..");
        return 1;
    }

    return 0;
}
