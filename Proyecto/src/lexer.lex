%{
#include "headers/tokens.h"
#include <stdio.h>
#define YY_DECL Token yylex(void)
%}

%option noyywrap
%option yylineno

num_ent [0-9]+
num_float [0-9]*"."[0-9]+
id [a-zA-Z][a-zA-Z0-9]*
whitespace [ \t\n]


char \'[^']\'
cadena \"(\\.|[^"\\])*\"

%%

"," {
  
  return Token(COMA, "");
}
";" {
  
  return Token(PCOMA, "");
}

":" {
  
  return Token(DOSP, "");
}
"(" {
  
  return Token(PIZQ, "");
}
")" {
  
  return Token(PDER, "");
}
"{" {
  
  return Token(KIZQ, "");
}
"}" {
  
  return Token(KDER, "");
}

"[" {
  
  return Token(CIZQ, "");
}
"]" {
  
  return Token(CDER, "");
}

"==" {
  
  return Token(EQ, "");
}
"!=" {
  
  return Token(NEQ, "");
}
"<" {
  
  return Token(LESS, "");
}
">" {
  
  return Token(GRE, "");
}
"<=" {
  
  return Token(LEQ, "");
}
">=" {
  
  return Token(GEQ, "");
}
"=" {
  
  return Token(ASSIG, "");
}
"+" {
  
  return Token(SUM, "");
}
"-" {
  
  return Token(SUB, "");
}
"*" {
  
  return Token(MUL, "");
}
"/" {
  
  return Token(DIV, "");
}
"%" {
  
  return Token(RES, "");
}
"!" {
  
  return Token(NEG, "");
}
"&&" {
  
  return Token(AND, "");
}
"||" {
  
  return Token(OR, "");
}

"int" {
  
  return Token(INT, "");
}
"float" {
  
  return Token(FLOAT, "");
}

"char" {
  
  return Token(CHAR, "", 0);
}
"cadena" {
  
  return Token(STRING, "", 0);
}
"double" {
  
  return Token(DOUBLE, "");
}
"void" {
  
  return Token(VOID, "");
}
"true" {
  
  return Token(TRUE, "");
}
"false" {
  
  return Token(FALSE, "");
}

"func" {
  
  return Token(FUNC, "");
}
"if" {
  
  return Token(IF, "");
}
"else" {
  
  return Token(ELSE, "");
}
"while" {
  
  return Token(WHILE, "");
}
"do" {
  
  return Token(DO, "");
}
"break" {
  
  return Token(BREAK, "");
}
"switch" {
  
  return Token(SWITCH, "");
}
"case" {
  
  return Token(CASE, "");
}
"default" {
  
  return Token(DEFAULT, "");
}

{num_ent} {
  
  return Token(NUM, yytext, INT);
}
{num_float} {
  
  return Token(NUM, yytext, FLOAT);
}

{char} {
  
  return Token(CHAR, yytext);
}
{cadena} {
  
  return Token(STRING, yytext);
}

{id} {
  
  return Token(ID, yytext);
}
{whitespace} {  }
<<EOF>> {
  puts("Fin de análisis léxico.");
  return Token(FIN, "");
}
. {
  printf("Error léxico en la linea: %i\n", yylineno);
  exit(1);
}

%%
