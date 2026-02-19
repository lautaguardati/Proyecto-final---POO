#include <iostream>
#include "empresa.h"
#include "producto.h"
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <cstring>
using namespace std;


bool ExisteArchivo(const string& nombre) {
	ifstream archivo(nombre);
	return archivo.good();
}

void CargarDatosEnMemoria (vector<Empresa> &emp) {
	ifstream archivo("lista_prov.dat", ios::binary);
	if (!archivo.is_open()) {
		throw runtime_error("No se pudo abrir el archivo");
	}
	int idEmpresa;
	while (archivo.read((char*) &idEmpresa, sizeof(idEmpresa))) {
		char auxNombre[256] = {0};
		char auxCorreo[256] = {0};
		char auxTelefono[20] = {0};
		int CantidadProductos;
		
		archivo.read(auxNombre, sizeof(auxNombre));
		archivo.read(auxCorreo, sizeof(auxCorreo));
		archivo.read(auxTelefono, sizeof(auxTelefono));
		archivo.read((char*) &CantidadProductos, sizeof(CantidadProductos));
		
		string nombre = auxNombre;
		string correo = auxCorreo;
		string telefono = auxTelefono;
		
		Empresa nuevaEmpresa(idEmpresa, nombre, correo, telefono);
		
		for(int i=0;i<CantidadProductos;i++) {
			char auxNombreProd[256] = {0};
			int idProducto, stock, cantidadVendida;
			double precio;
			archivo.read(auxNombreProd, sizeof(auxNombreProd));
			archivo.read((char*) &idProducto, sizeof(idProducto));
			archivo.read((char*) &stock, sizeof(stock));
			archivo.read((char*) &precio, sizeof(precio));
			archivo.read((char*) &cantidadVendida, sizeof(cantidadVendida));
			
			string NombreProd = auxNombreProd;
			nuevaEmpresa.AgregarProducto(NombreProd, idProducto, stock, precio, cantidadVendida);
		}
		emp.push_back(nuevaEmpresa);
	}
	archivo.close();
}

void GuardarCambios(vector<Empresa> &empresas) {
	// Vamos a usar un guardado atómico. Usamos un archivo temporal para evitar perder
	// datos ante un imprevisto (corte de luz, apagado inesperado, etc).
	
	string archivoTemporal = "lista_prov.tmp";
	string archivoFinal = "lista_prov.dat";
	if (empresas.empty())
		throw runtime_error("No se puede guardar sin cargar los datos antes");
	
	ofstream archivo(archivoTemporal, ios::binary | ios::trunc);
	if (!archivo.is_open()) throw runtime_error("No se pudo crear el archivo temporal");
	
	for (Empresa &emp : empresas) {
		int id = emp.ObtenerID();
		
		string auxNombre = emp.ObtenerNombre();
		char Nombre[256] = {0};
		// Usamos Strncpy y "255" para evitar un desvortamiento si el nombre es
		// muy largo. Así se nos aseguramos el "\0" en la última posición [255].
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

		
		// Pasamos por referencia el vector así no lo copiamos entero
		vector<Producto> &productos = emp.ObtenerListaProductos();
		for(Producto &p : productos) { 
			string auxNombreProd = p.ObtenerNombre();
			char NombreProd[256] = {0};
			strncpy(NombreProd, auxNombreProd.c_str(), 255);
			
			int idProd = p.ObtenerID();
			int stockProd = p.ObtenerStock();
			double precioProd = p.ObtenerPrecio();
			
			archivo.write(NombreProd, sizeof(NombreProd));
			archivo.write((char*) &idProd, sizeof(idProd));
			archivo.write((char*) &stockProd, sizeof(stockProd));
			archivo.write((char*) &precioProd, sizeof(precioProd));
		}
		
	}
	
	if (archivo.fail())	{
		archivo.close();
		remove(archivoTemporal.c_str()); // Borramos el archivo temporal corrupto
		throw runtime_error("Error durante la escritura. No se modificaron los datos originales");
	}
	archivo.close();
	
	if (remove(archivoFinal.c_str()) != 0) { // Si falla borrar, puede ser porque no existía (primera vez).
		if(ExisteArchivo(archivoFinal)) {
			throw runtime_error("Error: no se puede borrar el archivo original");
		}
	}
	// Renombramos el archivo temporal y lo volvemos la base de datos
	if (rename(archivoTemporal.c_str(), archivoFinal.c_str()) != 0) {
		throw runtime_error("Error: se guardó el temporal pero no se pudo renombrar.");
	}
}
	
void MostrarEmpresa(vector<Empresa> &emp, int id = 0,const string &nombre="") {
	if (emp.empty()) {
		cout<<"No hay empresas cargadas.";
		return;
	}
	
	if (id != 0 || nombre != ""){
		int aux = -1;
		for(size_t i=0;i<emp.size();i++) { 
			if(emp[i].ObtenerNombre() == nombre || emp[i].ObtenerID() == id) {
				aux = i;
			}
		}
		if (aux == -1) {
			cout<<"No se encontró la empresa";
			return;
		}
		cout<<emp[aux].ObtenerID()<<": "<<emp[aux].ObtenerNombre()<<". Tel: "<<emp[aux].ObtenerTelefono()<<endl;
		cout<<"Correo: "<<emp[aux].ObtenerCorreo()<<endl<<"Cantidad de Productos: "<<emp[aux].ObtenerCantidadProductos()<<endl<<endl;
		cout<<endl<<endl;
		return;
	}
	for(size_t i=0;i<emp.size();i++) { 
		cout<<emp[i].ObtenerID()<<": "<<emp[i].ObtenerNombre()<<". Tel: "<<emp[i].ObtenerTelefono();
		cout<<endl;
		cout<<"Correo: "<<emp[i].ObtenerCorreo()<<endl<<"Cantidad de Productos: "<<emp[i].ObtenerCantidadProductos()<<endl<<endl;
		cout<<endl<<endl;
	}
}

int main() {
	vector<Empresa> empresas;
	string ruta = "lista_prov.dat";
	
	// Try-catch para la carga
	try {
		if (ExisteArchivo(ruta)) {
			cout<<"Cargando base de datos..."<< endl;
			CargarDatosEnMemoria(empresas);
		} else {
			cout<<"No se encontró base de datos. Se iniciará vacío y se creará una nueva al guardar"<<endl;
		}
	} catch (const exception &e) {
		cerr << "Error al cargar: "<< e.what()<<endl;
	}
	
	MostrarEmpresa(empresas);
	
	// Try-catch para el guardado
	try {
		GuardarCambios(empresas);
		cout<<"Guardado exitoso."<<endl;
	} catch (const exception &e) {
		cerr<<"Error al guardar: "<<e.what()<<endl;
	}
	
	return 0;
}

