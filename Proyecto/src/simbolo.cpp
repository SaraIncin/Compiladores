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

bool TablaSimbolos::listaCompatibles(vector<int> lista, int tipo){
    if(lista.size() != 0 && tipo != VOID)
        return false;
    for(auto & t : lista){
        int max = maximo(t, tipo);
        if(max == 1 || max != tipo){
            return false;
        }
    }
    return true;
}

void TablaSimbolos::printTS(string contexto){
    printf("Tabla de Simbolos de %s\n", contexto.c_str());
    vector<Simbolo> TS = this -> tabla;
    for(auto & sim : TS){
        printf("id: %s, direccion: %d, tipo: %d, variable: %d argumentos:", 
                sim.id.c_str(), sim.dir, sim.tipo, sim.var);
        for (auto & arg : sim.args)    
            printf(" %d,", arg);
        printf("\n");
    }
    printf("\n");
}
