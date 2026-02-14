#include <iostream>
#include "empresa.h"
#include "producto.h"
#include <fstream>
using namespace std;

bool revisarExistenciaArchivo (string direc) {
	ifstream archivo (direc, ios::binary);
	return archivo.good();
}





int main() {
	
	if (revisarExistenciaArchivo("lista_prov.dat")) {
		ofstream cargaInicial("lista_prov.dat", ios::binary);
	} else {
		ofstream crear("lista_prov.dat", ios::binary);
	}
	
	ifstream cargaInicial("lista_prov.dat", ios::binary | ios::in);
	
	if (!cargaInicial.is_open()) {
		throw runtime_error("No se pudo abrir el archivo");
	}


	
	
	
	
	
	return 0;
}

