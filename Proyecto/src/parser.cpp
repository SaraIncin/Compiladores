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
        printf("Fin de análisis sintáctico\n");
    }else{
        error("No se encontro el fin de archivo\n");
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
                codigo.generaCodigo(Cuadrupla(C_LABEL, id, "", ""));
                tt.iniciaTTPrimitivos();
                //Posible error et
                
                
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
                            string t1 = nuevaEtiqueta();
                            codigo.generaCodigo(Cuadrupla(C_LABEL, t1, "", ""));
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
            tokenActual = yylex();
            return;
        }else{
            error("Cuerpo de funcion sin cerrar");
        }
    }else{
        error("Falta cuerpo a la funcion");
    }
}

void Parser::I(){
    string s = nuevaEtiqueta();//t2
    codigo.generaCodigo(Cuadrupla(C_LABEL, s, "", ""));
    S(s);
    IP();
}

void Parser::IP(){
    switch (tokenActual.clase)
    {
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

    string sig = nuevaEtiqueta();
    codigo.generaCodigo(Cuadrupla(C_LABEL, sig, "", ""));
    
    S(sig);
    IP();
}

void Parser::S(string sig){
    switch (tokenActual.clase)
    {
    case IF:
        tokenActual = yylex();
        if(tokenActual.equals(PIZQ)){
            tokenActual = yylex();
            BoolC bo = BoolC(nuevaEtiqueta(), nuevoIndice());
            Bo(bo);
            if(tokenActual.equals(PDER)){
                tokenActual = yylex();
                S(sig);
                vector<string> indices = vector<string>();
                indices.push_back(bo.fls);
                SentenciaP sp = SentenciaP(sig, indices);
                SP(sp);
                codigo.generaCodigo(Cuadrupla(C_LABEL, bo.vddr, "", ""));
            }else{
                error("Se esperaba )");    
            }
        }else{
            error("Se esperaba (");
        }
        break;

    case WHILE:
        tokenActual = yylex();
        if(tokenActual.equals(PIZQ)){
            tokenActual = yylex();
            BoolC bo = BoolC(nuevaEtiqueta(), sig);
            Bo(bo);
            if(tokenActual.equals(PDER)){
                tokenActual = yylex();

                string s1Sig = nuevaEtiqueta();
                S(s1Sig);
                codigo.generaCodigo(Cuadrupla(C_LABEL, s1Sig, "", ""));//t4
                codigo.generaCodigo(Cuadrupla(C_LABEL, bo.vddr, "", ""));//t3
                codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", s1Sig));//goto t4
            }else{
                error("Se esperaba )");
            }
        }else{
            error("Se esperaba (");
        }
        break;

    case DO:{
        tokenActual = yylex();
        string s2Sig = nuevaEtiqueta();
        S(s2Sig);
        printf("--------Do %d\n", tokenActual.clase);
        if(tokenActual.equals(WHILE)){
            tokenActual = yylex();
            if(tokenActual.equals(PIZQ)){
                tokenActual = yylex();
                BoolC bo = BoolC(nuevaEtiqueta(), s2Sig);
                Bo(bo);
                if(tokenActual.equals(PDER)){
                    tokenActual = yylex();
                    codigo.generaCodigo(Cuadrupla(C_LABEL, bo.vddr, "", ""));
                    codigo.generaCodigo(Cuadrupla(C_LABEL, s2Sig, "", ""));

                }
            }else{
                error("Se esperaba (");
            }
        }else{
            error("Do sin While");
        }
        break;
    }

    case BREAK:
        tokenActual = yylex();
        codigo.generaCodigo(Cuadrupla(C_GOTO, "", "", sig));
        break;
    
    case RETURN:
        tokenActual = yylex();
        RV();
        break;
    
    case SWITCH:
        break;
    
    case PRINT:
        tokenActual = yylex();
        string eDir = E();
        codigo.generaCodigo(Cuadrupla());
        break;

    case SCAN:
        tokenActual = yylex();

        break;
    
    case ID:
        break;

    case KIZQ:
        BL();
        //codigo.generaCodigo(Cuadrupla(C_LABEL, sig, "", ""));
        break;

    default:
        return;
    }
}

void Parser::SP(SentenciaP senten){

}

void Parser::Bo(BoolC bo){

}

void Parser::RV(){

}

string Parser::E(){


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
    


