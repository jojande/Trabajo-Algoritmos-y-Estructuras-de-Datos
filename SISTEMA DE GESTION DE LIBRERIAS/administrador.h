#pragma once
#include "usuario.h"

class Administrador : public Usuario {
private:
public:
	Administrador(const string id, const string nombre, const string contrasenia) : Usuario(id, nombre, contrasenia) {}
	
	void menuAdministrador() {
		cout << "Opciones de administrador:" << endl;
		cout << "1. Gestionar Usuarios: " << endl;
		cout << "2. Mostrar Arbol de Multas" << endl;
		cout << "0. Salir: " << endl;
	}


	void menuGestionUsuarios() {
		cout << "Gestion de Usuarios :" << endl;
		cout << "1. Agregar Usuario: " << endl;
		cout << "2. Mostrar Usuario: " << endl;
		cout << "3. Eliminar Usuario: " << endl;
		cout << "4. Modificar Usuario: " << endl;
		cout << "0. Salir: " << endl;
	}
};