%{
  #include <stdio.h>
  #include "tokens.h"
  #define YY_DECL token *yylex(void)
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

"," { ECHO; return crea_token(COMA, ""); }
";" { ECHO; return crea_token(PCOMA, ""); }


":" { ECHO; return crea_token(DOSP, ""); }
"(" { ECHO; return crea_token(PIZQ, ""); }
")" { ECHO; return crea_token(PDER, ""); }
"{" { ECHO; return crea_token(KIZQ, ""); }
"}" { ECHO; return crea_token(KDER, ""); }

	       
"[" { ECHO; return crea_token(CIZQ, ""); }
"]" { ECHO; return crea_token(CDER, ""); }

	       
"==" { ECHO; return crea_token(EQ, ""); }
"!=" { ECHO; return crea_token(NEQ, ""); }
"<" { ECHO; return crea_token(LESS, ""); }
">" { ECHO; return crea_token(GRE, ""); }
"<=" { ECHO; return crea_token(LEQ, ""); }
">=" { ECHO; return crea_token(GEQ, ""); }
"=" { ECHO; return crea_token(ASSIG, ""); }
"+" { ECHO; return crea_token(SUM, ""); }
"-" { ECHO; return crea_token(SUB, ""); }
"*" { ECHO; return crea_token(MUL, ""); }
"/" { ECHO; return crea_token(DIV, ""); }
"%" { ECHO; return crea_token(RES, ""); }
"!" { ECHO; return crea_token(NEG, ""); }
"&&" { ECHO; return crea_token(AND, ""); }
"||" { ECHO; return crea_token(OR, ""); }

	       
"int" { ECHO; return crea_token(INT, ""); }
"float" { ECHO; return crea_token(FLOAT, ""); }

	       
"char" { ECHO; return crea_token_tipo(CHAR, "", 0); }
"cadena" { ECHO; return crea_token_tipo(STRING, "", 0); }
"double" { ECHO; return crea_token(DOUBLE, ""); }
"void" { ECHO; return crea_token(VOID, ""); }
"true" { ECHO; return crea_token(TRUE, ""); }
"false" { ECHO; return crea_token(FALSE, ""); }

"func" { ECHO; return crea_token(FUNC, ""); }
"if" { ECHO; return crea_token(IF, ""); }
"else" { ECHO; return crea_token(ELSE, ""); }
"while" { ECHO; return crea_token(WHILE, ""); }
"do" { ECHO; return crea_token(DO, ""); }
"break" { ECHO; return crea_token(BREAK, ""); }
"switch" { ECHO; return crea_token(SWITCH, ""); }
"case" { ECHO; return crea_token(CASE, ""); }
"default" { ECHO; return  crea_token(DEFAULT, ""); }


{num_ent} { ECHO; return crea_token_tipo(NUM, yytext, 0); }
{num_float} { ECHO; return crea_token_tipo(NUM, yytext, 1); }

	       
{char} { ECHO; return crea_token_tipo(CHAR, yytext, 1); } 
{cadena} { ECHO; return crea_token_tipo(STRING, yytext, 1); }

	       
{id} { ECHO; return crea_token(ID, yytext); }
{whitespace} { ECHO; }
<<EOF>> { puts("Fin de análisis léxico."); return crea_token(FIN, "");}
. { printf("Error léxico en la linea: %i\n", yylineno); exit(1); }

%%


