%{
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
int yylex();
void yyerror (char const *s){fprintf (stderr, "%s\n", s);}
%}

/*
 *  yacc definitions
*/

/*
 *  CODE HERE
*/

%%
/*
 *  expected inputs
*/

program : "PROGRAM" identifier SEMICOLON decl_list compound_stmt {printf("PROGRAM identifier ';' decl_list compound_stmt");}

decl_list : decl_list ' ' SEMICOLON decl {printf("decl_list ';' decl");}
          | decl {printf("decl");}
          ;

decl : ident_list ';' type
      ;

ident_list : ident_list SEMICOLON identifier {printf("ident_list ';' identifier");}
           | identifier {printf("identifier");}
           ;

type : "integer" {printf("'integer'");}
     | "real" {printf("'real'");}
     | "booleanr" {printf("'booleanr'");}
     | "char" {printf("'char'");}
     ;

compound_stmt : "begin" stmt_list "end" {printf("'begin' stmt_list 'end'");}
              ;

stmt_list : stmt_list SEMICOLON stmt {printf("stmt_list ';' stmt");}
          | stmt {printf("stmt");}
          ;

stmt : assign_stmt {printf("assign_stmt");}
     | if_stmt {printf("if_stmt");}
     | loop_stmt {printf("loop_stmt");}
     | read_stmt {printf("read_stmt");}
     | write_stmt {printf("write_stmt");}
     | compound_stmt {printf("compound_stmt");}
     ;

assign_stmt : identifier " :=" expr {printf("identifier ':=' expr");}
            ;

if_stmt : "if" cond "then" stmt {printf("'if' cond 'then' stmt");}
        | "else" stmt {printf("'else'");}
        ;

cond : expr {;}
     ;

loop_stmt : stmt_prefix "do" stmt_list stmt_sufix {printf("stmt_prefix 'do' stmt_list stmt_sufix");}
          ;

stmt_prefix : "while" cond {printf("'while' cond");}
            ;

stmt_sufix : "until" cond {printf("'until' cond");}
           | "end"
           ;

read_stmt : "read" '(' ident_list ')' {printf("'read' '(' ident_list ')'");}
          ;

write_stmt : "write" '(' expr_list ')' {printf("'write' '(' expr_list ')'");}
           ;

expr_list : expr {printf("expr");}
          | expr_list " ," expr {printf("'expr_list ' ,' expr'");}
          ;

expr : simple_expr {printf("simple_expr");}
      | simple_expr RELOP simple_expr {printf("simple_expr RELOP simple_expr");}
      ;

simple_expr : term {printf("term");}
            | simple_expr ADDOP term {printf("simple_expr ADDOP simple_expr");} 
            ;

term : factor_a {printf("factor_a");}
     | term MULOP factor_a {printf("term MULOP factor_a");}
     ;

factor_a : '-' factor {printf("'-' factor");}
         | factor {printf("factor");}
         ;

factor : identifier {printf("identifier");}
       | constant {printf("constant");}
       | " (" expr " )" {printf("' (' expr ' )'");}
       | "NOT" factor {printf("NOT factor");}
       ;

constant : integer_constant {printf("integer_constant");}
         | real_constant {printf("real_constant");}
         | char_constant {printf("char_constant");}
         | boolean_constant {printf("boolean_constant");}
         ;

boolean_constant : "false" {printf("'false");}
                 | "true" {printf("'true");}
                 ;

integer_constant : "unsigned_integer";
real_constant : "unsigned_real";
char_constant : "caractereASCII"
identifier : "identifier";

RELOP : '='
      | '<'
      | "<="
      | '>'
      | ">="
      | "!="
      | "NOT"
      ;

ADDOP : '+'
      | '-'
      | "or"
      ;

MULOP : '*'
      | '/'
      | "div"
      | "mod"
      | "and"
      ;

SEMICOLON: ';'
      ;

%%
