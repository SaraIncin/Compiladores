#include <stack>
#include <string>
#include <vector>

#include "codigo.h"
#include "simbolo.h"

using namespace std;

struct Compuesto {
  int tipo;
  int base;

public:
  Compuesto(int tipo, int base) {
    this->tipo = tipo;
    this->base = base;
  }
  Compuesto(int base) {
    this->base = base;
    this->tipo = -1;
  }
};

struct ListaArg {
  vector<int> listaH;
  vector<int> listaS;

public:
  ListaArg(vector<int> listaH) {
    this->listaH = listaH;
    this->listaS = vector<int>();
  }
};

struct SentenciaP {
  string sig;
  vector<string> indices;

public:
  SentenciaP(string sig, vector<string> indices) {
    this->sig = sig;
    this->indices = indices;
  }
};

struct BoolC {
  string vddr;
  string fls;
  int tipo;
  string dir;

public:
  BoolC(string vddr, string fls) {
    this->vddr = vddr;
    this->fls = fls;
  }
  BoolC() {
    this->vddr = "";
    this->fls = "";
    this->dir = "";
    this->tipo = -1;
  }
};

struct BoolCP {
  string vddr;
  string fls;
  int tipoH;
  int tipoS;
  vector<string> indices;

public:
  BoolCP(int tipoH, vector<string> indices) {
    this->vddr = "";
    this->fls = "";
    this->tipoH = tipoH;
    this->tipoS = -1;
    this->indices = indices;
  }
  BoolCP(string vddr, string fls, int tipoH, vector<string> indices) {
    this->vddr = vddr;
    this->fls = fls;
    this->tipoH = tipoH;
    this->tipoS = -1;
    this->indices = indices;
  }
};

struct ParteIzq {
  int tipo;
  string dir;

public:
  ParteIzq(int tipo, string dir) {
    this->tipo = tipo;
    this->dir = dir;
  }
};

struct ParteIzqP {
  string base;
  string dir;
  int tipo;

public:
  ParteIzqP(string base) {
    this->base = base;
    this->dir = "";
    this->tipo = -1;
  }
};

struct Casos {
  string sig;
  string id;
  string etqPrueba;
  vector<Cuadrupla> prueba;

public:
  Casos(string sig, string id, string etqPrueba) {
    this->sig = sig;
    this->id = id;
    this->etqPrueba = etqPrueba;
    this->prueba = vector<Cuadrupla>();
  }
  Casos(string sig, string id) {
    this->etqPrueba = "";
    this->sig = sig;
    this->id = id;
    this->prueba = vector<Cuadrupla>();
  }
};

struct Exp {
  string dir;
  int tipo;

public:
  Exp(string dir, int tipo) {
    this->dir = dir;
    this->tipo = tipo;
  }
};

struct Comb {
  string vddr;
  string fls;
  int tipo;

public:
  Comb(string vddr, string fls) {
    this->vddr = vddr;
    this->fls = fls;
    this->tipo = -1;
  }
};

struct CombP {
  vector<string> indices;
  int tipoH;
  int tipoS;
  string vddr;
  string fls;

public:
  CombP(vector<string> indices, int tipoH) {
    this->indices = indices;
    this->tipoH = tipoH;
    this->tipoS = -1;
    this->vddr = "";
    this->fls = "";
  }
  CombP(vector<string> indices, int tipoH, string vddr, string fls) {
    this->indices = indices;
    this->tipoH = tipoH;
    this->tipoS = -1;
    this->vddr = vddr;
    this->fls = fls;
  }
};



struct Caso {
  string id;
  string inicio;
  string sig;
  Cuadrupla prueba;

public:
  Caso(string id, string sig) {
    this->id = id;
    this->sig = sig;
    this->inicio = "";
    this->prueba = Cuadrupla();
  }
};

struct Predeterminado {
  string sig;
  string inicio;
  Cuadrupla prueba;

public:
  Predeterminado(string sig) {
    this->sig = sig;
    this->inicio = "";
    this->prueba = Cuadrupla();
  }
};

struct Localizacion {
  string base;
  string dir;
  int tipo;

public:
  Localizacion(string base) {
    this->base = base;
    this->dir = "";
    this->tipo = -1;
  }
};

struct LocalizacionP {
  int tipo;
  int tipoS;
  int tam;
  string dir;
  string dirS;

public:
  LocalizacionP(int tipo, int tam, string dir) {
    this->tipo = tipo;
    this->tipoS = -1;
    this->tam = tam;
    this->dir = dir;
    this->dirS = "";
  }
};

