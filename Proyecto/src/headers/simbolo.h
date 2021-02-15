#include <string>
#include <vector>
using namespace std;

#define VAR 2001
#define PARAM 2002
#define FUNC 2003

struct Simbolo {
  string id;
  int dir;
  int tipo;
  int var;
  vector<int> args;
};

struct TablaSimbolos {
  vector<Simbolo> tabla;

public:
  bool busca(string id);
  bool inserta(Simbolo s);
  string buscaDir(string id);
  int buscaTipo(string id);
};

Simbolo nuevaTemporal();