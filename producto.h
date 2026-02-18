#include <iostream>
#include <string>
#pragma once

class Producto {
private:
	std::string m_nombre;
	int m_id;
	int m_stock;
	double m_precio;
public:
	Producto(const std::string &nombre, int id, int stock, double precio) : m_nombre(nombre), m_id(id), m_stock(stock),
		m_precio(precio){}
	const std::string& ObtenerNombre()const{return m_nombre;};
	int ObtenerID(){return m_id;};
	int ObtenerStock(){return m_stock;};
	double ObtenerPrecio(){return m_precio;};
	void ActualizarStock(int cantidad) {m_stock = cantidad;};
};
