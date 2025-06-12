#pragma once
#include "EstructurasDatos.h"
#include "lector.h"

class Prestamo {
private:
	string id; // codigo o ID
	Lector* solicitante; //ID del lector solicitante
	string fecha;
	string estado;

public:

	Prestamo(string c, Lector* l, string f) : id(c), solicitante(l), fecha(f), estado("Pendiete") {};

	void mostrar(){
		std::cout << "Código préstamo: " << id << "\n";
		std::cout << "Solicitado por: " << solicitante->getId() << "\n";
		std::cout << "Fecha: " << fecha << "\n";
		std::cout << "Estado: " << estado << "\n";
	}
			
};
