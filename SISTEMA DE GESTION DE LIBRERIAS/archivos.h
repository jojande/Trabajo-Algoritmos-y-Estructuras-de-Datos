#pragma once
#include "lector.h"
#include "bibliotecario.h"
#include "administrador.h"
#include "libro.h"
#include "tesis.h"
#include "revista.h"
#include "Prestamos.h"
#include <fstream>
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
    ss << libro.getId() << "|" << libro.getTitulo() << "|" << libro.getAutor() << "|" << libro.getFecha() << "|"
        << libro.getValoracion() << "|" << libro.getGenero() << "|" << libro.getEditorial();
    escribirLineaEnArchivo("archivos_txt/libros.txt", ss.str());
}

void guardarRevista(const revista& revista) {
    stringstream ss;
    ss << revista.getId() << "|" << revista.getTitulo() << "|" << revista.getAutor() << "|" << revista.getFecha() << "|"
        << revista.getValoracion() << "|" << revista.getISSN() << "|" << revista.getClasificacion();
    escribirLineaEnArchivo("archivos_txt/revistas.txt", ss.str());
}

void guardarTesis(const tesis& tesis) {
    stringstream ss;
    ss << tesis.getId() << "|" << tesis.getTitulo() << "|" << tesis.getAutor() << "|" << tesis.getFecha() << "|"
		<< tesis.getValoracion() << "|" << tesis.getUniversidad() << ";" << tesis.getPais();
    escribirLineaEnArchivo("archivos_txt/tesis.txt", ss.str());
}

void guardarLector(const Lector& lector) {
	stringstream ss;
	ss << lector.getId() << "|" << lector.getNombre() << "|" << lector.getContrasenia();
	escribirLineaEnArchivo("archivos_txt/lectores.txt", ss.str());
}

void guardarAdmin(const Administrador& admin) {
    stringstream ss;
    ss << admin.getId() << "|" << admin.getNombre() << "|" << admin.getContrasenia();
    escribirLineaEnArchivo("archivos_txt/admins.txt", ss.str());
}

void guardarBibliotecario(const Bibliotecario& bibliotecario) {
	stringstream ss;
	ss << bibliotecario.getId() << "|" << bibliotecario.getNombre() << "|" << bibliotecario.getContrasenia();
	escribirLineaEnArchivo("archivos_txt/bibliotecarios.txt", ss.str());
}

void guardarPrestamo(const Prestamo& prestamo) {
    stringstream ss;
    ss << prestamo.getId() << "|" << prestamo.getFecha() << "|" << prestamo.getSolicitante()->getId() << "|"
        << prestamo.getRecurso()->getId() << "|" << prestamo.getEstado();
	escribirLineaEnArchivo("archivos_txt/prestamos.txt", ss.str());
}





