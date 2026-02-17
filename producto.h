#include <iostream>
#include <string>
#pragma once

class Producto {
private:
	std::string m_nombre;
	int m_id;
	int m_stock;
	float m_precio;
public:
	Producto(const std::string &nombre, int id, int stock, float precio) : m_nombre(nombre), m_id(id), m_stock(stock),
		m_precio(precio){}
	std::string ObtenerNombre(){return m_nombre;};
	int ObtenerID(){return m_id;};
	int ObtenerStock(){return m_stock;};
	int ObtenerPrecio(){return m_precio;};
};
