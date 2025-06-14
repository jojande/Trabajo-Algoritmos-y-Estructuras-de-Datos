#pragma once
#include "Usuario.h"

class Lector : public Usuario {
private:
public:
	Lector(const string id, const string nombre, const string contrasenia) : Usuario( id, nombre, contrasenia) {}

	void menuLector() {
		cout << "Opciones de Usuario:" << endl;
		cout << "1. Buscar Recurso Bibliografico" << endl;
		cout << "2. Solicitar Prestamo" << endl;
		cout << "3. Ver Historial de Prestamos" << endl;
		cout << "0. Salir: " << endl;
	}

	
};
