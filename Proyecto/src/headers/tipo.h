#include <string>
#include <vector>

using namespace std;

struct Tipo {
  int id;
  string nombre;
  int tam;
  Tipo base;

public:
  bool operator<(Tipo t1, Tipo t2);
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
