#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "producto.h"
using namespace std;

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
	int ObtenerID() const {return m_idEmpresa;};
	const std::string& ObtenerNombre() const {return m_nombre;};
	const std::string& ObtenerCorreo() const {return m_correo;};
	const std::string& ObtenerTelefono() const {return m_telefono;};
	int ObtenerCantidadProductos();
	std::vector<Producto>& ObtenerListaProductos(){ return Productos; };
	
	bool AgregarProducto(const std::string &nombre, int id, int stock, double precio, int cantidadVendida, double ventas);
	bool QuitarProducto(int id);
	bool VenderProducto(int id, int cant);
	bool ExisteProducto(const std::string &nombre, int id);
	Producto* BuscarProducto(const std::string &nombre, int id);
	void OrdenarProductoPorID();
	void OrdenarProductoPorNombre();
	void OrdenarEmpresaPorID(vector<Empresa> &emp);
	void OrdenarEmpresaPorNombre(vector<Empresa> &emp);
	double CalcularVentasTotales();
};

inline int Empresa::ObtenerCantidadProductos() {
	return Productos.size();
}

inline bool Empresa::AgregarProducto(const std::string &nombre, int id, int stock,
									 double precio, int cantidadVendida, double ventas) {
	
	if (ExisteProducto(nombre, id)) return false;
	
	Producto auxProd(nombre, id, stock, precio, cantidadVendida, ventas);
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

inline bool Empresa::VenderProducto(int id, int cant) {
	for(Producto &p : Productos) { 
		if (id == p.ObtenerID()) {
			p.ActualizarStock((p.ObtenerStock()-1));
			p.VenderProducto(cant);
			return true;
		}
	}
	return false;
}

inline void Empresa::OrdenarProductoPorID() {
	// No hace falta pasarle la función para ordenar porque ya le hicimos una sobrecarga
	// a la clase Producto.
	std::sort(Productos.begin(), Productos.end());
}

inline void Empresa::OrdenarProductoPorNombre() {
	// Acá si tenemos que usar una función lambda porque ya hicimos una sobrecarga para el <
	std::sort(Productos.begin(), Productos.end(), [](Producto &a, Producto &b){
		return a.ObtenerNombre() < b.ObtenerNombre();
	});
}

inline void Empresa::OrdenarEmpresaPorID(vector<Empresa> &emp){
	std::sort(emp.begin(), emp.end(), [](Empresa &a, Empresa &b) {
		return a.ObtenerID() < b.ObtenerID();
	});
}

inline void Empresa::OrdenarEmpresaPorNombre(vector<Empresa> &emp){
	std::sort(emp.begin(), emp.end(), [](Empresa &a, Empresa &b) {
		return a.ObtenerNombre() < b.ObtenerNombre();
	});
}

inline double Empresa::CalcularVentasTotales() {
	double aux = 0;
	for (Producto &p : Productos) {
		aux += p.ObtenerVentas();
	}
	return aux;
}
