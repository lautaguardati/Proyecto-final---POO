#include <iostream>
#include <vector>
#include <string>
#include "producto.h"
using namespace std;

class Empresa {
private:
	string m_nombre;
	string m_correo;
	int m_telefono;
	vector<Producto> Productos;
public:
	Empresa(string nombre, string correo, int telefono) : m_nombre(nombre), m_correo(correo),
		m_telefono(telefono){}
	bool AgregarProducto();
	bool QuitarProducto();
	bool VendeProducto();
	Producto BuscarProducto(string nombre, int id);
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
