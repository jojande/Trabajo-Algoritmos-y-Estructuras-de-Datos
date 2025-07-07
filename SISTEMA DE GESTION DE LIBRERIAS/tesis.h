#pragma once
#include "RecursoBibliografico.h"

class tesis : public RecursoBibliografico {
private:
	string universidad;
	string pais;
public:
	tesis(const string& id, const string& titulo, const string& autor, const string& fecha, int valoracion, const string& universidad, const string& pais)
		: RecursoBibliografico(id, titulo, autor, fecha, valoracion) {
		this->universidad = universidad;
		this->pais = pais;
	}

	tesis(const string& id, const string& titulo, const string& autor, const string& fecha, int valoracion, const string& universidad, const string& pais, int stock)
		: RecursoBibliografico(id, titulo, autor, fecha, valoracion) {
		this->universidad = universidad;
		this->pais = pais;
	}

	tesis() : RecursoBibliografico() {
		this->universidad = "";
		this->pais = "";
	}

	tesis(const tesis& t)
		: RecursoBibliografico(t.getId(), t.getTitulo(), t.getAutor(), t.getFecha(), t.getValoracion()) {
		this->universidad = t.getUniversidad(); 
		this->setStock(t.getStock());
	}

	string getUniversidad() const { return universidad; }
	string getPais() const { return pais; }
	
    void setUniversidad(string universidad) { this->universidad = universidad; }
	void setPais(string pais) { this->pais = pais; }

	bool esIgualContenido(const tesis& otra) const {
		return titulo == otra.titulo &&
			autor == otra.autor &&
			fecha == otra.fecha &&
			valoracion == otra.valoracion &&
			universidad == otra.universidad &&
			pais == otra.pais;
	}


	void mostrar() const override {
		cout << "=== TESIS ===" << endl;
		cout << "ID: " << id << endl;
		cout << "Titulo: " << titulo << endl;
		cout << "Autor: " << autor << endl;
		cout << "Fecha: " << fecha << endl;
		cout << "Valoracion: " << valoracion << "/5" << endl;
		cout << "Universidad: " << universidad << endl;
		cout << "Pais: " << pais << endl;
		cout << "Stock: " << stock << endl;
		cout << "=====================" << endl;
	}


	void mostrarprestamo() const override {
		cout << "=== TESIS ===" << endl;
		cout << "ID: " << id << endl;
		cout << "Titulo: " << titulo << endl;
		cout << "Autor: " << autor << endl;
		cout << "Fecha: " << fecha << endl;
		cout << "Valoracion: " << valoracion << "/5" << endl;
		cout << "Universidad: " << universidad << endl;
		cout << "Pais: " << pais << endl;
		cout << "=====================" << endl;
	}


};