#include <iostream>
#include "empresa.h"
#include "producto.h"
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <cstring>
using namespace std;

// Función simplificada para verificar archivo
bool ExisteArchivo(const string& nombre) {
	ifstream archivo(nombre);
	return archivo.good();
}

void CargarDatosEnMemoria (vector<Empresa> &emp) {
	fstream archivo("lista_prov.dat", ios::binary | ios::in);
	if (!archivo.is_open()) {
		throw runtime_error("No se pudo abrir el archivo");
	}
	while (true) {
		int idEmpresa;
		char auxNombre[256] = {0};
		char auxCorreo[256] = {0};
		char auxTelefono[20] = {0};
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
			char auxNombreProd[256] = {0};
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
	if (empresas.empty())
		throw runtime_error("No se puede guardar sin cargar los datos antes");
	
	ofstream archivo("lista_prov.dat", ios::binary | ios::trunc);
	if (!archivo.is_open()) throw runtime_error("No se pudo abrir el archivo");
	for (Empresa &emp : empresas) {
		int id = emp.ObtenerID();
		
		string auxNombre = emp.ObtenerNombre();
		char Nombre[256] = {0};
		// Usamos Strncpy para evitar un desvortamiento si el nombre es muy largo
		strncpy(Nombre, auxNombre.c_str(), 255);
		
		string auxCorreo = emp.ObtenerCorreo();
		char Correo[256] = {0};
		strncpy(Correo, auxCorreo.c_str(), 255);
		
		string auxTelefono = emp.ObtenerTelefono();
		char Telefono[20] = {0};
		strncpy(Telefono, auxTelefono.c_str(), 19);
		
		int cantidadProductos = emp.ObtenerCantidadProductos(); 

		archivo.write((char*) &id, sizeof(id));
		archivo.write(Nombre, sizeof(Nombre));
		archivo.write(Correo, sizeof(Correo));
		archivo.write(Telefono, sizeof(Telefono));
		archivo.write((char*) &cantidadProductos, sizeof(cantidadProductos));

		vector<Producto> &productos = emp.ObtenerListaProductos();
		for(Producto &p : productos) { 
			string auxNombreProd = p.ObtenerNombre();
			char NombreProd[256] = {0};
			strncpy(NombreProd, auxNombreProd.c_str(), 255);
			
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
		cout<<endl<<i<<endl;
	}
}
	
	
	
	
	
int main() {
	vector<Empresa> empresas;
	
	string ruta = "lista_prov.dat";
	if (ExisteArchivo(ruta)) {
		cout << "Cargando base de datos..." << endl;
		CargarDatosEnMemoria(empresas);
	} else {
		cout << "No se encontró base de datos. Se creará una nueva al guardar." << endl;
	}
	
	
	CargarDatosEnMemoria(empresas);
	//Producto p = empresas[0].ObtenerPr
	//cout<<empresas[0]
	
	MostrarEmpresa(empresas);
	
	return 0;
}