struct Igualdad {
  string vddr;
  string fls;
  string dir;
  int tipo;

public:
  Igualdad(string vddr, string fls) {
    this->vddr = vddr;
    this->fls = fls;
    this->tipo = -1;
    this->dir="";
  }
};

struct IgualdadP
{
  string vddr;
  string fls;
  int tipoH;
  string dirH;
  string dirS;
  int tipoS;
  vector<string> indices;
public:
  IgualdadP(string vddr, string fls, int tipoH, string dirH, vector<string> indices){
    this->vddr=vddr;
    this->fls=fls;
    this->tipoH=tipoH;
    this->dirH=dirH;
    this->indices=indices;
    this->dirS="";
    this->tipoS=-1;
  }
  IgualdadP(int tipoH, string dirH){
    this->vddr="";
    this->fls="";
    this->tipoH=tipoH;
    this->dirH=dirH;
    this->indices=vector<string>();
    this->dirS="";
    this->tipoS=-1;
  }
};

struct Rel {
  string vddr;
  string fls;
  int tipo;
  string dir;

public:
  Rel(string vddr, string fls) {
    this->vddr = vddr;
    this->fls = fls;
    this->tipo = -1;
    this->dir = "";
  }
};

struct RelP {
  int tipoH;
  int tipoS;
  string vddr;
  string fls;
  string dir;
  string dirH;

public:
  RelP(int tipoH, string vddr, string fls, string dirH) {
    this->tipoH = tipoH;
    this->tipoS = -1;
    this->vddr = vddr;
    this->fls = fls;
    this->dir = "";
    this->dirH = dirH;
  }
};

struct Term {
  int tipo;
  string dir;

public:
  Term(int tipo, string dir) {
    this->tipo = tipo;
    this->dir = dir;
  }
};

struct TermP {
  int tipoH;
  int tipo;
  string dirH;
  string dir;

public:
  TermP(int tipoH, string dirH) {
    this->tipoH = tipoH;
    this->tipo = -1;
    this->dirH = dirH;
    this->dir = "";
  }
};

struct TermPP {
  int tipoH;
  int tipoS;
  string dirH;

public:
  TermPP(int tipoH, string dirH) {
    this->tipoH = tipoH;
    this->dirH = dirH;
  }
};

struct ExpP {
  int tipoH;
  int tipo;
  string dir;
  string dirH;

public:
  ExpP(int tipoH, string dirH) {
    this->tipoH = tipoH;
    this->tipo = -1;
    this->dirH = dirH;
    this->dir = "";
  }
};

struct ExpPP {
  string dirH;
  int tipoH;
  int tipoS;

public:
  ExpPP(int tipoH, string dirH) {
    this->dirH = dirH;
    this->tipoH = tipoH;
    this->tipoS = -1;
  }
};

struct Factor
{
  int tipo;
  string dir;
  string val;
public:
  Factor(){
    this->tipo = -1;
    this->dir = "";
    this->val = "";
  }
};

struct FactorP
{
  string dir;
  string base;
  int tipo;

public:
  FactorP(string dir){
    this->dir = dir;
    this->base = "";
    this->tipo = -1;
  }
};

struct Parametro
{
  vector<int> params;
public:
  Parametro(){
    this->params = vector<int>();
  }
};

struct ListaParam
{
  vector<int> param;
public:
  ListaParam(){
    this->param = vector<int>();
  }
};

struct ListaParamP
{
  vector<int> paramP;
public:
  ListaParamP(){
    this->paramP = vector<int>();
  }
};



struct Unitary {
  string dir;
  int tipo;

public:
  Unitary(string dir, int tipo) {
    this->dir = dir;
    this->tipo = tipo;
  }
};

struct Parser {
  vector<TablaSimbolos> pts;
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
  ExpP EP(ExpP ep);
  ExpPP EPP(ExpPP epp);
  ParteIzq PI();
  ParteIzqP PIP(ParteIzqP pip);
  Casos CA(Casos caso);
  Comb CB(Comb cb);
  CombP CBP(CombP cbp);
  Caso CO(Caso ca);
  Igualdad IG(Igualdad ig);
  IgualdadP IGP(IgualdadP igp);
  Predeterminado PR(Predeterminado pdr);
  Rel R(Rel r);
  RelP RP(RelP r);
  Term T();
  Factor FA();
  FactorP FAP(FactorP fap);
  Parametro PA();
  ListaParam LP();
  ListaParamP LPP();
  TermP TP(TermP tp);
  TermPP TPP(TermPP tpp);
  Unitary U();
  Localizacion LO(Localizacion lo);
  LocalizacionP LOP(LocalizacionP lop);
};
