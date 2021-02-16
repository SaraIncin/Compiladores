#include <stack>
#include <string>
#include <vector>

#include "simbolo.h"
#include "codigo.h"


using namespace std;

struct Compuesto
{
  int tipo;
  int base;
public:
  Compuesto(int tipo, int base){
    this->tipo = tipo;
    this->base = base;
  }
  Compuesto(int base){
    this->base = base;
  }
};

struct ListaArg
{
  vector<int> listaH;
  vector<int> listaS;

public:
  ListaArg(vector<int> listaH){
    this->listaH = listaH;
  }
};

struct SentenciaP
{
  string sig;
  vector<string> indices;
public: 
  SentenciaP(string sig, vector<string> indices){
    this->sig = sig;
    this->indices = indices;
  }
};

struct BoolC
{
  string vddr;
  string fls;
public: 
  BoolC(string vddr, string fls){
    this->vddr = vddr;
    this->fls = fls;
  }
};



struct Parser {
  stack<TablaSimbolos> pts;
  TablaSimbolos ts;
  stack<TablaTipos> ptt;
  TablaTipos tt;
  stack<int> pDir;
  int dir;
  vector<string> tc;
  vector<int> listaRetorno;

public:
  Parser();
  void parse();

private:
  void error(string msg);
  string amplia(string dir, int t1, int t2);
  string reduce(string dir, int t1, int t2);
  string nuevaTemporal();
  void P();
  void D();
  int TI();
  void LV(int tipo);
  void LVP(int tipo);
  int B();
  Compuesto C(Compuesto b);
  void F();
  vector<int> A();
  void BL();
  vector<int> LA();
  ListaArg LAP(ListaArg nArgs);
  void I();
  void IP();
  void S(string sig);
  void SP(SentenciaP indices);
  void Bo(BoolC bo);
  void RV();
  string E();
  
};



