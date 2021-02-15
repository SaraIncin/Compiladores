#include "headers/parser.h"

extern int yylex();
extern int yylineno;
int tokenActual;
Generador codigo;

Parser::Parser(){
  ts = TablaSimbolos();
  tt = TablaTipos();
  dir = 0;
  tc = vector<string>();
  listaRetorno = vector<int>();
}

void Parser::parse(){
    
}

void Parser::error(char* msg){
    printf("\n%s", msg);
    printf(": línea %i\n", yylineno);
    exit(1);
}

/**

void Parser::eat(int clase){
    if(equals(tokenActual, clase)) {
        // Consumimos el token
        tokenActual = yylex();
    } else {
        error("Error de sintaxis");
    }
}
**/

/*
 * Función encarga de  hacer un casteo de un tipo menor a un tipo mayor
 */ 
string Parser::amplia(string dir, int t1, int t2){  
    
    if(t1 == t2) return dir; 
    string temp = nuevaTemporal();
    
    //Entero a float
    if(t1 == 0 && t2 == 1){        
        codigo.generaCodigo(Cuadrupla("=", "(float)"+dir, "", temp));
        return temp;
    }
    
    //Entero a double
    if(t1 == 0 && t2 == 2){
        codigo.generaCodigo(Cuadrupla("=", "(double)"+dir, "", temp));
        return temp;
    }
    
    // Float a double
    if(t1== 1 && t2 == 2){
        codigo.generaCodigo(Cuadrupla("=", "(double)"+dir, "", temp));
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
    if(t1 == 0 && t2 == 1){        
        codigo.generaCodigo(Cuadrupla("=", "(int)"+dir, "", temp));
        return temp;
    }
    
    //double a int
    if(t1 == 0 && t2 == 2){
        codigo.generaCodigo(Cuadrupla("=", "(int)"+dir, "", temp));
        return temp;
    }
    
    // double a float 
    if(t1== 1 && t2 == 2){
        codigo.generaCodigo(Cuadrupla("=", "(float)"+dir, "", temp));
        return temp;
    }
    return "";
}

string Parser::nuevaTemporal(){
    static int numTemp = 0;
    string etq = "t"+numTemp++;
    return etq;
}
    


