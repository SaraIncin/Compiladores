#include <ostream>
#include <string>
#include <vector>

using namespace std;

// Operadores para código intermedio
#define C_COPY "="
#define C_PLUS "+"
#define C_MINUS "-"
#define C_MUL "*"
#define C_DIV "/"
#define C_GOTO "goto"
#define C_IF "if"
#define C_IF_FALSE "ifFalse"
#define C_IF_GE "ifGe"
#define C_IF_GEQ "ifGeq"
#define C_IF_LE "ifLe"
#define C_IF_LEQ "ifLeq"
#define C_IF_EQ "ifEq"
#define C_IF_NEQ "ifNeq"
#define C_IDX_COPY "=[]"
#define C_IDX_ASSIG "[]="
#define C_PARAM "param"
#define C_CALL "call"
#define C_PTR_COPY "=&"
#define C_VAL_COPY "=*"
#define C_VAL_ASSIG "*="

struct Cuadrupla {
  string op;
  string t1;
  string t2;
  string res;

public:
  string to_string();
};

ostream &operator<<(ostream &out, const Cuadrupla &c);

struct Generador {
  vector<Cuadrupla> codigo;

public:
  Generador() { codigo = vector<Cuadrupla>(); }
  void generaCodigo(Cuadrupla c);
};

string nuevaEtiqueta();
