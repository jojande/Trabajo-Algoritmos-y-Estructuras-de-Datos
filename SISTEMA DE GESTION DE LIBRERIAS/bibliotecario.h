#pragma once
#include "usuario.h"

class Bibliotecario : public Usuario {
private:
public:
	Bibliotecario(const string id, const string nombre, const string contrasenia) : Usuario(id, nombre, contrasenia) {}

	void menuBibliotecario() {
		cout << "Opciones de Bibliotecario:" << endl;
		cout << "1. Mostrar prestamos solicitados" << endl;
		cout << "2. Administrar prestamo" << endl;
		cout << "3. Gestionar recursos bibliograficos" << endl;
		cout << "4. Ver tabla de pedidos ordenados por fecha" << endl;
		cout << "5. Ver tabla de vencimientos ordenados " << endl;
		cout << "6. Mostrar el proximo en vencer" << endl;
		cout << "7. Mostrar todos en proximo en vencer" << endl;
		cout << "0. Salir: " << endl;
	}

	void menuGestionarRecursosBibliograficos() {
		cout << "Gestion de Recursos Bibliograficos:" << endl;
		cout << "1. Agregar Recurso Bibliografico: " << endl;
		cout << "2. Mostrar Recurso Bibliografico: " << endl;
		cout << "3. Eliminar Recurso Bibliografico: " << endl;
		cout << "4. Modificar Recurso Bibliografico: " << endl;
		cout << "5. Ordenar Recurso Bibliografico por valoracion (Mergesort)" << endl;
		cout << "6. Ordenar Recurso Bibliografico por valoracion (Quickshort)" << endl;
		cout << "7. Ordenar Recurso Bibliografico por anio de publicacion (Quickshort)" << endl;
		cout << "0. Salir: " << endl;
	}
}; 


