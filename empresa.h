#include <iostream>
#include <vector>
#include <string>
#include "producto.h"
using namespace std;

class Empresa {
private:
	int m_idEmpresa;
	string m_nombre;
	string m_correo;
	string m_telefono;
	int m_cantidadProductos;
	vector<Producto> Productos;
public:
	Empresa(int idEmpresa, const string &nombre, const string &correo, const string &telefono, int cantidadProductos) : m_idEmpresa(idEmpresa),
		m_nombre(nombre), m_correo(correo), m_telefono(telefono), m_cantidadProductos(cantidadProductos){}
	bool AgregarProducto(const string &nombre, int id, int stock, float precio);
	bool QuitarProducto();
	bool VenderProducto();
	bool BuscarProducto(const string &nombre, int id);
	int ObtenerID(){return m_idEmpresa;};
	string ObtenerNombre(){return m_nombre;};
	string ObtenerCorreo(){return m_correo;};
	string ObtenerTelefono(){return m_telefono;};
	int ObtenerCantidadProductos(){return m_cantidadProductos;};
	vector<Producto> ObtenerListaProductos(){return Productos;};
};

bool Empresa::AgregarProducto(const string &nombre, int id, int stock, float precio) {
	if (BuscarProducto(nombre, id)) return false;
	
	Producto auxProd(nombre, id, stock, precio);
	Productos.push_back(auxProd);
	return true;
}

bool Empresa::BuscarProducto(const string &nombre, int id) {
	for (Producto p : Productos) {
		if (p.ObtenerID() == id || p.ObtenerNombre() == nombre) return true;
	}
	return false;
}
