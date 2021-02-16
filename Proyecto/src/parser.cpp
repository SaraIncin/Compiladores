#include "headers/parser.h"

extern Token yylex();
extern int yylineno;
Token tokenActual = Token(FIN, "");
Generador codigo = Generador();

Parser::Parser(){
  ts = TablaSimbolos();
  tt = TablaTipos();
  dir = 0;
  tc = vector<string>();
  listaRetorno = vector<int>();
  tt.iniciaTTPrimitivos();
}

void Parser::parse(){
    tokenActual = yylex();
    P();
    if(tokenActual.equals(FIN)){
        printf("Fin de análisis sintáctico");
    }else{
        error("No se encontro el fin de archivo");
    }
    ts.printTS("Global");
    tt.printTT("Global");
    codigo.escribeCodigo();

}

void Parser::error(string msg){
    printf("\n%s", msg.c_str());
    printf(": línea %i\n", yylineno);
    exit(1);
}

void Parser::P(){
    this->pts.push(this->ts);
    this->ptt.push(this->tt);
    D();
    F();
}

void Parser::D(){
    if(tt.busca(tokenActual.clase)){ //Posible error con Tipo.
        int ti = TI();
        LV(ti);
        if(tokenActual.equals(PCOMA)){
            printf("%d\n", tokenActual.clase);
            tokenActual = yylex();
            D();
        }else{
            error("Se esperaba un ; al final de la declaración");
        }
    }    
}

int Parser::TI(){
    int b = B();
    Compuesto c = C(b);
    return c.tipo;
}

void Parser::LV(int tipo){
    if(tokenActual.equals(ID)){
        if(!ts.busca(tokenActual.valor)){
            ts.inserta(Simbolo(tokenActual.valor, this->dir, tipo, VAR));
            dir += tt.buscaTam(tipo);
            tokenActual = yylex();
        }else{
            error("Variable ya declarada");
        }
        LVP(tipo);        
    }else{
        error("Se esperaba un identificador");
    }
}

void Parser::LVP(int tipo){
    if(tokenActual.equals(COMA)){
        tokenActual = yylex();
        if(tokenActual.equals(ID)){
            if(!ts.busca(tokenActual.valor)){
                ts.inserta(Simbolo(tokenActual.valor, this->dir, tipo, VAR));
                dir += tt.buscaTam(tipo);
                tokenActual = yylex();
            }else{
                error("Variable ya declarada");
            }
            LVP(tipo);
        }else{
            error("Se esperaba un identificador");
        }
    }
}

