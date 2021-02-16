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
  ECHO;
  return Token(COMA, "");
}
";" {
  ECHO;
  return Token(PCOMA, "");
}

":" {
  ECHO;
  return Token(DOSP, "");
}
"(" {
  ECHO;
  return Token(PIZQ, "");
}
")" {
  ECHO;
  return Token(PDER, "");
}
"{" {
  ECHO;
  return Token(KIZQ, "");
}
"}" {
  ECHO;
  return Token(KDER, "");
}

"[" {
  ECHO;
  return Token(CIZQ, "");
}
"]" {
  ECHO;
  return Token(CDER, "");
}

"==" {
  ECHO;
  return Token(EQ, "");
}
"!=" {
  ECHO;
  return Token(NEQ, "");
}
"<" {
  ECHO;
  return Token(LESS, "");
}
">" {
  ECHO;
  return Token(GRE, "");
}
"<=" {
  ECHO;
  return Token(LEQ, "");
}
">=" {
  ECHO;
  return Token(GEQ, "");
}
"=" {
  ECHO;
  return Token(ASSIG, "");
}
"+" {
  ECHO;
  return Token(SUM, "");
}
"-" {
  ECHO;
  return Token(SUB, "");
}
"*" {
  ECHO;
  return Token(MUL, "");
}
"/" {
  ECHO;
  return Token(DIV, "");
}
"%" {
  ECHO;
  return Token(RES, "");
}
"!" {
  ECHO;
  return Token(NEG, "");
}
"&&" {
  ECHO;
  return Token(AND, "");
}
"||" {
  ECHO;
  return Token(OR, "");
}

"int" {
  ECHO;
  return Token(INT, "");
}
"float" {
  ECHO;
  return Token(FLOAT, "");
}

"char" {
  ECHO;
  return Token(CHAR, "", 0);
}
"cadena" {
  ECHO;
  return Token(STRING, "", 0);
}
"double" {
  ECHO;
  return Token(DOUBLE, "");
}
"void" {
  ECHO;
  return Token(VOID, "");
}
"true" {
  ECHO;
  return Token(TRUE, "");
}
"false" {
  ECHO;
  return Token(FALSE, "");
}

"func" {
  ECHO;
  return Token(FUNC, "");
}
"if" {
  ECHO;
  return Token(IF, "");
}
"else" {
  ECHO;
  return Token(ELSE, "");
}
"while" {
  ECHO;
  return Token(WHILE, "");
}
"do" {
  ECHO;
  return Token(DO, "");
}
"break" {
  ECHO;
  return Token(BREAK, "");
}
"switch" {
  ECHO;
  return Token(SWITCH, "");
}
"case" {
  ECHO;
  return Token(CASE, "");
}
"default" {
  ECHO;
  return Token(DEFAULT, "");
}

{num_ent} {
  ECHO;
  return Token(NUM, yytext, 0);
}
{num_float} {
  ECHO;
  return Token(NUM, yytext, 1);
}

{char} {
  ECHO;
  return Token(CHAR, yytext, 1);
}
{cadena} {
  ECHO;
  return Token(STRING, yytext, 1);
}

{id} {
  ECHO;
  return Token(ID, yytext);
}
{whitespace} { ECHO; }
<<EOF>> {
  puts("Fin de análisis léxico.");
  return Token(FIN, "");
}
. {
  printf("Error léxico en la linea: %i\n", yylineno);
  exit(1);
}

%%
