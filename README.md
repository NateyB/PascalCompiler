# PascalCompiler
The Pascal compiler for my CS 4013—Compiler Construction class. Specifically,
this compiler is the front-end of a compiler for a subset of the Psacal
language. It is written entirely in C.

The project is broken down into four phases (each of which will
be considered a release):

1. Lexical Analysis (tokenization)
2. Syntax Analysis (parse tree verification)
3. Semantic Analysis (parse tree decoration)
4. Offset Calculation

These four phases will be outlined below, as we cover them in the class. Each
phase will have a corresponding report, written in TeX, available in the
appropriate [release](https://github.com/NateyB/PascalCompiler/releases)
and in the reports directory of the project.

## Lexical Analysis
The lexical analysis phase of the project involves processing the source file
and converting each lexeme into the appropriate token. To achieve this aim, the
analyzer passes each lexeme through a series of machines that can identify
the corresponding token. The machines are Whitespace,
ID/Res, LongRealMachine, RealMachine, IntMachine, Grouping,
CatchAll, RELOP, ADDOP, and MULOP. Worth mentioning is that the ID/Res machine
will add variables to a symbol table to be used later.

## Syntax Analysis
The syntax analysis phase of the project involves processing the token stream
generated by the lexical analysis phase. The parser attempts to match the tokens
to the corresponding productions in our LL(1) grammar. The productions (as well
as the parse table, first, and follows sets) are available in the grammar
folder of the project and in the second
[release](https://github.com/NateyB/PascalCompiler/releases).

## Semantic Analysis & Offset Calculation
The semantic analysis phase of the project involves decorating the parse tree
generated by the syntax analysis phase. The decorations are designed to assign
meanings to the tokens. The semantic analysis performed includes type checking
and declarations processing (i.e., scope checking). The offset calculation
merely calculates the memory offsets of local variables in each scope. Some
fairly inadequate diagrams can be found in the third
[release](https://github.com/NateyB/PascalCompiler/releases).
