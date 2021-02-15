#include <string>
#include <vector>

using namespace std;

struct Cuadrupla {
  string op;
  string t1;
  string t2;
  string res;
  
  Cuadrupla(string op, string t1, string t2, string res){
    this->op = op;
    this->t1 = t1;
    this->t2 = t2;
    this->res = res;
  }
};

struct Generador {
  vector<Cuadrupla> codigo;

public:
  Generador() { codigo = vector<Cuadrupla>(); }
  void generaCodigo(Cuadrupla c);
};

string nuevaEtiqueta();
