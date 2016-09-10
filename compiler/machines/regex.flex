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
enum TokenType {ASSIGNOP, RELOP, IDRES, LONGREAL, REAL, INT};

typedef struct T_Type {
    enum TokenType category;
    union {
        int type;
        int* location;
    };
} Token;


Token manageAssignOp(char* op) {
    printf("Found an ASSIGNOP! It's %s. ", yytext);

    Token* token = malloc(sizeof(*token));
    token -> category = ASSIGNOP;
    token -> type = 0;

    return *token;
}
%}

%%
{ASSIGNOP}  manageAssignOp(yytext);
{RELOP}     printf("Found a RELOP! It's %s. ", yytext);
{IDRES}     printf("Found an ID! It's %s. ", yytext);

{LONGREAL}  printf("Found a long real! It's %s. ", yytext);
{REAL}      printf("Found a real! It's %s. ", yytext);
{INT}       printf("Found an int! It's %s. ", yytext);

{UNREC}     printf("Symbol '%s' not recognized. ", yytext);
.           printf("");
%%





int run()
{
    printf("%s\n", "Beginning machine parsing...");
    extern FILE* yyin;
    yyin=fopen("fileYouWantOpen","r");
    yylex();

    return 0;
}

int main()
{
    return run();
}
