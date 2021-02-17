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
    this->tipo = -1;
  }
};

struct ListaArg
{
  vector<int> listaH;
  vector<int> listaS;

public:
  ListaArg(vector<int> listaH){
    this->listaH = listaH;
    this->listaS = vector<int>();
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
  int tipo;
  string dir;
public: 
  BoolC(string vddr, string fls){
    this->vddr = vddr;
    this->fls = fls;
  }
  BoolC(){
    this->vddr = "";
    this->fls = "";
    this->dir = "";
    this->tipo = -1;
  }
};

struct BoolCP
{
  string vddr;
  string fls;
  int tipoH;
  int tipoS;
  vector<string> indices;
public:
  BoolCP(int tipoH, vector<string> indices){
    this->vddr = "";
    this->fls = "";
    this->tipoH=tipoH;
    this->tipoS=-1;
    this->indices=indices;
  }
  BoolCP(string vddr, string fls, int tipoH, vector<string> indices){
    this->vddr=vddr;
    this->fls=fls;
    this->tipoH=tipoH;
    this->tipoS=-1;
    this->indices=indices;
  }
};


struct ParteIzq
{
  int tipo;
  string dir;
public:
  ParteIzq(int tipo, string dir){
    this->tipo = tipo;
    this->dir = dir;
  }
};

struct Casos
{
  string sig;
  string id;
  string etqPrueba;
  vector<Cuadrupla> prueba;
public:
  Casos(string sig, string id, string etqPrueba){
    this->sig = sig;
    this->id = id;
    this->etqPrueba = etqPrueba;
    this-> prueba = vector<Cuadrupla>();
  }
  Casos(string sig, string id){
    this->etqPrueba = "";
    this->sig = sig;
    this->id = id;
    this-> prueba = vector<Cuadrupla>();
  }
};

struct Exp
{
  string dir;
  int tipo;
public:
  Exp(string dir, int tipo){
    this->dir=dir;
    this->tipo=tipo;
  }
};

struct Comb
{
  string vddr;
  string fls;
  int tipo;
public:
  Comb(string vddr, string fls){
    this->vddr = vddr;
    this->fls = fls;
    this->tipo = -1;
  }
};

struct Caso
{
  string id;
  string inicio;
  string sig;
  Cuadrupla prueba;
public:
  Caso(string id, string sig){
    this->id = id;
    this->sig = sig;
    this->inicio = "";
    this->prueba = Cuadrupla();
  }
};

struct Predeterminado
{
  string sig;
  string inicio;
  Cuadrupla prueba;
public:
  Predeterminado(string sig){
    this->sig = sig;
    this->inicio = "";
    this->prueba=Cuadrupla();
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
  BoolC Bo(BoolC bo);
  BoolCP BOP(BoolCP nBop);
  void RV();
  Exp E();
  ParteIzq PI();
  Casos CA(Casos caso);
  Comb CB(Comb cb);
  Caso CO(Caso ca);
  Predeterminado PR(Predeterminado pdr);
};



