#pragma once
#include "usuario.h"

class Bibliotecario : public Usuario {
private:
public:
	Bibliotecario(string nombre, string contrasenia) : Usuario(nombre, contrasenia) {}

	void menuBibliotecario() {
		cout << "Opciones de Bibliotecario:" << endl;
		cout << "Mostrar prestamos solicitados" << endl;
		cout << "Confirmar prestamo" << endl;
		cout << "Denegar prestamo" << endl;
		cout << "0. Salir: " << endl;
	}
}; 
