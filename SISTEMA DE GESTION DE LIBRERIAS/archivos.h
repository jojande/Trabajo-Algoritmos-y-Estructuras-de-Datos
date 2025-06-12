#pragma once
#include "tesis.h"
#include "libro.h"
#include "revista.h"
#include "usuario.h"
#include <string>
#include <sstream>  
using namespace std;

void escribirLineaEnArchivo(const string& nombreArchivo, const string& linea) {
    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << linea << "\n";
        archivo.close();
    }
}

void guardarLibro(const libro& libro) {
    stringstream ss;
    ss << libro.getId() << ";" << libro.getTitulo() << ";" << libro.getAutor() << ";" << libro.getFecha() << ";"
        << libro.getValoracion() << ";" << libro.getGenero() << ";" << libro.getEditorial();
    escribirLineaEnArchivo("libros.txt", ss.str());
}

void guardarRevista(const revista& revista) {
    stringstream ss;
    ss << revista.getId() << ";" << revista.getTitulo() << ";" << revista.getAutor() << ";" << revista.getFecha() << ";"
        << revista.getValoracion() << ";" << revista.getISSN() << ";" << revista.getClasificacion();
    escribirLineaEnArchivo("revistas.txt", ss.str());
}

void guardarTesis(const tesis& tesis) {
    stringstream ss;
    ss << tesis.getId() << ";" << tesis.getTitulo() << ";" << tesis.getAutor() << ";" << tesis.getFecha() << ";"
		<< tesis.getValoracion() << ";" << tesis.getUniversidad() << ";" << tesis.getPais();
    escribirLineaEnArchivo("tesis.txt", ss.str());
}




