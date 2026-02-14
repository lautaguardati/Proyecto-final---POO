#include <iostream>
#include "empresa.h"
#include "producto.h"
#include <fstream>
#include <cstdio>
#include <cerrno>
using namespace std;

// 	Usamos esta funci�n para revisar si el archivo no existe para crear uno
// o es si existe pero no abre por otro problema.
int RevisarEstadoArchivo (string direc) {
	// Intentamos abrir en modo lectura binaria ("rb")
	FILE* file = fopen(direc.c_str(), "rb");
	
	if (file != NULL) {
		// Se abri� correctamente
		fclose(file);
		return 0; // �xito
	}
	
	// Si llegamos aqu�, file es NULL. Revisamos errno.
	switch (errno) {
	case ENOENT: // Error NO ENTry (No existe el archivo o directorio)
		return 1; 
	case EACCES: // Error ACCESs (Permiso denegado)
		return 2;
	default:
		// Otro error (disco lleno, demasiados archivos abiertos, etc.)
		return 2; 
	}
}





int main() {
	int EstadoArchivo = RevisarEstadoArchivo("lista_prov.dat");
	// 0 = funciona;
	// 1 = no existe y 2 = no funciona
	if (EstadoArchivo) {
		if (EstadoArchivo == 1) {
			ofstream crear("lista_prov.dat", ios::binary);
			crear.close();
		}
		if (EstadoArchivo == 2) {
			throw runtime_error("Error: el archivo no puede abrirse");
		}
	}

	fstream CargaInicial("lista_prov.dat", ios::binary | ios::in);
	if (!CargaInicial.is_open()) {
		throw runtime_error("No se pudo abrir el archivo");
	}
	
	
	return 0;
}

