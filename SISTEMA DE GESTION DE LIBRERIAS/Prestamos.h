#pragma once
#include <memory>
#include "EstructurasDatos.h"
#include "RecursoBibliografico.h"
#include "lector.h"
#include "libro.h"
#include "tesis.h"
#include "revista.h"

class Prestamo {
private:
	string id; 
	Lector* solicitante; 
	RecursoBibliografico* recurso; // Puede ser libro, revista o tesis
	string fecha;
	string estado;

public:

	Prestamo(const string id, const string& fecha, Lector* solicitante, RecursoBibliografico* recurso, const string& estado = "Pendiente") {
		this->id = id;
		this->fecha = fecha;
		this->solicitante = solicitante;
		this->recurso = recurso;
		this->estado = estado;
	}

	void detallesPrestamo() {
		cout << "ID prestamo: " << id << "\n";
		cout << "Solicitado por: " << solicitante->getId() << "\n";
		cout << "Fecha: " << fecha << "\n";
		cout << "Estado: " << estado << "\n";
		cout << "----Detalles----\n";
		recurso->mostrar();
	}

	string getId() const { return id; }
	string getFecha() const { return fecha; }
	Lector* getSolicitante() const { return solicitante; }
	RecursoBibliografico* getRecurso() const { return recurso; }
	string getEstado() const { return estado; }

			
};
