#include "headers/codigo.h"
#include <iostream>
#include <ostream>
#include <sstream>
#include <algorithm>

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
#define build_label(l) l + ":"
#define build_syscall(call, x) call + " " + x

using namespace std;

ostream &operator<<(ostream &out, const Cuadrupla &c) {
  string s = "";
  string op = "";
  switch (c.op) {
  case C_COPY:
    s = build_copy(c.t1, c.res);
    break;
  case C_PLUS:
    op = "+";
    s = build_assig(op, c.res, c.t1, c.t2);
    break;
  case C_MINUS:
    op = "-";
    s = build_assig(op, c.res, c.t1, c.t2);
    break;
  case C_MUL:
    op = "*";
    s = build_assig(op, c.res, c.t1, c.t2);
    break;
  case C_DIV:
    op = "/";
    s = build_assig(op, c.res, c.t1, c.t2);
    break;
  case C_GOTO:
    s = build_goto(c.res);
    break;
  case C_IF:
    s = build_if(c.t1, c.res);
    break;
  case C_IF_FALSE:
    s = build_if_false(c.t1, c.res);
    break;
  case C_IF_GE:
    op = ">";
    s = build_if_rel(op, c.t1, c.t2, c.res);
    break;
  case C_IF_GEQ:
    op = ">=";
    s = build_if_rel(op, c.t1, c.t2, c.res);
    break;
  case C_IF_LE:
    op = "<";
    s = build_if_rel(op, c.t1, c.t2, c.res);
    break;
  case C_IF_LEQ:
    op = "<=";
    s = build_if_rel(op, c.t1, c.t2, c.res);
    break;
  case C_IF_EQ:
    op = "==";
    s = build_if_rel(op, c.t1, c.t2, c.res);
    break;
  case C_IF_NEQ:
    op = "!=";
    s = build_if_rel(op, c.t1, c.t2, c.res);
    break;
  case C_IDX_COPY:
    s = build_idx_copy(c.res, c.t1, c.t2);
    break;
  case C_IDX_ASSIG:
    s = build_idx_assig(c.res, c.t1, c.t2);
    break;
  case C_PARAM:
    s = build_param(c.t1);
    break;
  case C_CALL:
    s = build_call(c.t1, c.t2);
    break;
  case C_PTR_COPY:
    s = build_ptr_copy(c.res, c.t1);
    break;
  case C_VAL_COPY:
    s = build_val_copy(c.res, c.t1);
    break;
  case C_VAL_ASSIG:
    s = build_val_assig(c.res, c.t1);
    break;
  case C_LABEL:
    s = build_label(c.t1);
    break;
  case C_PRINT:
    op = "print";
    s = build_syscall(op, c.t1);
    break;
  case C_SCAN:
    op = "scan";
    s = build_syscall(op, c.t1);
    break;
  case C_RETURN:
    op = "return";
    s = build_syscall(op, c.t1);
  }
  out << s << endl;
  return out;
}

string Cuadrupla::to_string() {
  ostringstream s;
  s << this;
  return s.str();
}

void Generador::generaCodigo(Cuadrupla c) { this->codigo.push_back(c); }

void Generador::agregaCodigo(vector<Cuadrupla> cs) {
  this->codigo.insert(this->codigo.end(), cs.begin(), cs.end());
}

string nuevaEtiqueta() {
  static int numTemp = 0;
  numTemp++;
  return "t" + to_string(numTemp);
}

string nuevoIndice() {
  static int numTemp = 0;
  numTemp++;
  return "i" + to_string(numTemp);
}

void Generador::reemplazarIndices(string etq, vector<string> listaEtq){
  for(auto & c : this->codigo){
    if(c.op == C_LABEL){
      auto it = find(listaEtq.begin(), listaEtq.end(), c.res);
      if(listaEtq.end() != it){
        c.res = etq;
      }
    }
  }
}

string Generador::escribeCodigo(){
  string c = "";   
  for(auto & inst : this->codigo){
    cout << inst;
  }
  return c;
}
