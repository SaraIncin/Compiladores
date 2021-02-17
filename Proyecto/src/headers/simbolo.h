#include <string>
#include <vector>

#include "tipo.h"
using namespace std;

#define VAR 2001
#define PARAM 2002
#define FUNCION 2003

struct Simbolo {
  string id;
  int dir;
  int tipo;
  int var;
  vector<int> args;

public:
  Simbolo(string id, int dir, int tipo, int var, vector<int> args){
    this-> id = id;
    this-> dir = dir;
    this-> tipo = tipo;
    this-> var = var;
    this-> args = args;    
  }
  Simbolo(string id, int dir, int tipo, int var){
    this-> id = id;
    this-> dir = dir;
    this-> tipo = tipo;
    this-> var = var;  
  }
 
};

struct TablaSimbolos {
  vector<Simbolo> tabla;

public:
  bool busca(string id);
  bool inserta(Simbolo s);
  int buscaDir(string id);
  int buscaTipo(string id);
  int buscaVar(string id);
  std::vector<int> buscaArgs(string id);
  void printTS(string contexto);
  bool listaCompatibles(vector<int> lista, int tipo);
};
