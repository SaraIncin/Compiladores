#include "headers/parser.h"

extern Token yylex();
extern int yylineno;
Token tokenActual = Token(FIN, "");
Generador codigo = Generador();

Parser::Parser() {
  ts = TablaSimbolos();
  tt = TablaTipos();
  dir = 0;
  tc = vector<string>();
  listaRetorno = vector<int>();
  tt.iniciaTTPrimitivos();
}

void Parser::parse() {
  tokenActual = yylex();
  P();
  printf("%d\n", tokenActual.clase);
  if (tokenActual.equals(FIN)) {
    printf("Fin de análisis sintáctico\n");
  } else {
    error("No se encontro el fin de archivo");
  }
  ts.printTS("Global");
  tt.printTT("Global");
  codigo.escribeCodigo();
}

void Parser::error(string msg) {
  printf("\n%s", msg.c_str());
  printf(": línea %i\n", yylineno);
  exit(1);
}

void Parser::P() {
  this->pts.push(this->ts);
  this->ptt.push(this->tt);
  D();
  F();
}

void Parser::D() {
  if (tt.busca(tokenActual.clase)) { // Posible error con Tipo.
    int ti = TI();
    LV(ti);
    if (tokenActual.equals(PCOMA)) {
      printf("%d\n", tokenActual.clase);
      tokenActual = yylex();
      D();
    } else {
      error("Se esperaba un ; al final de la declaración");
    }
  }
}

int Parser::TI() {
  int b = B();
  Compuesto c = C(b);
  return c.tipo;
}

void Parser::LV(int tipo) {
  if (tokenActual.equals(ID)) {
    if (!ts.busca(tokenActual.valor)) {
      ts.inserta(Simbolo(tokenActual.valor, this->dir, tipo, VAR));
      dir += tt.buscaTam(tipo);
      tokenActual = yylex();
    } else {
      error("Variable ya declarada");
    }
    LVP(tipo);
  } else {
    error("Se esperaba un identificador");
  }
}

void Parser::LVP(int tipo) {
  if (tokenActual.equals(COMA)) {
    tokenActual = yylex();
    if (tokenActual.equals(ID)) {
      if (!ts.busca(tokenActual.valor)) {
        ts.inserta(Simbolo(tokenActual.valor, this->dir, tipo, VAR));
        dir += tt.buscaTam(tipo);
        tokenActual = yylex();
      } else {
        error("Variable ya declarada");
      }
      LVP(tipo);
    } else {
      error("Se esperaba un identificador");
    }
  }
}

int Parser::B() {
  switch (tokenActual.clase) {
  case INT:
    break;

  case FLOAT:
    break;

  case CHAR:
    break;

  case DOUBLE:
    break;

  case VOID:
    break;

  default:
    error("Esperaba un tipo");
    break;
  }
  int clase = tokenActual.clase;
  tokenActual = yylex();
  return clase;
}

Compuesto Parser::C(Compuesto comp) {

  if (tokenActual.equals(CIZQ)) {
    tokenActual = yylex();
    if (tokenActual.equals(INT)) {
      int tam = stoi(tokenActual.valor);
      tokenActual = yylex();
      if (tokenActual.equals(CDER)) {
        tokenActual = yylex();
        Compuesto c1 = Compuesto(comp.base);
        Compuesto res = C(c1);
        Tipo nTipo = Tipo(tt.nuevoID(), "array", tam, res.tipo);
        tt.inserta(nTipo);
        comp.tipo = nTipo.id;
      } else {
        error("Se esperaba ]");
      }
    } else {
      error("Se esperaba un entero");
    }

  } else {
    comp.tipo = comp.base;
  }
  return comp;
}

