#include <iostream>
#include "empresa.h"
#include "producto.h"
#include <fstream>
#include <cstdio>
#include <cerrno>
using namespace std;

// 	Usamos esta función para revisar si el archivo no existe para crear uno
// o es si existe pero no abre por otro problema.
int RevisarEstadoArchivo (string direc) {
	// Intentamos abrir en modo lectura binaria ("rb")
	FILE* file = fopen(direc.c_str(), "rb");
	
	if (file != NULL) {
		// Se abrió correctamente
		fclose(file);
		return 0; // Éxito
	}
	
	// Si llegamos aquí, file es NULL. Revisamos errno.
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

void CargarDatosEnMemoria (fstream &archivo, vector<Empresa> &emp) {
	if (archivo.peek() == EOF) return;
	while (true) {
		int idEmpresa;
		char auxNombre[256];
		char auxCorreo[256];
		char auxTelefono[20];
		int CantidadProductos;
		
		archivo.read((char*) &idEmpresa, sizeof(idEmpresa));
		// 	El .eof() aparentemente da "true" cuando se hace una lectura fallida de un archivo.
		// Por eso lo ponemos después de leer el id. Si falla se corta la lectura del archivo y
		// no se agregan empresas "basura" por error.
		if (archivo.eof()) break;
		
		archivo.read(auxNombre, sizeof(auxNombre));
		archivo.read(auxCorreo, sizeof(auxCorreo));
		archivo.read(auxTelefono, sizeof(auxTelefono));
		archivo.read((char*) &CantidadProductos, sizeof(CantidadProductos));
		
		string nombre = auxNombre;
		string correo = auxCorreo;
		string telefono = auxTelefono;
		
		Empresa nuevaEmpresa(idEmpresa, nombre, correo, telefono);
		
		for(int i=0;i<CantidadProductos;i++) {
			char auxNombreProd[256];
			int idProducto, stock;
			float precio;
			archivo.read(auxNombreProd, sizeof(auxNombreProd));
			archivo.read((char*) &idProducto, sizeof(idProducto));
			archivo.read((char*) &stock, sizeof(stock));
			archivo.read((char*) &precio, sizeof(precio));
			
			string NombreProd = auxNombreProd;
			nuevaEmpresa.AgregarProducto(NombreProd, idProducto, stock, precio);
		}
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
	
	vector<Empresa> empresas;
	CargarDatosEnMemoria(CargaInicial, empresas);
	CargaInicial.close();
	
	return 0;
}

