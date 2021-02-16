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

int Tipo::maximo(int tipo1, int tipo2) {
	if (tipo1 == tipo2)
		return tipo1;

	if (tipo1 == 1005 && tipo2 == 1006 || tipo1 == 1006 && tipo2 == 1005)
		return 1;

	return -1;
}

bool Tipo::equivalentes(int tipo1, int tipo2) {
	if (tipo1 == tipo2)
		return true;

	if (tipo1 == 1005 && tipo2 == 1006 || tipo1 == 1006 && tipo2 == 1005)
		return true;

	return false;
}