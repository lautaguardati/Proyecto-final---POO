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
