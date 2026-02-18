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
	std::vector<Producto> Productos;
public:
	Empresa(int idEmpresa, const std::string &nombre, const std::string &correo, const std::string &telefono, int cantidadProductos) : m_idEmpresa(idEmpresa),
		m_nombre(nombre), m_correo(correo), m_telefono(telefono){}
	int ObtenerID(){return m_idEmpresa;};
	std::string ObtenerNombre(){return m_nombre;};
	std::string ObtenerCorreo(){return m_correo;};
	std::string ObtenerTelefono(){return m_telefono;};
	int ObtenerCantidadProductos();
	std::vector<Producto>& ObtenerListaProductos() { return Productos; };
	
	bool AgregarProducto(const std::string &nombre, int id, int stock, float precio);
	bool QuitarProducto();
	bool VenderProducto();
	bool ExisteProducto(const std::string &nombre, int id);
	Producto* BuscarProducto(int pos, const std::string &nombre, int id);
};

inline int Empresa::ObtenerCantidadProductos() {
	return Productos.size();
}

inline bool Empresa::AgregarProducto(const std::string &nombre, int id, int stock, float precio) {
	if (ExisteProducto(nombre, id)) return false;
	
	Producto auxProd(nombre, id, stock, precio);
	Productos.push_back(auxProd);
	return true;
}

inline bool Empresa::ExisteProducto(const std::string &nombre, int id) {
	for (Producto &p : Productos) {
		if (p.ObtenerID() == id || p.ObtenerNombre() == nombre) return true;
	}
	return false;
}

inline Producto* Empresa::BuscarProducto(int pos, const std::string &nombre = "", int id = 0) {
	for (auto &p : Productos) {
		if (p.ObtenerID() == id || p.ObtenerNombre() == nombre) {
			return &p;
		}
	}
	return nullptr;
}






