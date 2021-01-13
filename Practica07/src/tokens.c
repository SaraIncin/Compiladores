#include <stdio.h>
#include "tokens.h"

token *crea_token(int clase, char *valor) {  
  token *t_out = malloc(sizeof(token));
  t_out->clase = clase;
  t_out->valor = malloc(sizeof(valor));
  strcpy(t_out->valor, valor);
  return t_out;
  
}

token *crea_token_tipo(int clase, char *valor, int tipo) {
  token *t_out = malloc(sizeof(token));
  t_out->clase = clase;
  t_out->valor = malloc(sizeof(valor));
  strcpy(t_out->valor, valor);
  t_out->tipo = tipo;
  return t_out;
}

int equals(token *t1, int clase) {
  return t1->clase == clase;
}