void Parser::F() {
  if (tokenActual.equals(FUNC)) {
    tokenActual = yylex();
    int tipo = TI();

    if (tokenActual.equals(ID)) {
      string id = tokenActual.valor;
      tokenActual = yylex();
      if (!ts.busca(id)) {
        this->listaRetorno = vector<int>();
        pts.push(ts);
        this->ts = TablaSimbolos();
        ptt.push(tt);
        this->tt = TablaTipos();
        pDir.push(this->dir);
        this->dir = 0;
        codigo.generaCodigo(Cuadrupla(C_LABEL, id, "", ""));
        tt.iniciaTTPrimitivos();
        // Posible error et

        if (tokenActual.equals(PIZQ)) {
          tokenActual = yylex();
          vector<int> args = A();
          if (tokenActual.equals(PDER)) {
            tokenActual = yylex();
            BL();

            ts.printTS(id);
            tt.printTT(id);
            ts = pts.top();
            pts.pop();
            tt = ptt.top();
            ptt.pop();
            dir = pDir.top();
            pDir.pop();

            if (ts.listaCompatibles(this->listaRetorno, tipo)) {
              ts.inserta(Simbolo(id, dir, tipo, FUNCION, args));
              string t1 = nuevaEtiqueta("fin func");
              codigo.generaCodigo(Cuadrupla(C_LABEL, t1, "", ""));
            } else {
              error("Tipo de retorno no compatible.");
            }
          } else {
            error("Se esperaba )");
          }
        } else {
          error("Se esperaba (");
        }
      } else {
        error("La función ya está declarada");
      }
    } else {
      error("Se esperaba el nombre de la función");
    }
  }
}

vector<int> Parser::A() {
  if (tt.busca(tokenActual.clase)) {
    vector<int> la = LA();
    return la;
  }
  return vector<int>();
}

vector<int> Parser::LA() {
  int tipo = TI();
  if (tokenActual.equals(ID)) {
    string id = tokenActual.valor;
    tokenActual = yylex();
    if (!ts.busca(id)) {
      ts.inserta(Simbolo(id, dir, tipo, PARAM));
      dir += tt.buscaTam(tipo);
    }
  } else {
    error("Parametro ya declarado");
  }
  ListaArg nArgs = ListaArg(vector<int>());
  nArgs.listaH.push_back(tipo);
  ListaArg nArgsP = LAP(nArgs);
  return nArgsP.listaS;
}

ListaArg Parser::LAP(ListaArg nArgs) {
  if (tokenActual.equals(COMA)) {
    tokenActual = yylex();
    int tipo = TI();
    if (tokenActual.equals(ID)) {
      string id = tokenActual.valor;
      tokenActual = yylex();
      if (!ts.busca(id)) {
        ts.inserta(Simbolo(id, dir, tipo, PARAM));
        dir += tt.buscaTam(tipo);
      }
    } else {
      error("Parametro ya declarado");
    }
    nArgs.listaH.push_back(tipo);
    ListaArg nArgsP = LAP(nArgs);
    nArgs.listaS = nArgsP.listaS;
  } else {
    nArgs.listaS = nArgs.listaH;
  }
  return nArgs;
}

void Parser::BL() {
  if (tokenActual.equals(KIZQ)) {
    tokenActual = yylex();
    D();
    I();
    if (tokenActual.equals(KDER)) {
      tokenActual = yylex();
      return;
    } else {
      error("Cuerpo de bloque sin cerrar");
    }
  } else {
    error("Falta cuerpo a la funcion");
  }
}

void Parser::I() {
  string s = nuevaEtiqueta("inst"); // t2
  S(s);
  codigo.generaCodigo(Cuadrupla(C_LABEL, s, "", ""));
  IP();
}

void Parser::IP() {
  switch (tokenActual.clase) {
  case IF:
    break;

  case WHILE:
    break;

  case DO:
    break;

  case BREAK:
    break;

  case RETURN:
    break;

  case SWITCH:
    break;

  case PRINT:
    break;

  case SCAN:
    break;

  case ID:
    break;

  case KIZQ:
    break;

  default:
    return;
  }

  string sig = nuevaEtiqueta("instP");
  codigo.generaCodigo(Cuadrupla(C_LABEL, sig, "", ""));

  S(sig);
  IP();
}

