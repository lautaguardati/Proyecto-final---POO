#include <iostream>
#include "empresa.h"
#include "producto.h"
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <cstring>
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
		return 3; 
	}
}

void CargarDatosEnMemoria (vector<Empresa> &emp) {
	fstream archivo("lista_prov.dat", ios::binary | ios::in);
	if (!archivo.is_open()) {
		throw runtime_error("No se pudo abrir el archivo");
	}
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
		
		Empresa nuevaEmpresa(idEmpresa, nombre, correo, telefono, CantidadProductos);
		
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
		emp.push_back(nuevaEmpresa);
	}
	archivo.close();
}

void GuardarCambios(vector<Empresa> &empresas) {
	if (empresas.size() == 0)
		throw runtime_error("No se puede guardar sin cargar los datos antes");
	
	ofstream archivo("lista_prov.dat", ios::binary | ios::trunc);
	
	for (Empresa &emp : empresas) {
		int id = emp.ObtenerID();
		
		string auxNombre = emp.ObtenerNombre();
		char Nombre[256];
		strcpy(Nombre, auxNombre.c_str());
		
		string auxCorreo = emp.ObtenerCorreo();
		char Correo[256];
		strcpy(Correo, auxCorreo.c_str());
		
		string auxTelefono = emp.ObtenerTelefono();
		char Telefono[20];
		strcpy(Telefono, auxTelefono.c_str());
		
		int cantidadProductos = emp.ObtenerCantidadProductos(); 

		archivo.write((char*) &id, sizeof(id));
		archivo.write(Nombre, sizeof(Nombre));
		archivo.write(Correo, sizeof(Correo));
		archivo.write(Telefono, sizeof(Telefono));
		archivo.write((char*) &cantidadProductos, sizeof(cantidadProductos));
		
		vector<Producto> productos = emp.ObtenerListaProductos();
		for(Producto &p : productos) { 
			string auxNombreProd = p.ObtenerNombre();
			char NombreProd[256];
			strcpy(NombreProd, auxNombreProd.c_str());
			
			int idProd = p.ObtenerID();
			int stockProd = p.ObtenerStock();
			float precioProd = p.ObtenerPrecio();
			
			archivo.write(NombreProd, sizeof(NombreProd));
			archivo.write((char*) &idProd, sizeof(idProd));
			archivo.write((char*) &stockProd, sizeof(stockProd));
			archivo.write((char*) &precioProd, sizeof(precioProd));
		}
		
	}
	archivo.close();
}
	
void MostrarEmpresa(vector<Empresa> &emp, int id = 0,const string &nombre="") {
	if (id != 0 || nombre != ""){
		
		
		//return;
	}
	for(int i=0;i<emp.size();i++) { 
		cout<<emp[i].ObtenerID()<<": "<<emp[i].ObtenerNombre()<<". Tel: "<<emp[i].ObtenerTelefono();
		cout<<endl;
		cout<<"Correo: "<<emp[i].ObtenerCorreo()<<endl<<"Cantidad de Productos: "<<emp[i].ObtenerCantidadProductos()<<endl<<endl;
	}
}
	
	
	
	
	
int main() {
	int EstadoArchivo = RevisarEstadoArchivo("lista_prov.dat");
	// 0 = existe y funciona;
	// 1 = no existe y 2 = no funciona
	if (EstadoArchivo) {
		switch (EstadoArchivo) {
		case 1: {
			ofstream crear("lista_prov.dat", ios::binary);
			crear.close();
			}
		case 2: 
			throw runtime_error("Error: No se tiene permiso para abrir el archivo");
		case 3:
			throw runtime_error("Error: el archivo no pudo abrirse.");
		}
	}
	
	vector<Empresa> empresas;
	
	CargarDatosEnMemoria(empresas);
	
	MostrarEmpresa(empresas);
	
	
	return 0;
}

