#pragma once
#include <iostream>
#include <string>


class Producto {
private:
	std::string m_nombre;
	int m_id;
	int m_stock;
	double m_precio;
	int m_cantidadVendida;
public:
	Producto(const std::string &nombre, int id, int stock, double precio, int cantidadVendida) : m_nombre(nombre), m_id(id), m_stock(stock),
		m_precio(precio), m_cantidadVendida(cantidadVendida){}
	const std::string& ObtenerNombre()const{return m_nombre;};
	int ObtenerID(){return m_id;};
	int ObtenerStock(){return m_stock;};
	double ObtenerPrecio(){return m_precio;};
	int ObtenerCantidadVentas() {return m_cantidadVendida;};
	void ActualizarStock(int cantidad) {m_stock = cantidad;};
	void ActualizarPrecio(int cantidad) {m_precio = cantidad;};
	void VenderProducto(int cantidad) {m_cantidadVendida+= cantidad;};
};
