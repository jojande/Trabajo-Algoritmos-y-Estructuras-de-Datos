#pragma once
#include "RecursoBibliografico.h"

class libro : public RecursoBibliografico {
private:
	string genero;
	string editorial;
public:
	libro(const string& id, const string& titulo, const string& autor, const string& fecha, int valoracion, const string& genero, const string& editorial)
		: RecursoBibliografico(id, titulo, autor, fecha, valoracion) {
		this->genero = genero;
		this->editorial = editorial;
	}

	libro(const string& id, const string& titulo, const string& autor, const string& fecha, int valoracion, const string& genero, const string& editorial, int stock)
		: RecursoBibliografico(id, titulo, autor, fecha, valoracion) {
		this->genero = genero;
		this->editorial = editorial;
	}


	libro() : RecursoBibliografico() {
		this->genero = "";
		this->editorial = "";
	}

	libro(const libro& l)
		: RecursoBibliografico(l.getId(), l.getTitulo(), l.getAutor(), l.getFecha(), l.getValoracion()) {
		this->genero = l.genero;
		this->editorial = l.editorial;
		this->setStock(l.getStock());
	}

	string getId() const {
		return id;
	}


	bool esIgualContenido(const libro& otro) const {
		return titulo == otro.titulo &&
			autor == otro.autor &&
			fecha == otro.fecha &&
			genero == otro.genero &&
			editorial == otro.editorial;

	}


	string getGenero() const { return genero; }
	string getEditorial() const { return editorial; }	
	void setGenero(string genero) { this->genero = genero; }	
	void setEditorial(string editorial) { this->editorial = editorial; }	

	void mostrar() const override {
		cout << "=== LIBRO ===" << endl;
		cout << "ID: " << id << endl;
		cout << "Titulo: " << titulo << endl;
		cout << "Autor: " << autor << endl;
		cout << "Fecha: " << fecha << endl;
		cout << "Valoracion: " << valoracion << "/5 estrellas" << endl;
		cout << "Genero: " << genero << endl;
		cout << "Editorial: " << editorial << endl;
		cout << "Stock: " << stock << endl;
		cout << "=====================" << endl;
	}

	void mostrarprestamo() const override {
		cout << "ID: " << id << endl;
		cout << "Titulo: " << titulo << endl;
		cout << "Autor: " << autor << endl;
		cout << "Fecha: " << fecha << endl;
		cout << "Valoracion: " << valoracion << "/5 estrellas" << endl;
		cout << "Genero: " << genero << endl;
		cout << "Editorial: " << editorial << endl;
		cout << "=====================" << endl;
	}
	
};