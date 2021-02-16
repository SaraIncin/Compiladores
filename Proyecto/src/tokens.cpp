#include "headers/tokens.h"
#include <stdio.h>

Token::Token(int clase, string valor) {
  this->clase = clase;
  this->valor = valor;
}

Token::Token(int clase, string valor, int tipo) {
  this->clase = clase;
  this->valor = valor;
  this->tipo = tipo;
}

bool Token::equals(int clase) { 
  if(this->clase != clase){
    return this->tipo == clase;
  }
  return this->clase == clase; 
}
