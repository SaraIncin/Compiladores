#include <string>
#include <vector>

using namespace std;

struct Cuadrupla {
  string op;
  string t1;
  string t2;
  string res;
};

struct Generador {
  vector<Cuadrupla> codigo;

public:
  Generador() { codigo = vector<Cuadrupla>(); }
  void generaCodigo(Cuadrupla c);
};

string nuevaEtiqueta();
