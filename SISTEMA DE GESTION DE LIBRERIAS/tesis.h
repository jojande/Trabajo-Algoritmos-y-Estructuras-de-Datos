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

	tesis() : RecursoBibliografico() {
		this->universidad = "";
		this->pais = "";
	}

	string getUniversidad() const { return universidad; }
	string getPais() const { return pais; }
	
    void setUniversidad(string universidad) { this->universidad = universidad; }
	void setPais(string pais) { this->pais = pais; }

	void mostrar() const override {
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