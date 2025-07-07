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

	revista(const revista& r)
		: RecursoBibliografico(r.getId(), r.getTitulo(), r.getAutor(), r.getFecha(), r.getValoracion()) {
		this->setStock(r.getStock());
	}

	revista() : RecursoBibliografico() {
		this->ISSN = "";
		this->clasificacion = "";
	}

	string getId() const {
		return id;
	}
	bool esIgualContenido(const revista& otra) const {
		return titulo == otra.titulo &&
			autor == otra.autor &&
			fecha == otra.fecha &&
			valoracion == otra.valoracion &&
			ISSN == otra.ISSN &&
			clasificacion == otra.clasificacion;
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
		cout << "Stock: " << stock << endl;
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