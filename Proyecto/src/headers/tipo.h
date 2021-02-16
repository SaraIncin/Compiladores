#include <string>
#include <vector>
#include "tokens.h"

using namespace std;

struct Tipo {
  int id;
  string nombre;
  int tam;
  int base;

public:
  Tipo(int id, string nombre, int tam, int base){
    this->id = id;
    this->nombre = nombre;
    this->tam = tam;
    this->base = base;
  }
};

struct TablaTipos {
  vector<Tipo> tabla;

public:
  bool busca(int id);
  bool inserta(Tipo t);
  string buscaNombre(int id);
  int buscaTam(int id);
  int buscaBase(int id);
  int nuevoID();
  void printTT(string contexto);
  void iniciaTTPrimitivos();
};

int maximo(int tipo1, int tipo2);
bool equivalentes(int tipo1, int tipo2);