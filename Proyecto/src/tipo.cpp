#include "headers/tipo.h"

bool TablaTipos::busca(int id) {
	for (Tipo t : tabla) {
		if (t.id == id)
			return true;
	}

	return false;
}

bool TablaTipos::inserta(Tipo t) {
	if (busca(t.id))
		return false;

	tabla.push_back(t);
	return true;
}

string TablaTipos::buscaNombre(int id) {
	for (Tipo t : tabla) {
		if (t.id == id)
			return t.nombre;
	}

	return "nel";
}

int TablaTipos::buscaTam(int id) {
	for (Tipo t : tabla) {
		if (t.id == id)
			return t.tam;
	}

	return -1;
}

int TablaTipos::buscaBase(int id) {
	for (Tipo t : tabla) {
		if (t.id == id)
			return t.base;
	}

	return -1;
}

int TablaTipos::nuevoID(){
	static int cont = 4000;
	cont++;
	return cont;
}

int maximo(int tipo1, int tipo2) {
	if (tipo1 == tipo2)
		return tipo1;

	if (tipo1 == 1005 && tipo2 == 1006 || tipo1 == 1006 && tipo2 == 1005)
		return 1;

	return -1;
}

bool equivalentes(int tipo1, int tipo2) {
	if (tipo1 == tipo2)
		return true;

	if (tipo1 == 1005 && tipo2 == 1006 || tipo1 == 1006 && tipo2 == 1005)
		return true;

	return false;
}

void TablaTipos::iniciaTTPrimitivos(){
	this->tabla.push_back(Tipo(INT, string("int"), 4, -1));
	this->tabla.push_back(Tipo(FLOAT, string("float"), 4, -1));
	this->tabla.push_back(Tipo(CHAR, string("char"), 1, -1));
	this->tabla.push_back(Tipo(DOUBLE, string("double"), 8, -1));
	this->tabla.push_back(Tipo(VOID, string("void"), 0, -1));
}

void TablaTipos::printTT(string contexto){
    printf("Tabla de Tipos %s\n", contexto.c_str());
    vector<Tipo> TS = this -> tabla;
    for(auto & tipo : TS){
        printf("id: %d, nombre: %s, tamaño: %d, base: %d\n", 
            tipo.id, tipo.nombre.c_str(), tipo.tam, tipo.base);
    }
	printf("\n");
}