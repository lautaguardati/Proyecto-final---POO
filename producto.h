#include <iostream>
#include <string>
using namespace std;

class Producto {
private:
	char nombre[50];
	int id;
	int stock;
	int precio;
public:
	string ObtenerNombre();
	int ObtenerID();
	int ObtenerStock();
	int ObtenerPrecio();
};
