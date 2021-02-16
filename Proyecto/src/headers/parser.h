#include <stack>
#include <string>
#include <vector>

#include "simbolo.h"
#include "tipo.h"
#include "tokens.h"
#include "codigo.h"


using namespace std;

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
  void error(char* msg);
  string amplia(string dir, int t1, int t2);
  string reduce(string dir, int t1, int t2);
  string nuevaTemporal();
  void P();
  void D();
  int TI();
  void LV(int tipo);
};

struct Ti
{
  int tipo;
};
