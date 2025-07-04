#pragma once
#include "RecursoBibliografico.h"

class revista : public RecursoBibliografico {
private:
	string ISSN;
	string clasificacion;
public:
	revista(const string& id, const string& titulo, const string& autor, const string& fecha, int valoracion, const string& ISSN, const string& clasificacion)
		: RecursoBibliografico(id,  titulo,  autor,  fecha,  valoracion) {
		this->ISSN = ISSN;
		this->clasificacion = clasificacion;
	}

	revista(const string& id, const string& titulo, const string& autor, const string& fecha, int valoracion, const string& ISSN, const string& clasificacion, int stock)
		: RecursoBibliografico(id, titulo, autor, fecha, valoracion) {
		this->ISSN = ISSN;
		this->clasificacion = clasificacion;
	}


	revista() : RecursoBibliografico() {
		this->ISSN = "";
		this->clasificacion = "";
	}

	string getId() const {
		return id;
	}

	string getISSN() const { return ISSN; }
	string getClasificacion() const { return clasificacion; }
	void setISSN(string ISSN) { this->ISSN = ISSN; }
	void setClasificacion(string clasificacion) { this->clasificacion = clasificacion; }	

	void mostrar() const override {
		cout << "=== REVISTA ===" << endl;
		cout << "ID: " << id << endl;
		cout << "Titulo: " << titulo << endl;
		cout << "Autor: " << autor << endl;
		cout << "Fecha: " << fecha << endl;
		cout << "Valoracion: " << valoracion << "/5" << endl;
		cout << "ISSN: " << ISSN << endl;
		cout << "Clasificacion: " << clasificacion << endl;
		cout << "=====================" << endl;
	}

	void mostrarprestamo() const override {
		cout << "=== REVISTA ===" << endl;
		cout << "ID: " << id << endl;
		cout << "Titulo: " << titulo << endl;
		cout << "Autor: " << autor << endl;
		cout << "Fecha: " << fecha << endl;
		cout << "Valoracion: " << valoracion << "/5" << endl;
		cout << "ISSN: " << ISSN << endl;
		cout << "Clasificacion: " << clasificacion << endl;
		cout << "=====================" << endl;
	}

};