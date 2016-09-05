alias crun="gcc compiler/lexicalanalyzer.c && ./a.out; rm a.out 2> /dev/null"
alias lexrun="cd compiler/machines && flex --noyywrap regex.lex && gcc lex.yy.c && ./a.out; cd ../.."
