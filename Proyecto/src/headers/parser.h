#include <stack>
#include <string>
#include <vector>

#include "simbolo.h"
#include "tipo.h"
#include "tokens.h"

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
  token *yylex();

public:
  Parser();
  void parse();

private:
  void error();
  void eat();
  Simbolo amplia(string d1, int tAct, int tMax);
  Simbolo reduce(string d1, int tAct, int tMin);
};
