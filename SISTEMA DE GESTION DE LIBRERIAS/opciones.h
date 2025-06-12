#ifndef opciones_H
#define opciones_H
#include "EstructurasDatos.h"
#include "tesis.h"
#include "libro.h"
#include "revista.h"
#include "archivos.h"
#include "administrador.h"

ListaSimple<libro> listaLibros;
ListaSimple<tesis> listaTesis;
ListaSimple<revista> listaRevistas;

string generarID(const string& tipo, int contador) {
    string prefijo;
    if (tipo == "libro") {
        prefijo = "IDLI";
    }
    else if (tipo == "revista") {
        prefijo = "IDRE";
    }
    else if (tipo == "tesis") {
        prefijo = "IDTE";
    }
    string sufijo = (contador < 10 ? "0" : "") + to_string(contador);
    return prefijo + sufijo;
}

string leerCadena(const string& mensaje) {
    cout << mensaje;
    string entrada;
    getline(cin >> ws, entrada);
    return entrada;
}

int leerEntero(const string& mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cout << "Entrada inválida. Intente de nuevo: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return valor;
}

void registrarLibro() {
    int cantidadLibros = listaLibros.tamano();
    string id = generarID("libro", cantidadLibros + 1);
    string titulo = leerCadena("Titulo: ");
    string autor = leerCadena("Autor: ");
    string fecha = leerCadena("Fecha: ");
    int valoracion = leerEntero("Valoracion: ");
    string genero = leerCadena("Genero: ");
    string editorial = leerCadena("Editorial: ");
    libro nuevo(id, titulo, autor, fecha, valoracion, genero, editorial);
    listaLibros.insertarAlFinal(nuevo);
    guardarLibro(nuevo);

    cout << "Libro registrado.\n";
}

void registrarRevista() {
    int cantidadRevistas = listaRevistas.tamano();
    string id = generarID("revista", cantidadRevistas + 1);
    string titulo = leerCadena("Titulo: ");
    string autor = leerCadena("Autor: ");
    string fecha = leerCadena("Fecha: ");
    int valoracion = leerEntero("Valoracion: ");
    string ISSN = leerCadena("ISSN: ");
    string clasificacion = leerCadena("Clasificacion: ");
    revista nuevo(id, titulo, autor, fecha, valoracion, ISSN, clasificacion);
    listaRevistas.insertarAlFinal(nuevo);
    guardarRevista(nuevo);

    cout << "Revista registrada.\n";
}

void registrarTesis() {
    int cantidadTesis = listaTesis.tamano();
    string id = generarID("tesis", cantidadTesis + 1);
    string titulo = leerCadena("Titulo: ");
    string autor = leerCadena("Autor: ");
    string fecha = leerCadena("Fecha: ");
    int valoracion = leerEntero("Valoracion: ");
    string universidad = leerCadena("Universidad: ");
    string pais = leerCadena("Pais: ");
    tesis nuevo(id, titulo, autor, fecha, valoracion, universidad, pais);
    listaTesis.insertarAlFinal(nuevo);
    guardarTesis(nuevo);

    cout << "Tesis registrada.\n";
}

void cargarLibros(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        size_t pos1 = linea.find(';');
        size_t pos2 = linea.find(';', pos1 + 1);
        size_t pos3 = linea.find(';', pos2 + 1);
        size_t pos4 = linea.find(';', pos3 + 1);
        size_t pos5 = linea.find(';', pos4 + 1);
        size_t pos6 = linea.find(';', pos5 + 1);

        try {
            string id = linea.substr(0, pos1);
            string titulo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string autor = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string fecha = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            int valoracion = stoi(linea.substr(pos4 + 1, pos5 - pos4 - 1));
            string genero = linea.substr(pos5 + 1, pos6 - pos5 - 1);
            string editorial = linea.substr(pos6 + 1);

            libro nuevo;
            nuevo.setId(id);
            nuevo.setTitulo(titulo);
            nuevo.setAutor(autor);
            nuevo.setFecha(fecha);
            nuevo.setValoracion(valoracion);
            nuevo.setGenero(genero);
            nuevo.setEditorial(editorial);

            listaLibros.insertarAlFinal(nuevo);
        }
        catch (const exception& e) {
            cerr << "Error en la línea:\n" << linea << "\n" << e.what() << endl;
        }
    }

    archivo.close();
}

void cargarRevistas(const string& nombreArchivo) {
	ifstream archivo(nombreArchivo);
	string linea;
	while (getline(archivo, linea)) {
		if (linea.empty()) continue;
		size_t pos1 = linea.find(';');
		size_t pos2 = linea.find(';', pos1 + 1);
		size_t pos3 = linea.find(';', pos2 + 1);
		size_t pos4 = linea.find(';', pos3 + 1);
		size_t pos5 = linea.find(';', pos4 + 1);
		size_t pos6 = linea.find(';', pos5 + 1);
		try {
			string id = linea.substr(0, pos1);
			string titulo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
			string autor = linea.substr(pos2 + 1, pos3 - pos2 - 1);
			string fecha = linea.substr(pos3 + 1, pos4 - pos3 - 1);
			int valoracion = stoi(linea.substr(pos4 + 1, pos5 - pos4 - 1));
			string ISSN = linea.substr(pos5 + 1, pos6 - pos5 - 1);
			string clasificacion = linea.substr(pos6 + 1);
			revista nuevo;
			nuevo.setId(id);
			nuevo.setTitulo(titulo);
			nuevo.setAutor(autor);
			nuevo.setFecha(fecha);
			nuevo.setValoracion(valoracion);
			nuevo.setISSN(ISSN);
			nuevo.setClasificacion(clasificacion);
			listaRevistas.insertarAlFinal(nuevo);
		}
		catch (const exception& e) {
			cerr << "Error en la línea:\n" << linea << "\n" << e.what() << endl;
		}
	}
	archivo.close();
}