void Parser::S(string sig) {
  switch (tokenActual.clase) {
  case IF: {
    tokenActual = yylex();
    printf("Sentencia IF\n");
    if (tokenActual.equals(PIZQ)) {

      tokenActual = yylex();
      BoolC bo = BoolC(nuevaEtiqueta("if_cond"), nuevoIndice());

      BoolC nBo = Bo(bo);
      codigo.generaCodigo(Cuadrupla(C_LABEL, nBo.vddr, "", ""));
      printf("Saliendo de BO\n");
      if (tokenActual.equals(PDER)) {
        tokenActual = yylex();

        S(sig);
        printf("Saliendo de S\n");
        vector<string> indices = vector<string>();
        indices.push_back(nBo.fls);
        SentenciaP sp = SentenciaP(sig, indices);
        SP(sp);
        printf("Saliendo de SP\n");

      } else {
        error("Se esperaba )");
      }
    } else {
      error("Se esperaba (");
    }
    break;
  }
  case WHILE: {
    tokenActual = yylex();
    printf("Sentencia WHILE\n");
    if (tokenActual.equals(PIZQ)) {
      tokenActual = yylex();
      BoolC bo = BoolC(nuevaEtiqueta("while cond"), sig);

      BoolC nBo = Bo(bo);
      printf("Saliendo BO\n");
      if (tokenActual.equals(PDER)) {
        tokenActual = yylex();

        string s1Sig = nuevaEtiqueta("while body");
        S(s1Sig);
        codigo.generaCodigo(Cuadrupla(C_LABEL, s1Sig, "", ""));    // t4
        codigo.generaCodigo(Cuadrupla(C_LABEL, nBo.vddr, "", "")); // t3
        codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", s1Sig));     // goto t4
      } else {
        error("Se esperaba )");
      }
    } else {
      error("Se esperaba (");
    }
    break;
  }
  case DO: {
    tokenActual = yylex();
    printf("Sentencia DO\n");
    string s2Sig = nuevaEtiqueta("do_body");
    codigo.generaCodigo(Cuadrupla(C_LABEL, s2Sig, "", ""));
    S(s2Sig);
    if (tokenActual.equals(WHILE)) {
      tokenActual = yylex();
      if (tokenActual.equals(PIZQ)) {
        tokenActual = yylex();
        BoolC bo = BoolC(nuevaEtiqueta("do_cond"), s2Sig);
        BoolC nBo = Bo(bo);
        if (tokenActual.equals(PDER)) {
          tokenActual = yylex();
          codigo.generaCodigo(Cuadrupla(C_LABEL, nBo.vddr, "", ""));
        }
      } else {
        error("Se esperaba (");
      }
    } else {
      error("Do sin While");
    }
    break;
  }

  case BREAK: {
    tokenActual = yylex();
    if (tokenActual.equals(PCOMA)) {
      tokenActual = yylex();
      codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", sig));
    } else {
      error("Se esperaba ;");
    }
    break;
  }
  case RETURN: {
    tokenActual = yylex();
    RV();
    if (tokenActual.equals(PCOMA)) {
      tokenActual = yylex();
    } else {
      error("Se esperaba \";\"");
    }
    break;
  }
  case SWITCH: {
    tokenActual = yylex();
    printf("Sentencia SWITCH\n");
    if (tokenActual.equals(PIZQ)) {
      tokenActual = yylex();
      BoolC bo = BoolC();
      BoolC nBo = Bo(bo);
      if (tokenActual.equals(PDER)) {
        tokenActual = yylex();
        string etq_sw = nuevaEtiqueta("switch");
        Casos caso = Casos(sig, nBo.dir, etq_sw);
        codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", etq_sw));
        if (tokenActual.equals(KIZQ)) {
          tokenActual = yylex();
          Casos nCaso = CA(caso);

          if (tokenActual.equals(KDER)) {
            tokenActual = yylex();

            codigo.generaCodigo(Cuadrupla(C_LABEL, nCaso.etqPrueba, "", ""));
            codigo.agregaCodigo(nCaso.prueba);
          } else {
            error("Se esperaba }");
          }
        } else {
          error("Se esperaba {");
        }

      } else {
        error("Se esperaba )");
      }
    } else {
      error("Se esperaba (");
    }
    break;
  }
  case PRINT: {
    tokenActual = yylex();
    printf("Sentencia PRINT\n");
    Exp e = E();
    codigo.generaCodigo(Cuadrupla(C_PRINT, e.dir, "", ""));
    break;
  }
  case SCAN: {
    tokenActual = yylex();
    printf("Sentencia SCAN\n");
    ParteIzq pi = PI();
    codigo.generaCodigo(Cuadrupla(C_SCAN, pi.dir, "", ""));
    break;
  }
  case ID: {
    tokenActual = yylex();
    printf("Sentencia ID\n");
    ParteIzq pi = PI();
    tokenActual = yylex();
    if (tokenActual.equals(ASSIG)) {
      BoolC bo = BoolC();
      BoolC nBo = Bo(bo);
      if (equivalentes(pi.tipo, nBo.tipo)) {
        string d1 = reduce(nBo.dir, nBo.tipo, pi.tipo);
        codigo.generaCodigo(Cuadrupla(C_COPY, d1, "", pi.dir));
      } else {
        error("Tipos incompatibles");
      }
      if (tokenActual.equals(PCOMA)) {
        tokenActual = yylex();
      }
    }
    break;
  }
  case KIZQ: {
    printf("Sentencia BLOQUE\n");
    BL();
    // codigo.generaCodigo(Cuadrupla(C_LABEL, sig, "", ""));
    break;
  }
  default:
    return;
  }
}

