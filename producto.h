#include <iostream>
#include <string>
#pragma once
using namespace std;

class Producto {
private:
	string m_nombre;
	int m_id;
	int m_stock;
	float m_precio;
public:
	Producto(string nombre, int id, int stock, float precio) : m_nombre(nombre), m_id(id), m_stock(stock),
		m_precio(precio){}
	string ObtenerNombre();
	int ObtenerID();
	int ObtenerStock();
	int ObtenerPrecio();
};
