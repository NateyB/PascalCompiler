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
static const char TOKEN_PATH[] = "out/tokens.dat"; // The constant token file path

FILE* tokenFile = NULL; // The token file pointer; opened at the beginning

// The valid token types in our subset of Pascal
enum TokenType {ASSIGNOP, RELOP, IDRES, LONGREAL, REAL, INT};
// The token data type (essentially a tuple :: (TokenType, int))
typedef struct T_Type {
    enum TokenType category;
    int type;
} Token;


Token* manageAssignOp(char* op)
{
    Token* token = malloc(sizeof(*token));
    token -> category = ASSIGNOP;
    token -> type = 0;

    return token;
}

void applyToken(Token* token)
{
    printf("Applying token.\n");
    fprintf(tokenFile, "%2d %2d", token -> category, token -> type);
}
%}

%%
{ASSIGNOP}  applyToken(manageAssignOp(yytext));
{RELOP}     printf("Found a RELOP! It's %s. ", yytext);
{IDRES}     printf("Found an ID! It's %s. ", yytext);

{LONGREAL}  printf("Found a long real! It's %s. ", yytext);
{REAL}      printf("Found a real! It's %s. ", yytext);
{INT}       printf("Found an int! It's %s. ", yytext);

{UNREC}     printf("Symbol '%s' not recognized. ", yytext);
.           printf("");
%%


// Returns 1 on success, 0 on failure.
int run()
{
    tokenFile = fopen(TOKEN_PATH, "w+");
    if (tokenFile == NULL) {
        printf("%s%s%s\n", "Could not create token file in ", TOKEN_PATH, " - aborting.");
        return 0;
    }

    printf("%s\n", "Beginning machine parsing...");
//    extern FILE* yyin;
//    yyin=fopen("fileYouWantOpen","r");
    yylex();

    return 1;
}

int main()
{
    return run();
}
