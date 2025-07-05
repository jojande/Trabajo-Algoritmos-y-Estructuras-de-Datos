#pragma once
#include "EstructurasDatos.h"
#include "RecursoBibliografico.h"
#include "lector.h"
#include "libro.h"
#include "tesis.h"
#include "revista.h"
#include "Fecha.h"

class Prestamo {
private:
	string id; 
	Lector* solicitante; 
	RecursoBibliografico* recurso; // Puede ser libro, revista o tesis
	string fecha;
	string estado;
	Fecha fechaVencimiento;

public:

	Prestamo(const string id, const string& fecha, Lector* solicitante, RecursoBibliografico* recurso, const string& estado = "Pendiente") {
		this->id = id;
		this->fecha = fecha;
		this->solicitante = solicitante;
		this->recurso = recurso;
		this->estado = estado;
		int dias = 5 + rand() % 10;
		this->fechaVencimiento = Fecha(fecha); 
		this->fechaVencimiento.sumarDias(dias);   
	}

	bool operator<(const Prestamo& otro) const {
		return this->fechaVencimiento < otro.fechaVencimiento;  
	}

	void detallesPrestamo() {
		cout << "ID prestamo: " << id << "\n";
		cout << "Solicitado por: " << solicitante->getId() << "\n";
		cout << "Nombre: " << solicitante->getNombre() << "\n";
		cout << "Fecha de prestamo: " << fecha << "\n";
		cout << "Fecha de vencimiento: " << fechaVencimiento.toString() << "\n";
		cout << "Estado: " << estado << "\n";
		cout << "----Detalles----\n";
		recurso->mostrarprestamo();
	}

	string getId() const { return id; }
	string getFecha() const { return fecha; }
	Lector* getSolicitante() const { return solicitante; }
	RecursoBibliografico* getRecurso() const { return recurso; }
	string getEstado() const { return estado; }
	Fecha getFechaVencimiento() const { return fechaVencimiento; }

	void setEstado(const string& nuevoEstado) {
		estado = nuevoEstado;
	}
	void setFechaVencimiento(const Fecha& nuevaFecha) {
		fechaVencimiento = nuevaFecha;
	}
};
