#include <stdio.h>
#include <stdlib.h>
#include "headers/parser.h"

extern FILE *yyin;
extern Token yylex();

int main(int argc, char **argv) {
  if(argc < 2) {
    puts("Falta archivo de entrada.");
    exit(1); 
  }
  printf("Archivo de entrada: ");
  puts(argv[1]);
  FILE *fin = fopen(argv[1], "r");
  yyin = fin;

  puts("Comenzando análisis...");
  Token tokenActual = yylex();
  //puts(tokenActual->valor); //verificación de lectura  
  Parser p = Parser();
  p.parse();
  return 0;
}