void Parser::SP(SentenciaP senten) {
  if (tokenActual.equals(ELSE)) {
    tokenActual = yylex();
    S(senten.sig);
    codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", senten.sig));
    codigo.generaCodigo(Cuadrupla(C_LABEL, senten.indices[0], "", ""));
    codigo.reemplazarIndices(nuevaEtiqueta("sent cond"), senten.indices);
  } else {
    codigo.reemplazarIndices(senten.sig, senten.indices);
  }
}

BoolC Parser::Bo(BoolC bo) {
  Comb cb = Comb(bo.vddr, nuevoIndice());

  Comb nCb = CB(cb); // Combo

  BoolCP bop = BoolCP(bo.tipo, vector<string>());

  bop.indices.push_back(nCb.fls);

  bop.tipoH = nCb.tipo;
  BoolCP nBop = BOP(bop);

  bo.tipo = bop.tipoS;
  codigo.generaCodigo(Cuadrupla(C_LABEL, nCb.fls, "", ""));
  return bo;
}

BoolCP Parser::BOP(BoolCP nBop) {
  if (tokenActual.equals(OR)) {
    tokenActual = yylex();
    Comb cb = Comb(nBop.vddr, nuevoIndice());
    Comb nCb = CB(cb);
    printf("Aqui\n");
    if (equivalentes(nBop.tipoH, nCb.tipo)) {
      BoolCP bop = BoolCP(nBop.vddr, nBop.fls, nCb.tipo, nBop.indices);
      printf("Aqui2\n");
      bop.indices.push_back(nCb.fls);
      codigo.generaCodigo(Cuadrupla(C_LABEL, bop.fls, "", ""));
      BoolCP superBop = BOP(bop);
      printf("Aqu3\n");
      nBop.tipoS = superBop.tipoS;
    } else {
      error("Tipos incompatibles");
    }
  } else {
    codigo.reemplazarIndices(nBop.fls, nBop.indices);
    nBop.tipoS = INT;
    printf("Aqu4\n");
  }
  return nBop;
}

void Parser::RV() {
  switch (tokenActual.clase) {
  case SUB:

  case NEG:

  case PIZQ:

  case NUM:

  case STRING:

  case TRUE:

  case FALSE:

  case ID: {
    Exp expr = E();
    this->listaRetorno.push_back(expr.tipo);
    codigo.generaCodigo(Cuadrupla(C_RETURN, "", "", expr.dir));
    break;
  }
  default: {
    this->listaRetorno.push_back(VOID);
    codigo.generaCodigo(
        Cuadrupla(C_RETURN, "", "", "")); // Posible error de return
    break;
  }
  }
}

Exp Parser::E() {
  switch (tokenActual.clase) {
  case NEG:
  case SUB:
  case PIZQ:
  case NUM:
  case STRING:
  case TRUE:
  case FALSE:
  case ID: {
    Term t = T();
    ExpPP epp = ExpPP(t.tipo, t.dir);
    ExpPP nepp = EPP(epp);
    return Exp(t.dir, nepp.tipoS);
  }
  default:
    error("Se esperada un término al inicio de la expresión");
  }
  return Exp("", -1); // Nunca se debería ejecutar esta línea
}

