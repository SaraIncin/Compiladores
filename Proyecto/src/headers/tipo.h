#include <string>
#include <vector>

using namespace std;

struct Tipo {
  int id;
  string nombre;
  int tam;
  int base;

public:
  int maximo(int tipo1, int tipo2);
  bool equivalentes(int tipo1, int tipo2);
};

struct TablaTipos {
  vector<Tipo> tabla;

public:
  bool busca(int id);
  bool inserta(Tipo t);
  string buscaNombre(int id);
  int buscaTam(int id);
  int buscaBase(int id);
};
