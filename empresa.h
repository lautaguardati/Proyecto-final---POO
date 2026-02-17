#include <iostream>
#include <vector>
#include <string>
#include "producto.h"

class Empresa {
private:
	int m_idEmpresa;
	std::string m_nombre;
	std::string m_correo;
	std::string m_telefono;
	int m_cantidadProductos;
	std::vector<Producto> Productos;
public:
	Empresa(int idEmpresa, const std::string &nombre, const std::string &correo, const std::string &telefono, int cantidadProductos) : m_idEmpresa(idEmpresa),
		m_nombre(nombre), m_correo(correo), m_telefono(telefono), m_cantidadProductos(cantidadProductos){}
	bool AgregarProducto(const std::string &nombre, int id, int stock, float precio);
	bool QuitarProducto();
	bool VenderProducto();
	bool BuscarProducto(const std::string &nombre, int id);
	int ObtenerID(){return m_idEmpresa;};
	std::string ObtenerNombre(){return m_nombre;};
	std::string ObtenerCorreo(){return m_correo;};
	std::string ObtenerTelefono(){return m_telefono;};
	int ObtenerCantidadProductos(){return m_cantidadProductos;};
	std::vector<Producto> ObtenerListaProductos(){return Productos;};
};

bool Empresa::AgregarProducto(const std::string &nombre, int id, int stock, float precio) {
	if (BuscarProducto(nombre, id)) return false;
	
	Producto auxProd(nombre, id, stock, precio);
	Productos.push_back(auxProd);
	return true;
}

bool Empresa::BuscarProducto(const std::string &nombre, int id) {
	for (Producto p : Productos) {
		if (p.ObtenerID() == id || p.ObtenerNombre() == nombre) return true;
	}
	return false;
}