int Parser::B(){
    switch (tokenActual.clase)
    {
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

Compuesto Parser::C(Compuesto comp){

    if (tokenActual.equals(CIZQ)){
        tokenActual = yylex();
        if(tokenActual.equals(INT)){
            int tam = stoi(tokenActual.valor);
            tokenActual = yylex();
            if(tokenActual.equals(CDER)){
                tokenActual = yylex();
                Compuesto c1 = Compuesto(comp.base);
                Compuesto res = C(c1);
                Tipo nTipo = Tipo(tt.nuevoID(), "array", tam, res.tipo);
                tt.inserta(nTipo);
                comp.tipo = nTipo.id;
            }else{
                error("Se esperaba ]");
            }
        }else{
            error("Se esperaba un entero");
        }
        
    }else{
        comp.tipo = comp.base;
    }
    return comp;
}

void Parser::F(){
    if(tokenActual.equals(FUNC)){
        tokenActual = yylex();
        int tipo = TI();
        
        if(tokenActual.equals(ID)){
            string id = tokenActual.valor;
            tokenActual = yylex();
            if(!ts.busca(id)){
                this->listaRetorno = vector<int>();
                pts.push(ts);
                this->ts = TablaSimbolos();
                ptt.push(tt);
                this->tt = TablaTipos();
                pDir.push(this->dir);
                this->dir = 0;
                tt.iniciaTTPrimitivos();
                //Posible error et
                string t1 = nuevaEtiqueta();
                codigo.generaCodigo(Cuadrupla(C_LABEL, t1, "", ""));
                
                if(tokenActual.equals(PIZQ)){
                    tokenActual = yylex();
                    vector<int> args = A();
                    if(tokenActual.equals(PDER)){
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
                        
                        if(ts.listaCompatibles(this->listaRetorno, tipo)){
                            ts.inserta(Simbolo(id, dir, tipo, FUNCION, args));
                            codigo.generaCodigo(Cuadrupla(C_LABEL, id, "", ""));
                            codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", t1));
                        }                        
                    }else{
                        error("Se esperaba )");
                    }
                }else{
                    error("Se esperaba (");
                }
            }else{
                error("La función ya está declarada");
            }
        }else{
            error("Se esperaba el nombre de la función");
        }
    }
}

vector<int> Parser::A(){
    if(tt.busca(tokenActual.clase)){
        vector<int> la = LA();
        return la;
    }
    return vector<int>();
}

vector<int> Parser::LA(){
    int tipo = TI();
    if(tokenActual.equals(ID)){
        string id = tokenActual.valor; 
        tokenActual = yylex();
        if(!ts.busca(id)){
            ts.inserta(Simbolo(id, dir, tipo, PARAM));
            dir += tt.buscaTam(tipo);
        }
    }else{
        error("Parametro ya declarado");
    }
    ListaArg nArgs = ListaArg(vector<int>());
    nArgs.listaH.push_back(tipo);
    ListaArg nArgsP = LAP(nArgs);
    return nArgsP.listaS;
}

ListaArg Parser::LAP(ListaArg nArgs){
    if(tokenActual.equals(COMA)){
        tokenActual = yylex();
        int tipo = TI();
        if(tokenActual.equals(ID)){
            string id = tokenActual.valor; 
            tokenActual = yylex();
            if(!ts.busca(id)){
                ts.inserta(Simbolo(id, dir, tipo, PARAM));
                dir += tt.buscaTam(tipo);
            }
        }else{
            error("Parametro ya declarado");
        }
        nArgs.listaH.push_back(tipo);
        ListaArg nArgsP = LAP(nArgs);
        nArgs.listaS = nArgsP.listaS;
    }else{
        nArgs.listaS = nArgs.listaH;
    }
    return nArgs;
}

void Parser::BL(){
    if(tokenActual.equals(KIZQ)){
        tokenActual = yylex();
        D();
        I();
        if(tokenActual.equals(KDER)){
            return;
        }else{
            error("Cuerpo de funcion sin cerrar");
        }
    }else{
        error("Falta cuerpo a la funcion");
    }
}

void Parser::I(){
}

/*
 * Función encarga de  hacer un casteo de un tipo menor a un tipo mayor
 */ 
string Parser::amplia(string dir, int t1, int t2){  
    
    if(t1 == t2) return dir; 
    string temp = Parser::nuevaTemporal();
    
    //Entero a float
    if(t1 == INT && t2 == FLOAT){        
        codigo.generaCodigo(Cuadrupla(C_COPY, "(float)"+dir, "", temp));
        return temp;
    }
    
    //Entero a double
    if(t1 == INT && t2 == DOUBLE){
        codigo.generaCodigo(Cuadrupla(C_COPY, "(double)"+dir, "", temp));
        return temp;
    }
    
    // Float a double
    if(t1== FLOAT && t2 == DOUBLE){
        codigo.generaCodigo(Cuadrupla(C_COPY, "(double)"+dir, "", temp));
        return temp;
    }
    return "";
}

/*
 * Función encarga de  hacer un casteo de un tipo mayor a un tipo menor
 */
string Parser::reduce(string dir, int t1, int t2){
    if(t1 == t2) return dir;
    string temp = nuevaTemporal();
    
    //float a int
    if(t1 == INT && t2 == FLOAT){        
        codigo.generaCodigo(Cuadrupla(C_COPY, "(int)"+dir, "", temp));
        return temp;
    }
    
    //double a int
    if(t1 == INT && t2 == DOUBLE){
        codigo.generaCodigo(Cuadrupla(C_COPY, "(int)"+dir, "", temp));
        return temp;
    }
    
    // double a float 
    if(t1== FLOAT && t2 == DOUBLE){
        codigo.generaCodigo(Cuadrupla(C_COPY, "(float)"+dir, "", temp));
        return temp;
    }
    return "";
}

string Parser::nuevaTemporal(){
    static int numTemp = 0;
    string etq = "t"+numTemp++;
    return etq;
}
    


