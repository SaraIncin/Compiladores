#include "headers/simbolo.h"

typedef unsigned int uint;

bool TablaSimbolos::busca(string id){
    
    vector<Simbolo> TS = this -> tabla;
    uint tam = TS.size();
    //Si está vacía
    if (tam <= 0)
        return false;
    //Iteramos buscando el id
    for (auto & sim : TS){
        if (sim.id.compare(id) == 0)
            return true;
    }
    //No fue encontrado
    return false;
}

bool TablaSimbolos::inserta(Simbolo s){
    
    bool existe = this -> busca(s.id);
    //Si ya existe regresamos
    if (existe)
        return false;
    //Insertamos el simbolo en la tabla
    this -> tabla.push_back(s);
    //Insertamos con éxito
    return true;
}

int TablaSimbolos::buscaDir(string id){
    
    vector<Simbolo> TS = this -> tabla;
    //Iterammos buscando la direccion
    for (auto & sim : TS){
        if (sim.id.compare(id) == 0)
            return sim.dir;
    }
    //No existe
    return -1;

}

int TablaSimbolos::buscaTipo(string id){
    
    vector<Simbolo> TS = this -> tabla;
    //Iterammos buscando el tipo
    for (auto & sim : TS){
        if (sim.id.compare(id) == 0)
            return sim.tipo;
    }
    //No existe
    return -1;
}

Simbolo Simbolo::nuevaTemporal(){
    Simbolo s = Simbolo();
    return s;
}

