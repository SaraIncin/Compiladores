#include "headers/parser.h"

extern Token yylex();
extern int yylineno;
Token tokenActual = yylex();
Generador codigo = Generador();

Parser::Parser(){
  ts = TablaSimbolos();
  tt = TablaTipos();
  dir = 0;
  tc = vector<string>();
  listaRetorno = vector<int>();
}

void Parser::parse(){
    this->P();
}

void Parser::error(char* msg){
    printf("\n%s", msg);
    printf(": línea %i\n", yylineno);
    exit(1);
}

void Parser::P(){
    this->pts.push(this->ts);
    this->ptt.push(this->tt);
    printf("Fin %d\n", tokenActual.clase);
}

void Parser::D(){
    int ti = TI();
    LV(ti);
    if(tokenActual.equals(PCOMA)){
        printf("%d\n", tokenActual.clase);
        tokenActual = yylex();
        D();
    }else if (tokenActual.equals(FIN)){
        return;
    }else{
        error("Se esperaba un ; al final de la declaración.");
    }
}
int Parser::TI(){
    printf("TI %d\n", tokenActual.clase);
    return 0;
}

void Parser::LV(int tipo){
    printf("LV %d\n", tokenActual.clase);
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
    


