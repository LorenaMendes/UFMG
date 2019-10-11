%{
    #include "scanner.h"
%}

%%
";"                                                     return SEMICOLON;
":"                                                     return COLON;
","                                                     return COMMA;
"("                                                     return OPEN_PARENTHESIS;
")"                                                     return CLOSE_PARENTHESIS;
":="                                                    return ASSIGNMENT;
"if"                                                    return IF;
"then"                                                  return THEN;
"else"                                                  return ELSE;
"do"                                                    return DO;
"while"                                                 return WHILE;
"until"                                                 return UNTIL;
"begin"                                                 return MYBEGIN;
"end"                                                   return END;
"read"                                                  return READ;
"write"                                                 return WRITE;
"program"                                               return PROGRAM;
[true|false]                                            return BOOLEAN_CONSTANT;
[=|>|<|>=|<=|!=|NOT]                                    return RELOP;
[+|-|or]                                                return ADDOP;
[*|/|div|mod|and]                                       return MULOP;
"-"                                                     return SCORE;
['][ -~][']                                             return CHAR_CONSTANT;
[0-9][0-9]*                                             return UNSIGNED_INTEGER;
[0-9][0-9]*[^$|[.][0-9]*][^$|[E][+-^$][0-9][0-9]*]      return UNSIGNED_REAL;
[a-zA-Z_][a-zA-Z0-9_]*                                  return IDENTIFIER;
[ \t\n]                                                 ;
.                                                       printf("unexpected character\n");
%%

int yywrap(void) {
    return 1;
}