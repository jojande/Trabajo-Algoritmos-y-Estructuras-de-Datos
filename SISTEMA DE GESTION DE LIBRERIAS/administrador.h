#pragma once
#include "usuario.h"

class Administrador : public Usuario {
private:
public:
	Administrador(const string id, const string nombre, const string contrasenia) : Usuario(id, nombre, contrasenia) {}
	
	void menuAdministrador() {
		cout << "Opciones de administrador:" << endl;
		cout << "1. Agregar Recurso Bibliografico: " << endl;
		cout << "2. Mostrar Recurso Bibliografico: " << endl;
		cout << "3. Eliminar Recurso Bibliografico: " << endl;
		cout << "4. Modificar Recurso Bibliografico: " << endl;
		cout << "0. Salir: " << endl;
	}
};