ExpPP Parser::EPP(ExpPP epp) {
  switch (tokenActual.clase) {
  case SUM:
  case SUB: {
    ExpP ep = ExpP(epp.tipoH, epp.dirH);
    ExpP nEp = EP(ep);
    ExpPP nEpp = ExpPP(epp.tipoH, nEp.dir);
    ExpPP lastEpp = EPP(nEpp);
    epp.tipoS = lastEpp.tipoS;
    break;
  }
  default:
    epp.tipoS = epp.tipoH;
  }
  return epp;
}

ExpP Parser::EP(ExpP ep) {
  int op = -1;
  switch (tokenActual.clase) {
  case SUM:
    op = C_PLUS;
    break;
  case SUB:
    op = C_MINUS;
    break;
  default:
    error("Se esperaba suma o resta entre expresiones");
  }
  tokenActual = yylex();

  switch (tokenActual.clase) {
  case NEG:
  case SUB:
  case PIZQ:
  case NUM:
  case STRING:
  case TRUE:
  case FALSE:
  case ID: {
    Term t = T();
    if (equivalentes(ep.tipoH, t.tipo)) {
      ep.tipo = maximo(ep.tipoH, t.tipo);
      ep.dir = nuevaTemporal();
      string d1 = amplia(ep.dirH, ep.tipoH, ep.tipo);
      string d2 = amplia(t.dir, t.tipo, ep.tipo);
      codigo.generaCodigo(Cuadrupla(op, d1, d2, ep.dir));
    } else {
      error("Tipos incompatibles en la expresión");
    }
    break;
  }
  default:
    error("Se esperaba término en la expresión");
  }
  return ep;
}

Term Parser::T() {
  Term t = Term(-1, "");
  switch (tokenActual.clase) {
  case NEG:
  case SUB:
  case PIZQ:
  case NUM:
  case STRING:
  case TRUE:
  case FALSE:
  case ID: {
    Unitary u = U();
    TermPP tpp = TermPP(u.tipo, u.dir);
    TermPP nTpp = TPP(tpp);
    t.tipo = nTpp.tipoS;
    t.dir = u.dir;
    break;
  }
  default:
    error("Se esperaba una expresión unitaria en el término");
  }
  return t;
}

TermP Parser::TP(TermP tp) {
  int op = -1;
  switch (tokenActual.clase) {
  case MUL:
    op = C_MUL;
    break;
  case DIV:
    op = C_DIV;
    break;
  case RES:
    op = C_MOD;
    break;
  default:
    error("Se esperaba mul, div o mod como oerapción de términos");
  }
  tokenActual = yylex();

  switch (tokenActual.clase) {
  case NEG:
  case SUB:
  case PIZQ:
  case NUM:
  case STRING:
  case TRUE:
  case FALSE:
  case ID: {
    Unitary u = U();
    if (equivalentes(tp.tipoH, u.tipo)) {
      tp.tipo = maximo(tp.tipoH, u.tipo);
      tp.dir = nuevaTemporal();
      string d1 = amplia(tp.dirH, tp.tipoH, tp.tipo);
      string d2 = amplia(u.dir, u.tipo, tp.tipo);
      codigo.generaCodigo(Cuadrupla(op, d1, d2, tp.dir));
    } else {
      error("Tipos incompatibles en el término");
    }
    break;
  }
  default:
    error("Se esperaba un factor");
  }
  return tp;
}

TermPP Parser::TPP(TermPP tpp) {
  switch (tokenActual.clase) {
  case MUL:
  case DIV:
  case RES: {
    TermP tp = TermP(tpp.tipoH, tpp.dirH);
    TermP nTp = TP(tp);
    TermPP nTpp = TermPP(nTp.tipo, nTp.dir);
    TermPP finalTpp = TPP(nTpp);
    tpp.tipoS = finalTpp.tipoS;
    break;
  }
  default:
    tpp.tipoS = tpp.tipoH;
  }
  return tpp;
}

Unitary Parser::U() { return Unitary("", -1); }

