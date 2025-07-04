#pragma once
#include "usuario.h"

class Bibliotecario : public Usuario {
private:
public:
	Bibliotecario(const string id, const string nombre, const string contrasenia) : Usuario(id, nombre, contrasenia) {}

	void menuBibliotecario() {
		cout << "Opciones de Bibliotecario:" << endl;
		cout << "1. Mostrar prestamos solicitados" << endl;
		cout << "2. Confirmar prestamo" << endl;
		cout << "3. Denegar prestamo" << endl;
		cout << "4. Ver tabla de vencimientos ordenados" << endl;
		cout << "5. Mostrar el proximo en vencer" << endl;
		cout << "6. Mostrar todos en proximo en vencer" << endl;
		cout << "0. Salir: " << endl;
	}
}; 
