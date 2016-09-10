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

// Returns 0 on success, 1 on failure
int init()
{
    tokenFile = fopen(TOKEN_PATH, "w+");
    if (tokenFile == NULL) {
        fprintf(stderr, "%s%s%s\n", "Could not create token file in ", TOKEN_PATH, " - aborting.");
        return 1;
    }

    printf("%s\n", "Beginning machine parsing...");
    return 0;
}

int main()
{
    if (init() == 0)
    {
        return run();
    } else {
        fprintf(stderr, "%s\n", "Initialization process failed in machine processor..");
    }
}