void cargarTesis(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        size_t pos1 = linea.find(';');
        size_t pos2 = linea.find(';', pos1 + 1);
        size_t pos3 = linea.find(';', pos2 + 1);
        size_t pos4 = linea.find(';', pos3 + 1);
        size_t pos5 = linea.find(';', pos4 + 1);
        size_t pos6 = linea.find(';', pos5 + 1);
        try {
            string id = linea.substr(0, pos1);
            string titulo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string autor = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string fecha = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            int valoracion = stoi(linea.substr(pos4 + 1, pos5 - pos4 - 1));
            string universidad = linea.substr(pos5 + 1, pos6 - pos5 - 1);
            string pais = linea.substr(pos6 + 1);
            tesis nuevo;
            nuevo.setId(id);
            nuevo.setTitulo(titulo);
            nuevo.setAutor(autor);
            nuevo.setFecha(fecha);
            nuevo.setValoracion(valoracion);
            nuevo.setUniversidad(universidad);
            nuevo.setPais(pais);
            listaTesis.insertarAlFinal(nuevo);
        }
        catch (const exception& e) {
            cerr << "Error en la línea:\n" << linea << "\n" << e.what() << endl;
        }
    }
    archivo.close();
}

void eliminarLibro() {
    string id;
    cout << "Ingrese ID del libro a eliminar: ";
    cin >> id;

    if (listaLibros.eliminarPorID(id)) {
        cout << "Libro eliminado correctamente.\n";
    }
    else {
        cout << "Libro no encontrado.\n";
    }
}

void eliminarRevista() {
    string id;
    cout << "Ingrese ID de la revista a eliminar: ";
    cin >> id;

    if (listaRevistas.eliminarPorID(id)) {
        cout << "Revista eliminada correctamente.\n";
    }
    else {
        cout << "Revista no encontrada.\n";
    }
}

void eliminarTesis() {
    string id;
    cout << "Ingrese ID de la tesis a eliminar: ";
    cin >> id;

    if (listaTesis.eliminarPorID(id)) {
        cout << "Tesis eliminada correctamente.\n";
    }
    else {
        cout << "Tesis no encontrada.\n";
    }
}

void modificarLibro() {
    string id;
    cout << "Ingrese ID del libro a modificar: ";
    cin >> id;

    
    string titulo = leerCadena("Nuevo titulo: ");
    string autor = leerCadena("Nuevo autor: ");
    string fecha = leerCadena("Nueva fecha: ");
    int valoracion = leerEntero("Nueva valoracion: ");
    string genero = leerCadena("Nuevo genero: ");
    string editorial = leerCadena("Nueva editorial: ");

    libro nuevosDatos(id, titulo, autor, fecha, valoracion, genero, editorial);

    if (listaLibros.modificarPorID(id, nuevosDatos)) {
        cout << "Libro modificado correctamente.\n";
        guardarLibro(nuevosDatos);  
    }
    else {
        cout << "Libro no encontrado.\n";
    }
}

void modificarRevista() {
    string id;
    cout << "Ingrese ID de la revista a modificar: ";
    cin >> id;

    
    string titulo = leerCadena("Nuevo titulo: ");
    string autor = leerCadena("Nuevo autor: ");
    string fecha = leerCadena("Nueva fecha: ");
    int valoracion = leerEntero("Nueva valoracion: ");
    string ISSN = leerCadena("Nuevo ISSN: ");
    string clasificacion = leerCadena("Nueva clasificacion: ");

    revista nuevosDatos(id, titulo, autor, fecha, valoracion, ISSN, clasificacion);

    if (listaRevistas.modificarPorID(id, nuevosDatos)) {
        cout << "Revista modificado correctamente.\n";
        guardarRevista(nuevosDatos);  
    }
    else {
        cout << "Revista no encontrado.\n";
    }
}

void modificarTesis() {
    string id;
    cout << "Ingrese ID de la tesis a modificar: ";
    cin >> id;

    string titulo = leerCadena("Nuevo titulo: ");
    string autor = leerCadena("Nuevo autor: ");
    string fecha = leerCadena("Nueva fecha: ");
    int valoracion = leerEntero("Nueva valoracion: ");
    string universidad = leerCadena("Nueva Universidad: ");
    string pais = leerCadena("Nuevo pais: ");

    tesis nuevosDatos(id, titulo, autor, fecha, valoracion, universidad, pais);

    if (listaTesis.modificarPorID(id, nuevosDatos)) {
        cout << "Tesis modificado correctamente.\n";
        guardarTesis(nuevosDatos);  
    }
    else {
        cout << "Tesis no encontrado.\n";
    }
}

void mostrarLibros() {
    cout << "\nLista de libros:\n";
	cout << listaLibros.tamano() << " libros registrados.\n";
    listaLibros.mostrarTodo();
}

void mostrarRevistas() {
    cout << "\nLista de revistas:\n";
    listaRevistas.mostrarTodo();
}

void mostrarTesis() {
    cout << "\nLista de tesis:\n";
    listaTesis.mostrarTodo();
}

#endif