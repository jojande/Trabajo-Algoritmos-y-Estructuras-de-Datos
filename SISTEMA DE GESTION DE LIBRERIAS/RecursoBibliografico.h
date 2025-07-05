#pragma once
#include <string>
#include <fstream>

using namespace std;

class RecursoBibliografico {
protected:
	string id;
	string titulo;
	string autor;
	string fecha;
	int valoracion;
	int stock;

public:
	RecursoBibliografico(const string& id, const string& titulo, const string& autor, const string& fecha, int valoracion) {
		this->id = id;
		this->titulo = titulo;
		this->autor = autor;
		this->fecha = fecha;
		this->valoracion = valoracion;
		this->stock = 0;
	}

	RecursoBibliografico(const string& id, const string& titulo, const string& autor, const string& fecha, int valoracion, int stock) {
		this->id = id;
		this->titulo = titulo;
		this->autor = autor;
		this->fecha = fecha;
		this->valoracion = valoracion;
		this->stock = stock;
	}


	RecursoBibliografico() {
		this->id = "";
		this->titulo = "";
		this->autor = "";
		this->fecha = "";
		this->valoracion = 0;
		this->stock = 0;
	}

	virtual ~RecursoBibliografico() {}
	virtual void mostrar() const = 0;

	virtual void mostrarprestamo() const = 0;


	string getId() const { return id; }
	string getTitulo() const { return titulo; }
	string getAutor() const{ return autor; }
	string getFecha() const { return fecha; }
	int getValoracion() const { return valoracion; }
	int getStock()const { return stock; }

	void setId(string id) { this->id = id; }
	void setTitulo(string titulo) { this->titulo = titulo; }
	void setAutor(string autor) { this->autor = autor; }
	void setFecha(string fecha) { this->fecha = fecha; }
	void setValoracion(int valoracion) { this->valoracion = valoracion; }
	void setStock(int stock) { this->stock = stock; }


	void incrementarStock() { stock++; }
	void decrementarStock() {
		if (stock > 0) stock--;
	}

	
};
