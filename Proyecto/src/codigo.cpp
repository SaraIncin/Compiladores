#include "headers/codigo.h"
#include <ostream>
#include <sstream>

// Macros para generar código intermedio
#define build_copy(x, y) x + "=" + y
#define build_assig(op, x, y, z) x + "=" + y + op + z
#define build_goto(l) "goto " + l
#define build_if(x, l) "if " + x + " goto " + l
#define build_if_false(x, l) "ifFalse" + x + " goto " + l
#define build_if_rel(r, x, y, l) "if " + x + r + y + " goto " + l
#define build_if_false_rel(r, x, y, l) "ifFalse " + x + r + y + " goto " + l
#define build_idx_copy(x, y, i) x + "=" + y + "[" + i + "]"
#define build_idx_assig(x, y, i) x + "[" + i + "]" + "=" + y
#define build_param(x) "param " + x
#define build_call(f, n) "call " + f + ", " + n
#define build_ptr_copy(x, y) x + " = " + "&" + y
#define build_val_copy(x, y) x + " = " + "*" + y
#define build_val_assig(x, y) x + "*" + " = " + y

using namespace std;

ostream &operator<<(ostream &out, const Cuadrupla &c) {
  out << c.op << " with ";
  out << c.t1;
  if (c.t2 != "")
    out << " and " << c.t2;
  if (c.res != "")
    out << " at " << c.res;
  out << endl;
  return out;
}

string Cuadrupla::to_string() {
  ostringstream s;
  s << this;
  return s.str();
}

void Generador::generaCodigo(Cuadrupla c) { this->codigo.push_back(c); }

string nuevaEtiqueta() {
  static int numTemp = 0;
  numTemp++;
  return "t" + to_string(numTemp);
}
