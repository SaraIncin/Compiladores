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
  FILE *out = fopen("salida.ci", "w");
  yyin = fin;
  
  puts("Comenzando análisis...");
  
  //puts(tokenActual.valor.c_str()); //verificación de lectura  
  Parser p = Parser(out);
  p.parse();
  return 0;
}