ParteIzq Parser::PI() {
  if (tokenActual.equals(ID)) {
    string id = tokenActual.valor;
    tokenActual = yylex();
    ParteIzqP pip = ParteIzqP(id);
    ParteIzqP npip = PIP(pip);
    ParteIzq pi = ParteIzq(npip.tipo, npip.dir);

    return pi;
  } else {
    error("Se esperaba un identificador");
  }

  return ParteIzq(-1, ""); // Tal vez no funcione.
}

ParteIzqP Parser::PIP(ParteIzqP pip) {
  if (tokenActual.equals(CIZQ)) {
    Localizacion l = Localizacion(pip.base);
    Localizacion nl = LO(l);
    pip.dir = nl.dir;
    pip.tipo = nl.tipo;
  } else if (ts.busca(pip.base)) {
    pip.dir = pip.base;
    pip.tipo = ts.buscaTipo(pip.dir);
  } else {
    error("Variable sin declarar");
  }

  return pip;
}

Casos Parser::CA(Casos casos) {
  switch (tokenActual.clase) {
  case CASE: {
    Caso ca = Caso(casos.id, casos.sig);
    Caso nCa = CO(ca);
    Casos nCasos = Casos(casos.sig, casos.id);
    codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", casos.sig));
    Casos superCasos = CA(nCasos);
    superCasos.prueba.insert(superCasos.prueba.begin(), nCa.prueba);
    casos.prueba = superCasos.prueba;

    break;
  }
  case DEFAULT: {
    Predeterminado pdr = Predeterminado(casos.sig);
    Predeterminado nPdr = PR(pdr);
    casos.prueba.push_back(nPdr.prueba);
    codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", casos.sig));
    break;
  }
  default: {
    casos.prueba = vector<Cuadrupla>();
    break;
  }
  }
  return casos;
}

Predeterminado Parser::PR(Predeterminado pdr) {
  if (tokenActual.equals(DEFAULT)) {
    tokenActual = yylex();
    if (tokenActual.equals(DOSP)) {
      tokenActual = yylex();
      pdr.inicio = nuevaEtiqueta("default");
      pdr.prueba = Cuadrupla(C_GOTO, "", "", pdr.inicio);
      codigo.generaCodigo(Cuadrupla(C_LABEL, pdr.inicio, "", ""));
      I();
    } else {
      error("Se esperaba \":\"");
    }
  } else {
    error("Se esperaba default");
  }
  return pdr;
}

Caso Parser::CO(Caso ca) {
  if (tokenActual.equals(CASE)) {
    tokenActual = yylex();
    if (tokenActual.equals(NUM)) {
      string numVal = tokenActual.valor;
      tokenActual = yylex();
      if (tokenActual.equals(DOSP)) {
        tokenActual = yylex();
        // I.sig = CO.sig <- Posible error
        ca.inicio = nuevaEtiqueta("case");
        codigo.generaCodigo(Cuadrupla(C_LABEL, ca.inicio, "", ""));
        I();

        ca.prueba = Cuadrupla(C_IF_EQ, ca.id, numVal, ca.inicio);
      }
    }
  }
  return ca;
}

Comb Parser::CB(Comb cb) {
  Igualdad ig = Igualdad(nuevoIndice(), cb.fls);
  Igualdad nig = IG(ig);
  CombP ncb = CombP(vector<string>(), nig.tipo);
  ncb.indices.push_back(nig.vddr);
  codigo.generaCodigo(Cuadrupla(C_LABEL, nig.vddr, "", ""));
  CombP cbp = CBP(ncb);
  cb.tipo = cbp.tipoS;

  return cb;
}

CombP Parser::CBP(CombP cbp) {
  printf("%d\n", tokenActual.clase);
  if (tokenActual.equals(AND)) {
    Igualdad ig = Igualdad(nuevoIndice(), cbp.fls);
    tokenActual = yylex();
    Igualdad nig = IG(ig);

    if (equivalentes(cbp.tipoH, nig.tipo)) {
      CombP cbp1 = CombP(cbp.indices, nig.tipo, cbp.vddr, cbp.fls);
      cbp1.indices.push_back(nig.vddr);
      codigo.generaCodigo(Cuadrupla(C_LABEL, nig.vddr, "", ""));
      CombP ncbp = CBP(cbp1);
      cbp.tipoS = ncbp.tipoS;
    } else {
      error("Tipos incompatibles");
    }
  } else {
    codigo.reemplazarIndices(cbp.vddr, cbp.indices);
    cbp.tipoS = INT;
  }

  return cbp;
}

