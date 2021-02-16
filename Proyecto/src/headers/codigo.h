#include <ostream>
#include <string>
#include <vector>

using namespace std;

// Operadores para código intermedio
#define C_COPY 3000
#define C_PLUS 3001
#define C_MINUS 3002
#define C_MUL 3003
#define C_DIV 3004
#define C_GOTO 3005
#define C_IF 3006
#define C_IF_FALSE 3007
#define C_IF_GE 3008
#define C_IF_GEQ 3009
#define C_IF_LE 3010
#define C_IF_LEQ 3011
#define C_IF_EQ 3012
#define C_IF_NEQ 3013
#define C_IDX_COPY 3014
#define C_IDX_ASSIG 3015
#define C_PARAM 3016
#define C_CALL 3017
#define C_PTR_COPY 3018
#define C_VAL_COPY 3019
#define C_VAL_ASSIG 3020
#define C_LABEL 3021
#define C_PRINT 3022
#define C_SCAN 3023

struct Cuadrupla {
  int op;
  string t1;
  string t2;
  string res;

  Cuadrupla(int op, string t1, string t2, string res) {
    this->op = op;
    this->t1 = t1;
    this->t2 = t2;
    this->res = res;
  }

public:
  string to_string();
};

ostream &operator<<(ostream &out, const Cuadrupla &c);

struct Generador {
  vector<Cuadrupla> codigo;

public:
  Generador() { codigo = vector<Cuadrupla>(); }
  void generaCodigo(Cuadrupla c);
  string escribeCodigo();
};

string nuevaEtiqueta();
