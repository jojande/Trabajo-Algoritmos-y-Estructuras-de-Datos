#pragma once
#include "lector.h"
#include "bibliotecario.h"
#include "administrador.h"
#include "libro.h"
#include "tesis.h"
#include "revista.h"
#include "Prestamos.h"
#include "Multa.h"
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

void guardarLibrosEnArchivo(ListaSimple<libro>& lista) {
    ofstream archivo("archivos_txt/libros.txt", ios::trunc);  // Borra contenido anterior

    if (!archivo.is_open()) {
        cout << "No se pudo abrir libros.txt\n";
        return;
    }

    Nodo<libro>* actual = lista.getCabeza();
    while (actual) {
        const libro& l = actual->dato;
        archivo << l.getId() << "|"
            << l.getTitulo() << "|"
            << l.getAutor() << "|"
            << l.getFecha() << "|"
            << l.getValoracion() << "|"
            << l.getGenero() << "|"
            << l.getEditorial() << "|"
            << l.getStock() << "\n"; 
        actual = actual->siguiente;
    }

    archivo.close();
}



void guardarRevistasEnArchivo(ListaSimple<revista>& lista) {
    ofstream archivo("archivos_txt/revistas.txt", ios::trunc);  // Borra contenido anterior

    if (!archivo.is_open()) {
        cout << "No se pudo abrir revistas.txt\n";
        return;
    }

    Nodo<revista>* actual = lista.getCabeza();
    while (actual) {
        const revista& r = actual->dato;
        archivo << r.getId() << "|"
            << r.getTitulo() << "|"
            << r.getAutor() << "|"
            << r.getFecha() << "|"
            << r.getValoracion() << "|"
            << r.getISSN() << "|"
            << r.getClasificacion() << "|"
            << r.getStock() << "\n";
        actual = actual->siguiente;
    }

    archivo.close();
}

void guardarTesisEnArchivo(ListaSimple<tesis>& lista) {
    ofstream archivo("archivos_txt/tesis.txt", ios::trunc);  // Borra contenido anterior

    if (!archivo.is_open()) {
        cout << "No se pudo abrir tesis.txt\n";
        return;
    }

    Nodo<tesis>* actual = lista.getCabeza();
    while (actual) {
        const tesis& t = actual->dato;
        archivo << t.getId() << "|"
            << t.getTitulo() << "|"
            << t.getAutor() << "|"
            << t.getFecha() << "|"
            << t.getValoracion() << "|"
            << t.getUniversidad() << "|"
            << t.getPais() << "|"
            << t.getStock() << "\n";
        actual = actual->siguiente;
    }

    archivo.close();
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
    ss << prestamo.getId() << "|" << prestamo.getFecha() << "|" << prestamo.getSolicitante()->getId() << "|" << prestamo.getSolicitante()->getNombre() << "|"
        << prestamo.getRecurso()->getId() << "|" << prestamo.getRecurso()->getTitulo() << "|" << prestamo.getFechaVencimiento().toString() << "|" << prestamo.getEstado();
    escribirLineaEnArchivo("archivos_txt/prestamos.txt", ss.str());
}

void guardarTodosLosPrestamosEnArchivo(const Cola<Prestamo>& cola) {
    ofstream archivo("archivos_txt/prestamos.txt", ios::out); 

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de prestamos.txt\n";
        return;
    }

    Nodo<Prestamo>* actual = cola.getFrente();
    while (actual != nullptr) {
        const Prestamo& prestamo = actual->dato;
        archivo << prestamo.getId() << "|"
            << prestamo.getFecha() << "|"
            << prestamo.getSolicitante()->getId() << "|"
            << prestamo.getSolicitante()->getNombre() << "|"
            << prestamo.getRecurso()->getId() << "|"
            << prestamo.getRecurso()->getTitulo() << "|"
            << prestamo.getFechaVencimiento().toString() << "|"
            << prestamo.getEstado() << "\n";
        actual = actual->siguiente;
    }

    archivo.close();
}

void guardarPrestamosConfirmadosDesdeHashTable(HashTable<Prestamo>& tabla) {
    ofstream archivo("archivos_txt/prestamos_confirmados.txt", ios::trunc);  // limpia el archivo

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }
    for (int i = 0; i < 50; i++) {
        Nodo<Prestamo>* actual = tabla.getCubeta(i);
        while (actual != nullptr) {
            Prestamo& p = actual->dato;
            if (actual->dato.getEstado() == "Confirmado") {
                archivo << actual->dato.getId() << "|"
                    << actual->dato.getFecha() << "|"
                    << actual->dato.getSolicitante()->getId() << "|"
                    << actual->dato.getSolicitante()->getNombre() << "|"
                    << actual->dato.getRecurso()->getId() << "|"
                    << actual->dato.getRecurso()->getTitulo() << "|"
                    << actual->dato.getFechaVencimiento().toString() << "|"
                    << actual->dato.getEstado() << "\n";
            }
            actual = actual->siguiente;
        }
    }

    archivo.close();
}



void guardarMultasEnArchivoRecursivo(NodoArbol<Multa>* nodo, ofstream& archivo) {
    if (!nodo) return;

    guardarMultasEnArchivoRecursivo(nodo->izq, archivo);

    Multa& m = nodo->dato;
    Prestamo* p = m.getPrestamo();

    if (p) {
        archivo << m.getIdMulta() << "|"
            << p->getId() << "|"
            << p->getSolicitante()->getNombre() << "|"
            << p->getRecurso()->getTitulo() << "|"
            << m.getMonto() << "|"
            << p->getFechaVencimiento().toString() << "\n";
    }

    guardarMultasEnArchivoRecursivo(nodo->der, archivo);
}

void guardarMultasEnArchivo(ArbolBinario<Multa>& arbol) {
    ofstream archivo("archivos_txt/multas.txt", ios::trunc);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir multas.txt\n";
        return;
    }

    guardarMultasEnArchivoRecursivo(arbol.getRaiz(), archivo);
    archivo.close();
}