Igualdad Parser::IG(Igualdad ig) {
  ig.vddr = "k onda k pes";
  ig.fls = "no k onda no k pes";
  return ig;
}

Rel Parser::R(Rel r) {
  switch (tokenActual.clase) {
  case SUB:
  case NEG:
  case PIZQ:
  case NUM:
  case STRING:
  case TRUE:
  case FALSE:
  case ID:
    Exp e = E();
    RelP relp = RelP(e.tipo, r.vddr, r.fls, e.dir);
    RelP nRelp = RP(relp);
    r.tipo = nRelp.tipoS;
  }
  return r;
}

RelP Parser::RP(RelP r) {
  int op = -1;
  switch (tokenActual.clase) {
  case LESS:
    op = C_LE;
    break;
  case LEQ:
    op = C_LEQ;
    break;
  case GEQ:
    op = C_GEQ;
    break;
  case GRE:
    op = C_GE;
    break;
  default:
    r.tipoS = r.tipoH;
    return r;
  }
  tokenActual = yylex();

  switch (tokenActual.clase) {
  case SUB:
  case NEG:
  case PIZQ:
  case NUM:
  case STRING:
  case TRUE:
  case FALSE:
  case ID: {
    Exp e = E();
    if (equivalentes(r.tipoH, e.tipo)) {
      r.tipoS = INT;
      r.dir = nuevaTemporal();
      int nTipo = maximo(r.tipoH, e.tipo);
      string d1 = amplia(r.dirH, r.tipoH, nTipo);
      string d2 = amplia(e.dir, e.tipo, nTipo);
      codigo.generaCodigo(Cuadrupla(op, d1, d2, r.dir));
      codigo.generaCodigo(Cuadrupla(C_IF, r.dir, r.vddr, ""));
      codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", r.fls));
    } else {
      error("Tipos incompatibles en la comparación");
    }
    break;
  }
  default:
    error("Se esperaba una expresión para usar con el oerador relacional");
  }
  return r;
}

Localizacion Parser::LO(Localizacion loc) { return loc; }

/*
 * Función encarga de  hacer un casteo de un tipo menor a un tipo mayor
 */
string Parser::amplia(string dir, int t1, int t2) {

  if (t1 == t2)
    return dir;
  string temp = Parser::nuevaTemporal();

  // Entero a float
  if (t1 == INT && t2 == FLOAT) {
    codigo.generaCodigo(Cuadrupla(C_COPY, "(float)" + dir, "", temp));
    return temp;
  }

  // Entero a double
  if (t1 == INT && t2 == DOUBLE) {
    codigo.generaCodigo(Cuadrupla(C_COPY, "(double)" + dir, "", temp));
    return temp;
  }

  // Float a double
  if (t1 == FLOAT && t2 == DOUBLE) {
    codigo.generaCodigo(Cuadrupla(C_COPY, "(double)" + dir, "", temp));
    return temp;
  }
  return "";
}

/*
 * Función encarga de  hacer un casteo de un tipo mayor a un tipo menor
 */
string Parser::reduce(string dir, int t1, int t2) {
  if (t1 == t2)
    return dir;
  string temp = nuevaTemporal();

  // float a int
  if (t1 == INT && t2 == FLOAT) {
    codigo.generaCodigo(Cuadrupla(C_COPY, "(int)" + dir, "", temp));
    return temp;
  }

  // double a int
  if (t1 == INT && t2 == DOUBLE) {
    codigo.generaCodigo(Cuadrupla(C_COPY, "(int)" + dir, "", temp));
    return temp;
  }

  // double a float
  if (t1 == FLOAT && t2 == DOUBLE) {
    codigo.generaCodigo(Cuadrupla(C_COPY, "(float)" + dir, "", temp));
    return temp;
  }
  return "";
}

string Parser::nuevaTemporal() {
  static int numTemp = 0;
  string etq = "t" + numTemp++;
  return etq;
}
