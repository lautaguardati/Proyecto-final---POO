#pragma once
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
	Empresa(int idEmpresa, const std::string &nombre, const std::string &correo, const std::string &telefono) : m_idEmpresa(idEmpresa),
		m_nombre(nombre), m_correo(correo), m_telefono(telefono){}
	int ObtenerID(){return m_idEmpresa;};
	const std::string& ObtenerNombre() const {return m_nombre;};
	const std::string& ObtenerCorreo() const {return m_correo;};
	const std::string& ObtenerTelefono() const {return m_telefono;};
	int ObtenerCantidadProductos();
	std::vector<Producto>& ObtenerListaProductos() { return Productos; };
	
	bool AgregarProducto(const std::string &nombre, int id, int stock, double precio, int cantidadVendida);
	bool QuitarProducto(int id);
	bool VenderProducto(int id);
	bool ExisteProducto(const std::string &nombre, int id);
	Producto* BuscarProducto(const std::string &nombre, int id);
};

inline int Empresa::ObtenerCantidadProductos() {
	return Productos.size();
}

inline bool Empresa::AgregarProducto(const std::string &nombre, int id, int stock, double precio, int cantidadVendida) {
	if (ExisteProducto(nombre, id)) return false;
	
	Producto auxProd(nombre, id, stock, precio, cantidadVendida);
	Productos.push_back(auxProd);
	return true;
}

inline bool Empresa::ExisteProducto(const std::string &nombre, int id) {
	for (Producto &p : Productos) {
		if (p.ObtenerID() == id || p.ObtenerNombre() == nombre) return true;
	}
	return false;
}

inline Producto* Empresa::BuscarProducto(const std::string &nombre = "", int id = 0) {
	for (auto &p : Productos) {
		if ((id != 0 && p.ObtenerID() == id) || (nombre != "" && p.ObtenerNombre() == nombre)) {
			return &p;
		}
	}
	return nullptr;
}

inline bool Empresa::QuitarProducto(int id) {
	for(size_t i=0;i<Productos.size();i++) { 
		if (id == Productos[i].ObtenerID()) {
			Productos.erase(Productos.begin() + i);
			return true;
		}
	}
	return false;
}

inline bool Empresa::VenderProducto(int id) {
	for(Producto &p : Productos) { 
		if (id == p.ObtenerID()) {
			p.ActualizarStock((p.ObtenerStock()-1));
			p.VenderProducto();
			return true;
		}
	}
	return false;
}





