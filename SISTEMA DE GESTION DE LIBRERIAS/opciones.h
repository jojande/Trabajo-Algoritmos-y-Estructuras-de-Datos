#pragma once
#include "EstructurasDatos.h"
#include "lector.h"
#include "bibliotecario.h"
#include "administrador.h"
#include "libro.h"
#include "tesis.h"
#include "revista.h"
#include "archivos.h"
#include "ControlVencimientos.h"
#include <conio.h>
ListaSimple<libro> listaLibros;
ListaSimple<tesis> listaTesis;
ListaSimple<revista> listaRevistas;
ListaSimple<Administrador> listaAdmins;
ListaSimple<Lector> listaLectores;
ListaSimple<Bibliotecario> listaBibliotecarios;

Cola<Prestamo> colaPrestamos;
HashTable<Prestamo> tablaOrdenada;
ArbolBinario<Multa> arbolMultasSimuladas;

ControlVencimientos heap;

Grafo<string> grafoRecursos(100, false); // No dirigido





void construirGrafoDeLibrosPorGenero() {
    Nodo<libro>* i = listaLibros.getCabeza();
    while (i != nullptr) {
        grafoRecursos.agregarNodo(i->dato.getId());

        Nodo<libro>* j = i->siguiente;
        while (j != nullptr) {
            if (i->dato.getGenero() == j->dato.getGenero()) {
                grafoRecursos.agregarNodo(j->dato.getId());
                grafoRecursos.agregarArista(i->dato.getId(), j->dato.getId());
            }
            j = j->siguiente;
        }
        i = i->siguiente;
    }
}

void construirGrafoDeLibrosPorAutor() {
    Nodo<libro>* i = listaLibros.getCabeza();
    while (i != nullptr) {
        grafoRecursos.agregarNodo(i->dato.getId());

        Nodo<libro>* j = i->siguiente;
        while (j != nullptr) {
            if (i->dato.getAutor() == j->dato.getAutor()) {
                grafoRecursos.agregarNodo(j->dato.getId());
                grafoRecursos.agregarArista(i->dato.getId(), j->dato.getId());
            }
            j = j->siguiente;
        }
        i = i->siguiente;
    }
}

void mostrarRecursosRelacionados(const string& id) {
    cout << "Recursos relacionados con " << id << ":\n";

    int idx = grafoRecursos.obtenerGrado(id);
    if (idx == -1) {
        cout << "Recurso no encontrado en el grafo.\n";
        return;
    }

    // Mostrar desde la lista de adyacencia
    Nodo<string>* actual = nullptr;
    for (int i = 0; i < 100; ++i) {
        if (grafoRecursos.getNodo(i) != nullptr && grafoRecursos.getNodo(i)->dato == id) {
            actual = grafoRecursos.getNodo(i)->siguiente;
            break;
        }
    }

    if (actual == nullptr) {
        cout << "Este recurso no tiene conexiones.\n";
        return;
    }

    while (actual != nullptr) {
        cout << "- " << actual->dato << endl;
        actual = actual->siguiente;
    }
}


int obtenerIDDisponible(const string& archivoNombre, const string& prefijo) {
    ifstream archivo(archivoNombre);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivoNombre << endl;
        return 1; // Empezar desde 1 si el archivo no existe
    }

    bool usados[100] = { false }; // IDLI01 a IDLI99 (hasta 99 recursos)
    string linea;

    while (getline(archivo, linea)) {
        if (linea.substr(0, prefijo.size()) == prefijo) {
            string numStr = linea.substr(prefijo.size(), 2);
            try {
                int num = stoi(numStr);
                if (num >= 1 && num <= 99)
                    usados[num] = true;
            }
            catch (...) {

            }
        }
    }
    archivo.close();

    for (int i = 1; i <= 99; ++i) {
        if (!usados[i])
            return i;
    }

    return 100;
}



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
    else if (tipo == "lector") {
		prefijo = "IDLE";
	}
	else if (tipo == "bibliotecario") {
		prefijo = "IDBI";
	}
	else if (tipo == "administrador") {
		prefijo = "IDAD";
	}
	else if (tipo == "prestamo") {
		prefijo = "IDPR";
	}
    else if (tipo == "multa") {
        prefijo = "IDMU";
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
    int disponibleID = obtenerIDDisponible("archivos_txt/libros.txt", "IDLI");
    string id = generarID("libro", disponibleID);
    string titulo = leerCadena("Titulo: ");
    string autor = leerCadena("Autor: ");
    string fecha = leerCadena("Fecha: ");
    int valoracion = leerEntero("Valoracion: ");
    string genero = leerCadena("Genero: ");
    string editorial = leerCadena("Editorial: ");
    int stock = leerEntero("Stock: ");

    libro nuevo(id, titulo, autor, fecha, valoracion, genero, editorial, stock);
    listaLibros.insertarAlFinal(nuevo);
    guardarLibrosEnArchivo(listaLibros); 

    cout << "Libro registrado.\n";
}


void registrarRevista() {
    int disponibleID = obtenerIDDisponible("archivos_txt/revistas.txt", "IDRE");
    string id = generarID("libro", disponibleID);
    string titulo = leerCadena("Titulo: ");
    string autor = leerCadena("Autor: ");
    string fecha = leerCadena("Fecha: ");
    int valoracion = leerEntero("Valoracion: ");
    string ISSN = leerCadena("ISSN: ");
    string clasificacion = leerCadena("Clasificacion: ");
    int stock = leerEntero("Stock: ");

    revista nuevo(id, titulo, autor, fecha, valoracion, ISSN, clasificacion,stock);
    listaRevistas.insertarAlFinal(nuevo);
    guardarRevistasEnArchivo(listaRevistas);

    cout << "Revista registrada.\n";
}


void registrarTesis() {
    int disponibleID = obtenerIDDisponible("archivos_txt/tesis.txt", "IDTE");
    string id = generarID("libro", disponibleID);
    string titulo = leerCadena("Titulo: ");
    string autor = leerCadena("Autor: ");
    string fecha = leerCadena("Fecha: ");
    int valoracion = leerEntero("Valoracion: ");
    string universidad = leerCadena("Universidad: ");
    string pais = leerCadena("Pais: ");
    int stock = leerEntero("Stock: ");

    tesis nuevo(id, titulo, autor, fecha, valoracion, universidad, pais, stock);
    listaTesis.insertarAlFinal(nuevo);
    guardarTesisEnArchivo(listaTesis);

    cout << "Tesis registrada.\n";
}

void registrarLector() {
    int cantidadLector = listaLectores.tamano();
    string id = generarID("lector", cantidadLector + 1);
    string nombre = leerCadena("Nombre: ");
    string contrasenia = leerCadena("Contrasena: ");
    Lector nuevo(id, nombre, contrasenia);
    listaLectores.insertarAlFinal(nuevo);
    guardarLector(nuevo);

    cout << "Lector registrado.\n";
}

void registrarBibliotecario() {
	int cantidadBibliotecario = listaBibliotecarios.tamano();
	string id = generarID("bibliotecario", cantidadBibliotecario + 1);
	string nombre = leerCadena("Nombre: ");
	string contrasenia = leerCadena("Contrasena: ");
	Bibliotecario nuevo(id, nombre, contrasenia);
	listaBibliotecarios.insertarAlFinal(nuevo);
	guardarBibliotecario(nuevo);
	cout << "Bibliotecario registrado.\n";
}

void registrarAdministrador() {
	int cantidadAdmin = listaAdmins.tamano();
	string id = generarID("administrador", cantidadAdmin + 1);
	string nombre = leerCadena("Nombre: ");
	string contrasenia = leerCadena("Contrasena: ");
	Administrador nuevo(id, nombre, contrasenia);
	listaAdmins.insertarAlFinal(nuevo);
	guardarAdmin(nuevo);
	cout << "Administrador registrado.\n";
}

void registrarPrestamo() {
    if (listaLibros.tamano() == 0 && listaRevistas.tamano() == 0 && listaTesis.tamano() == 0) {
        cout << "No hay recursos disponibles para prestar.\n";
        return;
    }

    int cantidadPrestamos = colaPrestamos.tamanio();
    string id = generarID("prestamo", cantidadPrestamos + 1);
    string fecha = leerCadena("Fecha del prestamo: ");
    string idLector = leerCadena("ID del lector: ");

    Lector* solicitante = listaLectores.hallarID(idLector);
    if (!solicitante) {
        cout << "Lector no encontrado.\n";
        return;
    }

    cout << "Seleccione el tipo de recurso a prestar:\n";
    cout << "1. Libro\n";
    cout << "2. Revista\n";
    cout << "3. Tesis\n";

    int opcion;
    cin >> opcion;
    cin.ignore();

    RecursoBibliografico* recurso = nullptr;

    switch (opcion) {
    case 1: {
        string idLibro = leerCadena("ID del libro: ");
        recurso = listaLibros.hallarID(idLibro);
        break;
    }
    case 2: {
        string idRevista = leerCadena("ID de la revista: ");
        recurso = listaRevistas.hallarID(idRevista);
        break;
    }
    case 3: {
        string idTesis = leerCadena("ID de la tesis: ");
        recurso = listaTesis.hallarID(idTesis);
        break;
    }
    default:
        cout << "Opción inválida.\n";
        return;
    }

    if (!recurso) {
        cout << "Recurso no encontrado.\n";
        return;
    }

    // guarda en lista y txt
    Prestamo nuevoPrestamo(id, fecha, solicitante, recurso);
    colaPrestamos.encolar(nuevoPrestamo);
    guardarPrestamo(nuevoPrestamo);

    cout << "Prestamo registrado correctamente con ID: " << id << "\n";
}


void cargarLibros(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);
        size_t pos4 = linea.find('|', pos3 + 1);
        size_t pos5 = linea.find('|', pos4 + 1);
        size_t pos6 = linea.find('|', pos5 + 1);
        size_t pos7 = linea.find('|', pos6 + 1);


        try {
            string id = linea.substr(0, pos1);
            string titulo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string autor = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string fecha = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            int valoracion = stoi(linea.substr(pos4 + 1, pos5 - pos4 - 1));
            string genero = linea.substr(pos5 + 1, pos6 - pos5 - 1);
            string editorial = linea.substr(pos6 + 1, pos7 - pos6 - 1);
            int stock = stoi(linea.substr(pos7 + 1));

            libro nuevo;
            nuevo.setId(id);
            nuevo.setTitulo(titulo);
            nuevo.setAutor(autor);
            nuevo.setFecha(fecha);
            nuevo.setValoracion(valoracion);
            nuevo.setGenero(genero);
            nuevo.setEditorial(editorial);
            nuevo.setStock(stock);

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
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);
        size_t pos4 = linea.find('|', pos3 + 1);
        size_t pos5 = linea.find('|', pos4 + 1);
        size_t pos6 = linea.find('|', pos5 + 1);
        size_t pos7 = linea.find('|', pos6 + 1);

		try {
			string id = linea.substr(0, pos1);
			string titulo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
			string autor = linea.substr(pos2 + 1, pos3 - pos2 - 1);
			string fecha = linea.substr(pos3 + 1, pos4 - pos3 - 1);
			int valoracion = stoi(linea.substr(pos4 + 1, pos5 - pos4 - 1));
			string ISSN = linea.substr(pos5 + 1, pos6 - pos5 - 1);
			string clasificacion = linea.substr(pos6 + 1,pos7 - pos6 -1);
            int stock = stoi(linea.substr(pos7 + 1));

			revista nuevo;
			nuevo.setId(id);
			nuevo.setTitulo(titulo);
			nuevo.setAutor(autor);
			nuevo.setFecha(fecha);
			nuevo.setValoracion(valoracion);
			nuevo.setISSN(ISSN);
			nuevo.setClasificacion(clasificacion);
            nuevo.setStock(stock);

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
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);
        size_t pos4 = linea.find('|', pos3 + 1);
        size_t pos5 = linea.find('|', pos4 + 1);
        size_t pos6 = linea.find('|', pos5 + 1);
        size_t pos7 = linea.find('|', pos6 + 1);

        try {
            string id = linea.substr(0, pos1);
            string titulo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string autor = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string fecha = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            int valoracion = stoi(linea.substr(pos4 + 1, pos5 - pos4 - 1));
            string universidad = linea.substr(pos5 + 1, pos6 - pos5 - 1);
            string pais = linea.substr(pos6 + 1,pos7 - pos6 -1);
            int stock = stoi(linea.substr(pos7 + 1));

            tesis nuevo;
            nuevo.setId(id);
            nuevo.setTitulo(titulo);
            nuevo.setAutor(autor);
            nuevo.setFecha(fecha);
            nuevo.setValoracion(valoracion);
            nuevo.setUniversidad(universidad);
            nuevo.setPais(pais);
            nuevo.setStock(stock);

            listaTesis.insertarAlFinal(nuevo);
        }
        catch (const exception& e) {
            cerr << "Error en la línea:\n" << linea << "\n" << e.what() << endl;
        }
    }
    archivo.close();
}

void cargarLector(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        try {
            string id = linea.substr(0, pos1);
            string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string contrasenia = linea.substr(pos2 + 1);
            Lector nuevo(id, nombre, contrasenia);
            listaLectores.insertarAlFinal(nuevo);
        }
        catch (const exception& e) {
            cerr << "Error en la línea:\n" << linea << "\n" << e.what() << endl;
        }
    }
    archivo.close();
}

void cargarBibliotecario(const string& nombreArchivo) {
	ifstream archivo(nombreArchivo);
	string linea;
	while (getline(archivo, linea)) {
		if (linea.empty()) continue;
		size_t pos1 = linea.find('|');
		size_t pos2 = linea.find('|', pos1 + 1);
		try {
			string id = linea.substr(0, pos1);
			string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
			string contrasenia = linea.substr(pos2 + 1);
			Bibliotecario nuevo(id, nombre, contrasenia);
			listaBibliotecarios.insertarAlFinal(nuevo);
		}
		catch (const exception& e) {
			cerr << "Error en la línea:\n" << linea << "\n" << e.what() << endl;
		}
	}
	archivo.close();
}

void cargarAdministrador(const string& nombreArchivo) {
	ifstream archivo(nombreArchivo);
	string linea;
	while (getline(archivo, linea)) {
		if (linea.empty()) continue;
		size_t pos1 = linea.find('|');
		size_t pos2 = linea.find('|', pos1 + 1);
		try {
			string id = linea.substr(0, pos1);
			string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
			string contrasenia = linea.substr(pos2 + 1);
			Administrador nuevo(id, nombre, contrasenia);
			listaAdmins.insertarAlFinal(nuevo);
		}
		catch (const exception& e) {
			cerr << "Error en la línea:\n" << linea << "\n" << e.what() << endl;
		}
	}
	archivo.close();
}

void cargarPrestamo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        try {
            // Buscar las posiciones de los 6 separadores '|'
            size_t p1 = linea.find('|');
            size_t p2 = linea.find('|', p1 + 1);
            size_t p3 = linea.find('|', p2 + 1);
            size_t p4 = linea.find('|', p3 + 1);
            size_t p5 = linea.find('|', p4 + 1);
            size_t p6 = linea.find('|', p5 + 1);
            size_t p7 = linea.find('|', p6 + 1);


            if (p6 == string::npos) {
                cerr << "Línea mal formateada:\n" << linea << endl;
                continue;
            }

            string id = linea.substr(0, p1);
            string fecha = linea.substr(p1 + 1, p2 - p1 - 1);
            string idLector = linea.substr(p2 + 1, p3 - p2 - 1);
            string nombreLector = linea.substr(p3 + 1, p4 - p3 - 1); // opcional
            string idRecurso = linea.substr(p4 + 1, p5 - p4 - 1);
            string tituloRecurso = linea.substr(p5 + 1, p6 - p5 - 1); // opcional
            string fechaVencimiento = linea.substr(p6 + 1, p7 - p6 - 1); // hasta fin de línea
            string estado = linea.substr(p7 + 1); // hasta fin de línea
             
            Lector* solicitante = listaLectores.hallarID(idLector);
            RecursoBibliografico* recurso = nullptr;

            if (idRecurso.substr(0, 4) == "IDLI") {
                recurso = listaLibros.hallarID(idRecurso);
            }
            else if (idRecurso.substr(0, 4) == "IDRE") {
                recurso = listaRevistas.hallarID(idRecurso);
            }
            else if (idRecurso.substr(0, 4) == "IDTE") {
                recurso = listaTesis.hallarID(idRecurso);
            }

            if (solicitante && recurso) {
                Prestamo nuevoPrestamo(id, fecha, solicitante, recurso, estado);
                colaPrestamos.encolar(nuevoPrestamo);

                // Si el préstamo está pendiente, reducimos el stock
                if (estado == "Pendiente") {
                    recurso->setStock(recurso->getStock() - 1);
                }
            }
            else {
                cerr << "No se encontró lector o recurso en la línea:\n" << linea << endl;
            }
        }
        catch (const exception& e) {
            cerr << "Error procesando la línea:\n" << linea << "\n" << e.what() << endl;
        }
    }

    archivo.close();
}

void eliminarLibro() {
    string id;
    cout << "Ingrese ID del libro a eliminar: ";
    cin >> id;

    if (listaLibros.eliminarPorID(id)) {
        cout << "Libro eliminado correctamente de la lista.\n";

        // Reescribir el archivo sin el libro eliminado
        ofstream archivo("archivos_txt/libros.txt");
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo para actualizar.\n";
            return;
        }

        Nodo<libro>* actual = listaLibros.getCabeza();
        while (actual != nullptr) {
            libro lib = actual->dato;
            archivo << lib.getId() << "|" << lib.getTitulo() << "|" << lib.getAutor() << "|" << lib.getFecha() << "|"
                << lib.getValoracion() << "|" << lib.getGenero() << "|" << lib.getEditorial() << "|" << lib.getStock() << endl;
            actual = actual->siguiente;
        }

        archivo.close();
        cout << "Archivo actualizado.\n";

    }
    else {
        cout << "Libro no encontrado.\n";
    }

}
void cargarTablaPrestamosConfirmados(const string& nombreArchivo, HashTable<Prestamo>& tablaOrdenada) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string id, fecha, idLector, nombreLector, idRecurso, tituloRecurso, estado;

        getline(ss, id, '|');
        getline(ss, fecha, '|');
        getline(ss, idLector, '|');
        getline(ss, nombreLector, '|');
        getline(ss, idRecurso, '|');
        getline(ss, tituloRecurso, '|');
        getline(ss, estado, '|');

        if (estado != "Confirmado") continue;

        Lector* lector = listaLectores.hallarID(idLector);
        if (!lector) continue;

        RecursoBibliografico* recurso = nullptr;
        if (idRecurso.find("IDLI") == 0)
            recurso = listaLibros.hallarID(idRecurso);
        else if (idRecurso.find("IDRE") == 0)
            recurso = listaRevistas.hallarID(idRecurso);
        else if (idRecurso.find("IDTE") == 0)
            recurso = listaTesis.hallarID(idRecurso);

        if (!recurso) continue;

        Prestamo p(id, fecha, lector, recurso, estado);
        tablaOrdenada.insertar(p);
    }

    archivo.close();
}

void cargarmultas(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de multas.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string idMulta, idPrestamo, nombreLector, tituloRecurso, montoStr, fechaVenc;

        getline(ss, idMulta, '|');
        getline(ss, idPrestamo, '|');
        getline(ss, nombreLector, '|');
        getline(ss, tituloRecurso, '|');
        getline(ss, montoStr, '|');
        getline(ss, fechaVenc, '\n');

        double monto = stod(montoStr);

        Nodo<Prestamo>* nodoPrestamo = colaPrestamos.hallarID(idPrestamo);
        if (nodoPrestamo == nullptr) {
            cout << "No se encontró el préstamo con ID " << idPrestamo << " para la multa " << idMulta << "\n";
            continue;
        }

        Prestamo* ptrPrestamo = &(nodoPrestamo->dato);
        Multa nuevaMulta(idMulta, ptrPrestamo);
        nuevaMulta.setMonto(monto);

        arbolMultasSimuladas.insertar(nuevaMulta);  // usa el global
    }

    archivo.close();
    cout << "Multas cargadas correctamente.\n";
}



void eliminarRevista() {
    string id;
    cout << "Ingrese ID de la revista a eliminar: ";
    cin >> id;

    if (listaRevistas.eliminarPorID(id)) {
        cout << "Revista eliminada correctamente de la lista.\n";

        ofstream archivo("archivos_txt/revistas.txt");
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo para actualizar.\n";
            return;
        }

        Nodo<revista>* actual = listaRevistas.getCabeza();
        while (actual != nullptr) {
            revista lib = actual->dato;
            archivo << lib.getId() << "|" << lib.getTitulo() << "|" << lib.getAutor() << "|" << lib.getFecha() << "|"
                << lib.getValoracion() << "|" << lib.getISSN() << "|" << lib.getClasificacion() << "|" << lib.getStock() << endl;
            actual = actual->siguiente;
        }

        archivo.close();
        cout << "Archivo actualizado.\n";

    }
    else {
        cout << "Revista no encontrada.\n";
    }
}

void eliminarTesis() {
    string id;
    cout << "Ingrese ID de la tesis a eliminar: ";
    cin >> id;

    if (listaLibros.eliminarPorID(id)) {
        cout << "Libro eliminado correctamente de la lista.\n";

        ofstream archivo("archivos_txt/tesis.txt");
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo para actualizar.\n";
            return;
        }

        Nodo<tesis>* actual = listaTesis.getCabeza();
        while (actual != nullptr) {
            tesis lib = actual->dato;
            archivo << lib.getId() << "|" << lib.getTitulo() << "|" << lib.getAutor() << "|" << lib.getFecha() << "|"
                << lib.getValoracion() << "|" << lib.getUniversidad() << "|" << lib.getPais() << "|" << lib.getStock() << endl;
            actual = actual->siguiente;
        }

        archivo.close();
        cout << "Archivo actualizado.\n";

    }
    else {
        cout << "Tesis no encontrada.\n";
    }
}

void elimnarLector() {
    string id;
    cout << "Ingrese ID del lector a eliminar: ";
    cin >> id;

    if (listaLectores.eliminarPorID(id)) {
        cout << "Lector eliminado correctamente.\n";
    }
    else {
        cout << "Lector no encontrado.\n";
    }
}

void eliminarBibliotecario() {
    string id;
    cout << "Ingrese ID del Bibliotecario a eliminar: ";
    cin >> id;

    if (listaBibliotecarios.eliminarPorID(id)) {
        cout << "Biblioteracio eliminado correctamente.\n";
    }
    else {
        cout << "Bibliotecario no encontrado.\n";
    }
}

void eliminarAdmin() {
    string id;
    cout << "Ingrese ID del Administrador a eliminar: ";
    cin >> id;

    if (listaAdmins.eliminarPorID(id)) {
        cout << "Administrador eliminado correctamente.\n";
    }
    else {
        cout << "Administrador no encontrado.\n";
    }
}

void modificarLibro() {
    string id;
    cout << "Ingrese ID del libro a modificar: ";
    cin >> id;

    libro* libroEncontrado = listaLibros.hallarID(id);

    if (libroEncontrado) {
        cout << "\nIngrese los nuevos datos del libro:\n";

        string titulo = leerCadena("Nuevo titulo: ");
        string autor = leerCadena("Nuevo autor: ");
        string fecha = leerCadena("Nueva fecha: ");
        int valoracion = leerEntero("Nueva valoracion: ");
        string genero = leerCadena("Nuevo genero: ");
        string editorial = leerCadena("Nueva editorial: ");
        int stock = leerEntero("Nuevo stock: ");

        libroEncontrado->setTitulo(titulo);
        libroEncontrado->setAutor(autor);
        libroEncontrado->setFecha(fecha);
        libroEncontrado->setValoracion(valoracion);
        libroEncontrado->setGenero(genero);
        libroEncontrado->setEditorial(editorial);
        libroEncontrado->setStock(stock);  

        guardarLibrosEnArchivo(listaLibros); 
        cout << "Libro modificado correctamente.\n";
    }
    else {
        cout << "Libro no encontrado.\n";
    }
}


void modificarRevista() {
    string id;
    cout << "Ingrese ID de la revista a modificar: ";
    cin >> id;

    revista* revistaEncontrado = listaRevistas.hallarID(id);

    if (revistaEncontrado) {
        cout << "\nIngrese los nuevos datos de la revista:\n";

        string titulo = leerCadena("Nuevo titulo: ");
        string autor = leerCadena("Nuevo autor: ");
        string fecha = leerCadena("Nueva fecha: ");
        int valoracion = leerEntero("Nueva valoracion: ");
        string ISSN = leerCadena("Nuevo ISSN: ");
        string clasificacion = leerCadena("Nueva clasificacion: ");
        int stock = leerEntero("Nuevo stock: ");

        revistaEncontrado->setTitulo(titulo);
        revistaEncontrado->setAutor(autor);
        revistaEncontrado->setFecha(fecha);
        revistaEncontrado->setValoracion(valoracion);
        revistaEncontrado->setISSN(ISSN);
        revistaEncontrado->setClasificacion(clasificacion);
        revistaEncontrado->setStock(stock);

        guardarRevistasEnArchivo(listaRevistas);
        cout << "Revista modificado correctamente.\n";
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
    int stock = leerEntero("Nuevo stock: ");

    tesis* tesisEncontrada = listaTesis.hallarID(id);

    if (tesisEncontrada) {
        tesisEncontrada->setTitulo(titulo);
        tesisEncontrada->setAutor(autor);
        tesisEncontrada->setFecha(fecha);
        tesisEncontrada->setValoracion(valoracion);
        tesisEncontrada->setUniversidad(universidad);
        tesisEncontrada->setPais(pais);
        tesisEncontrada->setStock(stock);

        guardarTesisEnArchivo(listaTesis);  
        cout << "Tesis modificada correctamente.\n";
    }
    else {
        cout << "Tesis no encontrada.\n";
    }
}


void modificarAdmin() {
    string id;
    cout << "Ingrese ID del administrador a modificar: ";
    cin >> id;
    string nombre = leerCadena("Nuevo nombre: ");
    string contrasenia = leerCadena("Nueva contrasenia: ");
    Administrador nuevosDatos(id, nombre, contrasenia);
    if (listaAdmins.modificarPorID(id, nuevosDatos)) {
        cout << "Administrador modificado correctamente.\n";
        guardarAdmin(nuevosDatos);
    }
    else {
        cout << "Administrador no encontrado.\n";
    }
}

void modificarLector() {
	string id;
	cout << "Ingrese ID del lector a modificar: ";
	cin >> id;
	string nombre = leerCadena("Nuevo nombre: ");
	string contrasenia = leerCadena("Nueva contrasenia: ");
	Lector nuevosDatos(id, nombre, contrasenia);
	if (listaLectores.modificarPorID(id, nuevosDatos)) {
		cout << "Lector modificado correctamente.\n";
		guardarLector(nuevosDatos);
	}
	else {
		cout << "Lector no encontrado.\n";
	}
}

void modificarBibliotecario() {
    string id;
    cout << "Ingrese ID del bibliotecario a modificar: ";
    cin >> id;
    string nombre = leerCadena("Nuevo nombre: ");
    string contrasenia = leerCadena("Nueva contrasenia: ");
    Bibliotecario nuevosDatos(id, nombre, contrasenia);
    if (listaBibliotecarios.modificarPorID(id, nuevosDatos)) {
        cout << "Bibliotecario modificado correctamente.\n";
        guardarBibliotecario(nuevosDatos);
    }
    else {
        cout << "Bibliotecario no encontrado.\n";
    }
}

void mostrarLibros() {
    cout << "\nLista de libros:\n";
	cout << listaLibros.tamano() << " libros registrados.\n";
    listaLibros.mostrarTodo();
}

void mostrarRevistas() {
    cout << "\nLista de revistas:\n";
    cout << listaRevistas.tamano() << " libros registrados.\n";
    listaRevistas.mostrarTodo();
}

void mostrarTesis() {
    cout << "\nLista de tesis:\n";
    cout << listaTesis.tamano() << " libros registrados.\n";
    listaTesis.mostrarTodo();
}

void mostrarLectores() {
	cout << "\nLista de lectores:\n";
	listaLectores.mostrarTodo();
}

void mostrarBibliotecarios() {
	cout << "\nLista de bibliotecarios:\n";
	listaBibliotecarios.mostrarTodo();
}

void mostrarAdmins() {
	cout << "\nLista de administradores:\n";
	listaAdmins.mostrarTodo();
}

void mostrarPrestamos() {
	cout << "\nLista de prestamos:\n";
	if (colaPrestamos.estaVacia()) {
		cout << "No hay prestamos registrados.\n";
	}
	else {
		cout << colaPrestamos.tamanio() << " prestamos registrados.\n";
		colaPrestamos.mostrarTodo();
	}
}


void dibujarArbol(NodoArbol<Multa>* nodo, string prefijo = "", bool esIzquierdo = true) {


    if (nodo == nullptr) return;

    cout << prefijo;
    cout << (esIzquierdo ? "|-- " : "\\-- ");
    cout << " S/." << nodo->dato.getMonto() << " (" << nodo->dato.getIdMulta() << ")" << endl;

    dibujarArbol(nodo->izq, prefijo + (esIzquierdo ? "|   " : "    "), true);
    dibujarArbol(nodo->der, prefijo + (esIzquierdo ? "|   " : "    "), false);
}


void mostrarPrestamosPorLector(const string& idLector) {
	cout << "\nPrestamos del lector con ID " << idLector << ":\n";
	if (colaPrestamos.estaVacia()) {
		cout << "No hay prestamos registrados.\n";
		return;
	}
	Nodo<Prestamo>* actual = colaPrestamos.getFrente();
	bool encontrado = false;
	while (actual != nullptr) {
		if (actual->dato.getSolicitante()->getId() == idLector) {
			encontrado = true;

            actual->dato.detallesPrestamo();
            
		}
		actual = actual->siguiente;
	}
	if (!encontrado) {
		cout << "No se encontraron prestamos para el lector con ID " << idLector << ".\n";
	}
}


void insertarEnHashOrdenadoRecFechaPrestamo(NodoArbol<Prestamo>* nodo, HashTable<Prestamo>& tabla, int& indice, string& ultimaFecha) {
    if (nodo != nullptr) {
        insertarEnHashOrdenadoRecFechaPrestamo(nodo->izq, tabla, indice, ultimaFecha);

        if (nodo->dato.getEstado() == "Confirmado") {
            string fechaActual = nodo->dato.getFecha();  // 🔹 Fecha de préstamo

            if (fechaActual != ultimaFecha) {
                ultimaFecha = fechaActual;
                indice++;
            }

            tabla.insertarEnCubeta(nodo->dato, indice);
        }

        insertarEnHashOrdenadoRecFechaPrestamo(nodo->der, tabla, indice, ultimaFecha);
    }
}


void insertarEnHashOrdenadoRecFechaVencimiento(NodoArbol<Prestamo>* nodo, HashTable<Prestamo>& tabla, int& indice, string& ultimaFecha) {
    if (nodo != nullptr) {
        insertarEnHashOrdenadoRecFechaVencimiento(nodo->izq, tabla, indice, ultimaFecha);

        if (nodo->dato.getEstado() == "Confirmado") {
            string fechaActual = nodo->dato.getFechaVencimiento().toString();  // 🔹 Fecha de vencimiento

            if (fechaActual != ultimaFecha) {
                ultimaFecha = fechaActual;
                indice++;
            }

            tabla.insertarEnCubeta(nodo->dato, indice);
        }

        insertarEnHashOrdenadoRecFechaVencimiento(nodo->der, tabla, indice, ultimaFecha);
    }
}
void generarTablaPorFechaVencimiento(Cola<Prestamo>& cola, HashTable<Prestamo>& tablaOrdenada) {
    ArbolBinario<Prestamo> arbol;

    Nodo<Prestamo>* actual = cola.getFrente();
    while (actual != nullptr) {
        arbol.insertar(actual->dato);  // Usa sobrecarga < con getFechaVencimiento()
        actual = actual->siguiente;
    }

    int indice = -1;
    string ultimaFecha = "";
    insertarEnHashOrdenadoRecFechaVencimiento(arbol.getRaiz(), tablaOrdenada, indice, ultimaFecha);
}

void generarTablaPorFechaPrestamo(Cola<Prestamo>& cola, HashTable<Prestamo>& tablaOrdenada) {
    ArbolBinario<Prestamo> arbol;

    Nodo<Prestamo>* actual = cola.getFrente();
    while (actual != nullptr) {
        arbol.insertar(actual->dato);  // Usa < basado en fecha de préstamo
        actual = actual->siguiente;
    }

    int indice = -1;
    string ultimaFecha = "";
    insertarEnHashOrdenadoRecFechaPrestamo(arbol.getRaiz(), tablaOrdenada, indice, ultimaFecha);
}


void administrarPrestamos() {
    cout << "\nAdministrar prestamos:\n";
    if (colaPrestamos.estaVacia()) {
        cout << "No hay prestamos registrados.\n";
        return;
    }

    colaPrestamos.mostrarTodo();

    string idPrestamo;
    cout << "Ingrese el ID del prestamo a administrar: ";
    cin >> idPrestamo;

    Nodo<Prestamo>* prestamo = colaPrestamos.hallarID(idPrestamo);
    if (!prestamo) {
        cout << "Prestamo no encontrado.\n";
        return;
    }

    cout << "Detalles del prestamo:\n";
    prestamo->dato.detallesPrestamo();

    int opcion;
    cout << "Seleccione una opcion:\n";
    cout << "1. Confirmar prestamo\n";
    cout << "2. Denegar prestamo\n";
    cout << "0. Salir\n";
    cin >> opcion;

    if (opcion == 1) {
        RecursoBibliografico* recurso = prestamo->dato.getRecurso();
        int stockActual = recurso->getStock();

      
        if (stockActual > 0) {
            recurso->setStock(stockActual - 1);
            prestamo->dato.setEstado("Confirmado");
            cout << "Prestamo confirmado. Nuevo stock: " << recurso->getStock() << "\n";

            string idRecurso = recurso->getId();
            string prefijo = idRecurso.substr(0, 4);

            if (prefijo == "IDLI") {
                guardarLibrosEnArchivo(listaLibros);
            }
            else if (prefijo == "IDRE") {
               guardarRevistasEnArchivo(listaRevistas);
            }
            else if (prefijo == "IDTE") {
                guardarTesisEnArchivo(listaTesis);
            }

            // Aquí genera tabla y guarda
            HashTable<Prestamo> tablaConfirmados;
            generarTablaPorFechaPrestamo(colaPrestamos, tablaConfirmados);
            guardarPrestamosConfirmadosDesdeHashTable(tablaConfirmados);

            // Generar multa simulada
            string idMulta = generarID("multa", rand() % 100 + 1);
            Multa multaSimulada(idMulta, &(prestamo->dato)); 

            arbolMultasSimuladas.insertar(multaSimulada);

            // Guardar todo el árbol de multas en el archivo
            guardarMultasEnArchivo(arbolMultasSimuladas);


        }
        else {
            cout << "No se puede confirmar el préstamo. Stock agotado.\n";
        }
    }
    else if (opcion == 2) {
        prestamo->dato.setEstado("Denegado");
        guardarTodosLosPrestamosEnArchivo(colaPrestamos); 
        cout << "Prestamo denegado.\n";
    }

}

void mostrarProximoVencimiento(Cola<Prestamo>& cola) {
    ControlVencimientos heap;

    Nodo<Prestamo>* actual = cola.getFrente();
    while (actual != nullptr) {
        if (actual->dato.getEstado() == "Confirmado") {
            heap.agregarPrestamo(&actual->dato);
        }
        actual = actual->siguiente;
    }

    Prestamo* p = heap.obtenerMasUrgente();
    if (p) {
        cout << "Próximo préstamo por vencer:\n";
        cout << "ID: " << p->getId()
            << ", Solicitante: " << p->getSolicitante()->getNombre()
            << ", Título: " << p->getRecurso()->getTitulo()
            << ", Fecha de vencimiento: " << p->getFechaVencimiento().toString()
            << ", Estado: " << p->getEstado()
            << endl;
    }
    else {
        cout << "No hay préstamos confirmados.\n";
    }
}
void pausar() {
    cout << "\nPresione cualquier tecla para continuar...";
    _getch();
}

int extraerAnio(const string& fecha) {
    return stoi(fecha);
}

template <typename T>
int particionPorValoracion(ListaSimple<T>& lista, int p, int r) {
    int pivote = lista.getPorIndice(r).getValoracion(); // Costo: n (getPorIndice) + 1 (.getValoracion) + 1 (asignación) = n + 2
    int i = p - 1; // 2

    for (int j = p; j < r; ++j) { // ? 1 + (r - p)(1 + INTERNA + 2)
        if (lista.getPorIndice(j).getValoracion() <= pivote) { // ? n + 1 (valoracion) + 1 (comparación)
            i++; // 1
            T tempI = lista.getPorIndice(i); //n
            T tempJ = lista.getPorIndice(j); //n
            lista.setPorIndice(i, tempJ); //n
            lista.setPorIndice(j, tempI); //n
        }
    }

    T tempI = lista.getPorIndice(i + 1); //n
    T tempR = lista.getPorIndice(r); //n
    lista.setPorIndice(i + 1, tempR); //n 
    lista.setPorIndice(r, tempI); //n 

    return i + 1;
    //  n + 4 + 6n*n + 3n + 4n = 6n*n + 8n + 4
    // O(n^2)
}

template <typename T>
void quickSortPorValoracion(ListaSimple<T>& lista, int p, int r) {
    if (p < r) {
        int q = particionPorValoracion(lista, p, r);  // O(n*n)
        quickSortPorValoracion(lista, p, q - 1);
        quickSortPorValoracion(lista, q + 1, r);
    }
}

template <typename T>
int particionPorAnio(ListaSimple<T>& lista, int p, int r) {
    int anioPivote = extraerAnio(lista.getPorIndice(r).getFecha()); // Costo: n (getPorIndice) + 1 (.getFecha) + 1 (asignación) = n + 2
    int i = p - 1; // 2

    for (int j = p; j < r; ++j) { // ? 1 + (r - p)(1 + INTERNA + 2)
        if (extraerAnio(lista.getPorIndice(j).getFecha()) <= anioPivote) { // ? n + 1 (Fecha) + 1 (comparación)
            i++; // 1
            T tempI = lista.getPorIndice(i);  //n
            T tempJ = lista.getPorIndice(j); //n
            lista.setPorIndice(i, tempJ);  //n
            lista.setPorIndice(j, tempI);  //n
        }
    }

    T tempI = lista.getPorIndice(i + 1);  //n
    T tempR = lista.getPorIndice(r);  //n
    lista.setPorIndice(i + 1, tempR);  //n
    lista.setPorIndice(r, tempI);  //n

    return i + 1;
    //  n + 4 + 6n*n + 3n + 4n = 6n*n + 8n + 4
    // O(n^2)
}

template <typename T>
void quickSortPorAnio(ListaSimple<T>& lista, int p, int r) {
    if (p < r) { // 1 comparación ? 1
        int q = particionPorAnio(lista, p, r); // 1 asignación + llamada a función ? O(n*n) si getPorIndice = O(n)
        quickSortPorAnio(lista, p, q - 1); 
        quickSortPorAnio(lista, q + 1, r);
    }
}


template <typename T>
void merge(ListaSimple<T>& lista, int izq, int mid, int der) {
    int n1 = mid - izq + 1; // 2
    int n2 = der - mid;  // 2

    T* L = new T[n1]; // 1
    T* R = new T[n2]; // 1

    for (int i = 0; i < n1; ++i) // 1 + n1(1 + INTERNA + 2)
        L[i] = lista.getPorIndice(izq + i);  // 1 +O(n) acceso + 1  = n + 2
    for (int j = 0; j < n2; ++j)   // 1 + n2(1 + INTERNA + 2)
        R[j] = lista.getPorIndice(mid + 1 + j);  // 2  + O(n) + 1  = n + 3

    int i = 0, j = 0, k = izq; // 3
    while (i < n1 && j < n2) { // 2
        if (L[i].getValoracion() <= R[j].getValoracion()) { // 2 accesos + 2 llamadas + 1 comparación = 5
            lista.setPorIndice(k++, L[i++]); //  O(n) acceso + 2 incrementos = n + 2
        }
        else {
            lista.setPorIndice(k++, R[j++]); // O(n) acceso + 2 incrementos = n + 2
        }
    }

    while (i < n1) // n
        lista.setPorIndice(k++, L[i++]); //  O(n) + 2 incrementos = n + 2
    while (j < n2) // n
        lista.setPorIndice(k++, R[j++]); // O(n) + 2 incrementos = n + 2

    delete[] L; // 1
    delete[] R; // 1

}

template <typename T>
void OrdenamientoMergeporValoracionRecursoBibliografico(ListaSimple<T>& lista, int izq, int der) {
    if (izq < der) { // 1 comparación ? 1
        int mid = (izq + der) / 2;  // 2 sumas + 1 división + 1 asignación = 4
        OrdenamientoMergeporValoracionRecursoBibliografico(lista, izq, mid);
        OrdenamientoMergeporValoracionRecursoBibliografico(lista, mid + 1, der);
        merge(lista, izq, mid, der); // llamada a merge ? O(n²)
    }
}

void gestionarUsuarios(const string& tipo, int opcion) {
    if (opcion == 1) {
        if (tipo == "lector") registrarLector();
        else if (tipo == "bibliotecario") registrarBibliotecario();
        else if (tipo == "administrador") registrarAdministrador();
        else cout << "Tipo de usuario no valido.\n";
    }
    else if(opcion == 2){
        if (tipo == "lector") mostrarLectores();
        else if (tipo == "bibliotecario") mostrarBibliotecarios();
        else if (tipo == "administrador") mostrarAdmins();
        else cout << "Tipo de usuario no valido.\n";
    }
    else if (opcion == 3) {
        if (tipo == "lector") elimnarLector();
        else if (tipo == "bibliotecario") eliminarBibliotecario();
        else if (tipo == "administrador") eliminarAdmin();
        else cout << "Tipo de usuario no valido.\n";
    }
    else if (opcion == 4) {
        if (tipo == "lector") modificarLector();
        else if (tipo == "bibliotecario") modificarBibliotecario();
        else if (tipo == "administrador") modificarAdmin();
        else cout << "Tipo de usuario no valido.\n";
    }
    pausar();
}



void gestionarRecursos(const string& tipo, int opcion) {
    if (opcion == 1) {
        if (tipo == "libro") registrarLibro();
        else if (tipo == "revista") registrarRevista();
        else if (tipo == "tesis") registrarTesis();
        else cout << "Tipo de recurso no valido.\n";
    }
    else if (opcion == 2) {
        if (tipo == "libro") mostrarLibros();
        else if (tipo == "revista") mostrarRevistas();
        else if (tipo == "tesis") mostrarTesis();
        else cout << "Tipo de recurso no valido.\n";
    }
    else if (opcion == 3) {
        if (tipo == "libro") eliminarLibro();
        else if (tipo == "revista") eliminarRevista();
        else if (tipo == "tesis") eliminarTesis();
        else cout << "Tipo de recurso no valido.\n";
    }
    else if (opcion == 4) {
        if (tipo == "libro") modificarLibro();
        else if (tipo == "revista") modificarRevista();
        else if (tipo == "tesis") modificarTesis();
        else cout << "Tipo de recurso no valido.\n";
    }
    else if (opcion == 5) {
        if (tipo == "libro") {
            OrdenamientoMergeporValoracionRecursoBibliografico(listaLibros,0,listaLibros.tamano()-1);
            mostrarLibros();
        }
        else if (tipo == "revista") {
            OrdenamientoMergeporValoracionRecursoBibliografico(listaRevistas, 0, listaRevistas.tamano() - 1);
            mostrarLibros();
        }
        else if (tipo == "tesis") {
            OrdenamientoMergeporValoracionRecursoBibliografico(listaTesis, 0, listaTesis.tamano() - 1);
            mostrarLibros();
        }   
        else cout << "Tipo de recurso no valido.\n";
    }
    else if (opcion == 6) {
        if (tipo == "libro") {
            quickSortPorValoracion(listaLibros, 0, listaLibros.tamano() - 1);
            mostrarLibros();
        }
        else if (tipo == "revista") {
            quickSortPorValoracion(listaRevistas, 0, listaRevistas.tamano() - 1);
            mostrarLibros();
        }
        else if (tipo == "tesis") {
            quickSortPorValoracion(listaTesis, 0, listaTesis.tamano() - 1);
            mostrarLibros();
        }
        else cout << "Tipo de recurso no valido.\n";
    }
    else if (opcion == 7) {
        if (tipo == "libro") {
            quickSortPorAnio(listaLibros, 0, listaLibros.tamano() - 1);
            mostrarLibros();
        }
        else if (tipo == "revista") {
            quickSortPorAnio(listaRevistas, 0, listaRevistas.tamano() - 1);
            mostrarLibros();
        }
        else if (tipo == "tesis") {
            quickSortPorAnio(listaTesis, 0, listaTesis.tamano() - 1);
            mostrarLibros();
        }
        else cout << "Tipo de recurso no valido.\n";
    }
    pausar();
}




void Ejecutar_menuLector(const string& id, const string& nombre, const string& contrasenia) {
    Lector lector(id, nombre, contrasenia);
    int opcionLECTOR;
    string tipo;
    do {
        system("cls");
        cout << "Bienvenido " << nombre << "\n";
        lector.menuLector();
        cout << "Ingrese una opcion: ";
        cin >> opcionLECTOR;
        cin.ignore();
        switch (opcionLECTOR) {
        case 1:
            cout << "Ingrese tipo de recurso (libro|revista|tesis): ";
            cin >> tipo;
			cin.ignore();
			if (tipo == "libro") {
				mostrarLibros();
			}
			else if (tipo == "revista") {
				mostrarRevistas();
			}
			else if (tipo == "tesis") {
				mostrarTesis();
			}
			else {
				cout << "Tipo de recurso no valido.\n";
			}
            break;

        case 2:
            registrarPrestamo();
            break;
        case 3:
            mostrarPrestamosPorLector(lector.getId());
            break;
        case 4:
            construirGrafoDeLibrosPorGenero();
			cout << "Ingrese el ID de libros a consultar: ";
			cin >> tipo;
			cout << "Grafo de libros por genero construido.\n";
            mostrarRecursosRelacionados(tipo);
            break;
        case 5:
            construirGrafoDeLibrosPorAutor();
            cout << "Ingrese el ID de libros a consultar: ";
            cin >> tipo;
            cout << "Grafo de libros por autor construido.\n";
            mostrarRecursosRelacionados(tipo);
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
        pausar();
    } while (opcionLECTOR != 0);
}


void Ejectuar_menuAdministrador(const string& id, const string& nombre, const string& contrasenia) {
    Administrador admin(id, nombre, contrasenia);
    int opcionADMIN;
    string tipo;

    do {
        system("cls");
        cout << "Bienvenido " << nombre << "\n";
        admin.menuAdministrador();
        cout << "Ingrese una opción: ";
        cin >> opcionADMIN;
        cin.ignore();

        switch (opcionADMIN)
        {
        case 1: {
            int opcion;
            string tipo;
            do {
                system("cls");
                cout << "Bienvenido " << nombre << "\n";
                admin.menuGestionUsuarios();
                cout << "Ingrese una opcion: ";
                cin >> opcion;
                cin.ignore();

                if (opcion >= 1 && opcion <= 4) {
                    cout << "Ingrese tipo de recurso (lector|bibliotecario|administrador): ";
                    cin >> tipo;
                    cin.ignore();
                }

                gestionarRecursos(tipo, opcion);

            } while (opcion != 0);
            break;
        }

        case 2:
            cout << "Arbol de Multas (por monto):" << endl;
            if (arbolMultasSimuladas.getRaiz() == nullptr) {
                cout << "No hay multas en el arbol.\n";
            }
            else {
                dibujarArbol(arbolMultasSimuladas.getRaiz());
            }
            system("pause");
            break;

        default:
            break;
        }

    } while (opcionADMIN != 0);

}


void Ejectuar_menuBibliotecario(const string& id, const string& nombre, const string& contrasenia) {
    Bibliotecario bibliotecario(id, nombre, contrasenia);
    int opcionBIBLIOTECARIO;
    do {
        system("cls");
        cout << "Bienvenido " << nombre << "\n";
        bibliotecario.menuBibliotecario();
        cout << "Ingrese una opcion: ";
        cin >> opcionBIBLIOTECARIO;
        cin.ignore();
        switch (opcionBIBLIOTECARIO) {
        case 1:
            mostrarPrestamos();
            break;
        case 2:
            administrarPrestamos();
            break;
        case 3: {
            int opcion;
            string tipo;
            do {
                system("cls");
                cout << "Bienvenido " << nombre << "\n";
                bibliotecario.menuGestionarRecursosBibliograficos();
                cout << "Ingrese una opcion: ";
                cin >> opcion;
                cin.ignore();

                if (opcion >= 1 && opcion <= 7) {
                    cout << "Ingrese tipo de recurso (libro|revista|tesis): ";
                    cin >> tipo;
                    cin.ignore();
                }

                gestionarRecursos(tipo, opcion);

            } while (opcion != 0);
            break;
            }
        case 4: {
            HashTable<Prestamo> tablaPorFechaPrestamo;
            generarTablaPorFechaPrestamo(colaPrestamos, tablaPorFechaPrestamo);

            cout << "\n==== Tabla ordenada por fecha de préstamo ====\n";
            tablaPorFechaPrestamo.mostrar();

            guardarPrestamosConfirmadosDesdeHashTable(tablaPorFechaPrestamo);

            int opcionSub;
            do {
                cout << "\nOpciones:\n";
                cout << "1. Buscar prestamo por ID\n";
                cout << "2. Salir\n";
                cout << "Ingrese opcion: ";
                cin >> opcionSub;
                cin.ignore();

                if (opcionSub == 1) {
                    string idBuscado;
                    cout << "Ingrese el ID del préstamo: ";
                    getline(cin >> ws, idBuscado);

                    Prestamo* encontrado = tablaPorFechaPrestamo.buscar(idBuscado);

                    if (encontrado) {
                        cout << "\nPréstamo encontrado:\n";
                        encontrado->detallesPrestamo();
                    }
                    else {
                        cout << "No se encontro un préstamo con ese ID.\n";
                    }
                }

            } while (opcionSub != 2);
            break;
        }
        case 5: {
            HashTable<Prestamo> tablaPorFechaVencimiento;
            generarTablaPorFechaVencimiento(colaPrestamos, tablaPorFechaVencimiento);

            cout << "\n==== Tabla ordenada por fecha de vencimiento ====\n";
            tablaPorFechaVencimiento.mostrar();
                
            guardarPrestamosConfirmadosDesdeHashTable(tablaPorFechaVencimiento);

            int opcionSub;
            do {
                cout << "\nOpciones:\n";
                cout << "1. Buscar préstamo por ID\n";
                cout << "2. Salir\n";
                cout << "Ingrese opción: ";
                cin >> opcionSub;
                cin.ignore();

                if (opcionSub == 1) {
                    string idBuscado;
                    cout << "Ingrese el ID del préstamo: ";
                    getline(cin >> ws, idBuscado);

                    Prestamo* encontrado = tablaPorFechaVencimiento.buscar(idBuscado);

                    if (encontrado) {
                        cout << "\nPrestamo encontrado:\n";
                        encontrado->detallesPrestamo();
                    }
                    else {
                        cout << "No se encontró un prestamo con ese ID.\n";
                    }
                }

            } while (opcionSub != 2);
            break;
        }

        case 6: {
            mostrarProximoVencimiento(colaPrestamos);
            break;
        }

        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
        pausar();
    } while (opcionBIBLIOTECARIO != 0);
}

void iniciarSesionLector() {
    string nombre, contrasenia;
    cout << "Ingrese su nombre de usuario: ";
    cin >> nombre;
    cout << "Ingrese su contrasenia: ";
    cin >> contrasenia;

    ifstream archivo("archivos_txt/lectores.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de lectores.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);

        string id = linea.substr(0, pos1);
        string nombreArchivo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string contraseniaArchivo = linea.substr(pos2 + 1);

        if (nombre == nombreArchivo && contrasenia == contraseniaArchivo) {
            cout << "Inicio de sesion exitoso.\n";
            archivo.close();
            Ejecutar_menuLector(id, nombreArchivo, contraseniaArchivo);
            return;
        }
    }

    cout << "Usuario o contrasena incorrectas\n";
    archivo.close();
    
}

void iniciarSesionAdministrador() {
	string nombre, contrasenia;
	cout << "Ingrese su nombre de usuario: ";
	cin >> nombre;
	cout << "Ingrese su contrasenia: ";
	cin >> contrasenia;
	ifstream archivo("archivos_txt/admins.txt");
	if (!archivo.is_open()) {
		cout << "No se pudo abrir el archivo de administradores.\n";
		return ;
	}
	string linea;
	while (getline(archivo, linea)) {
		size_t pos1 = linea.find('|');
		size_t pos2 = linea.find('|', pos1 + 1);
		string id = linea.substr(0, pos1);
		string nombreArchivo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
		string contraseniaArchivo = linea.substr(pos2 + 1);
		if (nombre == nombreArchivo && contrasenia == contraseniaArchivo) {
			cout << "Inicio de sesion exitoso.\n";
			archivo.close();
			Ejectuar_menuAdministrador(id, nombreArchivo, contraseniaArchivo);
            return;
		}
	}

    cout << "Usuario o contrasena incorrectas\n";
	archivo.close();

}

void iniciarSesionBibliotecario() {
	string nombre, contrasenia;
	cout << "Ingrese su nombre de usuario: ";
	cin >> nombre;
	cout << "Ingrese su contrasenia: ";
	cin >> contrasenia;
	ifstream archivo("archivos_txt/bibliotecarios.txt");
	if (!archivo.is_open()) {
		cout << "No se pudo abrir el archivo de bibliotecarios.\n";
		return;
	}
	string linea;
	while (getline(archivo, linea)) {
		size_t pos1 = linea.find('|');
		size_t pos2 = linea.find('|', pos1 + 1);
		string id = linea.substr(0, pos1);
		string nombreArchivo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
		string contraseniaArchivo = linea.substr(pos2 + 1);
		if (nombre == nombreArchivo && contrasenia == contraseniaArchivo) {
			cout << "Inicio de sesion exitoso.\n";
			archivo.close();
			Ejectuar_menuBibliotecario(id, nombreArchivo, contraseniaArchivo);
            return;
		}
	}

    cout << "Usuario o contrasena incorrectas\n";
	archivo.close();
}


void marcarIDsUsados(bool usados[100], const string& archivoNombre, const string& prefijo) {
    ifstream archivo(archivoNombre);
    string linea;
    while (getline(archivo, linea)) {
        if (linea.substr(0, prefijo.size()) == prefijo) {
            string numStr = linea.substr(prefijo.size(), 2);
            try {
                int num = stoi(numStr);
                if (num >= 1 && num <= 99)
                    usados[num] = true;
            }
            catch (...) {}
        }
    }
    archivo.close();
}

void generarDatasetLibros(int cantidad, ListaSimple<libro>& listaLibros) {
    srand(time(0));
    bool usados[100] = { false };
    marcarIDsUsados(usados, "archivos_txt/libros.txt", "IDLI");

    // Datos base
    string titulos[] = {
        "Cien Años de Soledad", "El Principito", "1984", "Don Quijote", "Rayuela",
        "La Odisea", "Fahrenheit 451", "Crimen y Castigo", "Ulises", "Orgullo y Prejuicio",
        "El Gran Gatsby", "Matar a un Ruiseñor", "Lolita", "La Metamorfosis", "La Iliada",
        "El Retrato de Dorian Gray", "La Sombra del Viento", "Los Miserables", "Drácula", "El Hobbit",
        "Hamlet", "Macbeth", "Romeo y Julieta", "El Viejo y el Mar", "En el Camino",
        "Pedro Páramo", "La Tregua", "Travesuras de la Niña Mala", "El Aleph", "El Perfume",
        "Tokio Blues", "Kafka en la orilla", "La insoportable levedad del ser", "La Carretera", "Ensayo sobre la ceguera",
        "2666", "Patria", "Los Pilares de la Tierra", "Juego de Tronos", "Dune",
        "Solaris", "Neuromante", "Un Mundo Feliz", "La Máquina del Tiempo", "Fundación",
        "El Nombre del Viento", "It", "Carrie", "Cementerio de Animales", "Misery"
    };

    string autores[] = {
        "García Márquez", "Saint-Exupéry", "Orwell", "Cervantes", "Cortázar",
        "Homero", "Bradbury", "Dostoyevski", "Joyce", "Austen",
        "Fitzgerald", "Harper Lee", "Nabokov", "Kafka", "Homero",
        "Wilde", "Ruiz Zafón", "Hugo", "Stoker", "Tolkien",
        "Shakespeare", "Shakespeare", "Shakespeare", "Hemingway", "Kerouac",
        "Juan Rulfo", "Mario Benedetti", "Vargas Llosa", "Borges", "Süskind",
        "Murakami", "Murakami", "Kundera", "McCarthy", "Saramago",
        "Bolaño", "Aramburu", "Follett", "George R. R. Martin", "Herbert",
        "Lem", "Gibson", "Huxley", "Wells", "Asimov",
        "Rothfuss", "Stephen King", "Stephen King", "Stephen King", "Stephen King"
    };

    string fechas[] = {
        "1967", "1943", "1949", "1605", "1963",
        "800 a.C.", "1953", "1866", "1922", "1813",
        "1925", "1960", "1955", "1915", "750 a.C.",
        "1890", "2001", "1862", "1897", "1937",
        "1603", "1606", "1597", "1952", "1957",
        "1955", "1960", "2006", "1949", "1985",
        "2000", "2002", "1984", "2006", "1995",
        "2004", "2016", "1989", "1996", "1965",
        "1961", "1984", "1932", "1895", "1951",
        "2007", "1986", "1974", "1983", "1987"
    };

    string generos[] = {
        "Novela", "Fábula", "Distopía", "Clásico", "Experimental",
        "Épico", "Ciencia Ficción", "Drama", "Modernismo", "Romance",
        "Contemporáneo", "Juvenil", "Psicológico", "Fantasía", "Tragedia",
        "Histórico", "Policíaco", "Suspenso", "Terror", "Ensayo",
        "Autobiografía", "Aventura", "Satírico", "Misterio", "Literatura femenina",
        "Narrativa", "Mitología", "Utopía", "Biografía", "Humor",
        "Romántico", "Sociología", "Filosofía", "Ciberpunk", "Thriller",
        "Político", "Viajes", "Guerra", "Tecnología", "Realismo mágico",
        "Gótico", "Drama histórico", "Teatro", "Crónica", "Didáctico",
        "Parodia", "Ético", "Cultural", "Lenguaje", "Neorrealismo"
    };

    string editoriales[] = {
        "Planeta", "Penguin", "Alianza", "SM", "Random House",
        "Anagrama", "Siruela", "Debolsillo", "Tusquets", "Espasa",
        "Salamandra", "Alfaguara", "RBA", "Gredos", "Edelvives",
        "Larousse", "Oxford", "Cambridge", "Norma", "Ediciones B",
        "Ariel", "Páginas de Espuma", "Taurus", "Crítica", "Paidós",
        "McGraw-Hill", "Siglo XXI", "Minotauro", "Destino", "Austral",
        "Grijalbo", "Acantilado", "Océano", "Emece", "Trotalibros",
        "Zig-Zag", "Kapelusz", "Pearson", "Loqueleo", "Hachette",
        "Kairós", "Morata", "Trillas", "Marcombo", "Montena",
        "Noguer", "Herder", "Lumen", "Galaxia Gutenberg", "Editorial FCE"
    };

    ifstream archivo("archivos_txt/libros.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string id, titulo, autor, fecha, valStr, genero, editorial, stockStr;

            getline(ss, id, '|');
            getline(ss, titulo, '|');
            getline(ss, autor, '|');
            getline(ss, fecha, '|');
            getline(ss, valStr, '|');
            getline(ss, genero, '|');
            getline(ss, editorial, '|');
            getline(ss, stockStr, '|');

            try {
                int valoracion = stoi(valStr);
                int stock = stoi(stockStr);

                libro l(id, titulo, autor, fecha, valoracion, genero, editorial, stock);
                listaLibros.insertarAlFinal(l);
            }
            catch (const std::exception& e) {
                cout << "❌ Error al procesar línea: " << linea << " (" << e.what() << ")\n";
            }
        }
        archivo.close();
    }

    for (int i = 0; i < cantidad; ++i) {
        string titulo = titulos[i % 5];
        string autor = autores[i % 5];
        string fecha = fechas[i % 5];
        string genero = generos[i % 5];
        string editorial = editoriales[i % 5];
        int valoracion = 1 + rand() % 5;

        libro nuevoLibro;
        nuevoLibro.setTitulo(titulo);
        nuevoLibro.setAutor(autor);
        nuevoLibro.setFecha(fecha);
        nuevoLibro.setValoracion(valoracion); 
        nuevoLibro.setGenero(genero);
        nuevoLibro.setEditorial(editorial);
        nuevoLibro.setStock(1);

        bool encontrado = false;
        Nodo<libro>* actual = listaLibros.getCabeza();

        while (actual != nullptr) {
            if (actual->dato.esIgualContenido(nuevoLibro)) {
                actual->dato.setStock(actual->dato.getStock() + 1);
                encontrado = true;
                break;
            }
            actual = actual->siguiente;
        }

        if (!encontrado) {
            int idNum = -1;
            for (int j = 1; j <= 99; ++j) {
                if (!usados[j]) {
                    usados[j] = true;
                    idNum = j;
                    break;
                }
            }

            if (idNum == -1) {
                cout << "IDs agotados para libros\n";
                break;
            }

            string nuevoID = generarID("libro", idNum);
            nuevoLibro.setId(nuevoID);
            listaLibros.insertarAlFinal(nuevoLibro);
        }
    }

    guardarLibrosEnArchivo(listaLibros);
    cout << "Libros generados y stock actualizado correctamente.\n";
}

void generarDatasetRevistas(int cantidad, ListaSimple<revista>& listaRevistas) {
    srand(time(0));
    bool usados[100] = { false };
    marcarIDsUsados(usados, "archivos_txt/revistas.txt", "IDRE");

    string titulos[] = {
       "Ciencia Hoy", "National Geographic", "Nature", "Forbes", "Muy Interesante",
       "Scientific American", "Time", "The Economist", "Popular Science", "PC World",
       "Wired", "IEEE Spectrum", "New Scientist", "Harvard Business Review", "MIT Technology Review",
       "Quo", "Discovery", "Astronomy", "Ecología y Medio Ambiente", "Investigación y Ciencia",
       "Revista de Historia", "Salud Total", "Mente y Cerebro", "Psicología Hoy", "Cultura Científica",
       "Geo", "Cosmos", "Tec Review", "Semana Económica", "Caretas",
       "The Lancet", "BMJ", "Computer Hoy", "Linux Magazine", "Historia National",
       "Revista de Ciencias Sociales", "Estudios Filosóficos", "Revista Andina", "Agronomía Peruana", "Medicina UNMSM",
       "Comunicación y Sociedad", "Revista Digital UDEP", "Boletín Estadístico", "Contabilidad Global", "Marketing Actual",
       "Gestión Empresarial", "Revista del Consumidor", "Derecho Público", "Jurídica", "Ingeniería Hoy", "Arquitectura Viva"
    };

    string autores[] = {
        "Equipo Editorial", "Expertos", "Investigadores", "Redacción", "Colaboradores",
        "Analistas", "Científicos", "Docentes", "Periodistas", "Académicos",
        "Estudiantes", "Miembros IEEE", "Psicólogos", "Economistas", "Ingenieros",
        "Editorial Forbes", "Biólogos", "Historiadores", "Astrónomos", "Educadores",
        "Físicos", "Sociólogos", "Filósofos", "Médicos", "Psicoanalistas",
        "Tecnólogos", "Especialistas", "Químicos", "Ecologistas", "Matemáticos",
        "Jueces", "Abogados", "Politólogos", "Lingüistas", "Antropólogos",
        "Pedagogos", "Neurólogos", "Epidemiólogos", "Contadores", "Publicistas",
        "Diseñadores", "Constructores", "Investigadores PUCP", "Investigadores UNI", "UNSA",
        "UDEP", "UCSUR", "ULIMA", "USMP", "UIGV"
    };

    string fechas[] = {
        "2020", "2021", "2022", "2023", "2024",
        "2019", "2018", "2017", "2016", "2015",
        "2014", "2013", "2012", "2011", "2010",
        "2009", "2008", "2007", "2006", "2005",
        "2004", "2003", "2002", "2001", "2000",
        "1999", "1998", "1997", "1996", "1995",
        "1994", "1993", "1992", "1991", "1990",
        "1989", "1988", "1987", "1986", "1985",
        "1984", "1983", "1982", "1981", "1980",
        "1979", "1978", "1977", "1976", "1975"
    };

    string ISSNs[] = {
        "1234-5678", "2345-6789", "3456-7890", "4567-8901", "5678-9012",
        "6789-0123", "7890-1234", "8901-2345", "9012-3456", "0123-4567",
        "1122-3344", "2233-4455", "3344-5566", "4455-6677", "5566-7788",
        "6677-8899", "7788-9900", "8899-0011", "9900-1122", "0011-2233",
        "ABCD-1234", "EFGH-5678", "IJKL-9012", "MNOP-3456", "QRST-7890",
        "UVWX-2345", "YZAB-6789", "CDEF-0123", "GHIJ-4567", "KLMN-8901",
        "OPQR-2345", "STUV-6789", "WXYZ-0123", "PQRS-4567", "LMNO-8901",
        "ZXCV-1234", "ASDF-5678", "QWER-9012", "TYUI-3456", "GHJK-7890",
        "BNMQ-2345", "VCAZ-6789", "LOPM-0123", "IKUJ-4567", "UHYN-8901",
        "OLKD-2345", "POIU-6789", "MLKJ-0123", "NJHB-4567", "BQWE-8901"
    };

    string clasificaciones[] = {
        "Divulgación", "Científica", "Tecnología", "Economía", "Educativa",
        "Cultura", "Historia", "Salud", "Psicología", "Ecología",
        "Astronomía", "Física", "Química", "Matemáticas", "Ingeniería",
        "Derecho", "Contabilidad", "Empresarial", "Marketing", "Literatura",
        "Lingüística", "Social", "Antropología", "Política", "Medicina",
        "Filosofía", "Educación", "Sociología", "Arte", "Cómic",
        "Robótica", "Programación", "Ciberseguridad", "Criminalística", "Forense",
        "Veterinaria", "Nutrición", "Odontología", "Enfermería", "Bioética",
        "Fotografía", "Diseño", "Arquitectura", "Urbanismo", "Religión",
        "Turismo", "Transporte", "Geografía", "Geología", "Ingeniería Civil"
    };


    // Leer archivo existente
    ifstream archivo("archivos_txt/revistas.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string id, titulo, autor, fecha, valStr, issn, clasif, stockStr;

            getline(ss, id, '|');
            getline(ss, titulo, '|');
            getline(ss, autor, '|');
            getline(ss, fecha, '|');
            getline(ss, valStr, '|');
            getline(ss, issn, '|');
            getline(ss, clasif, '|');
            getline(ss, stockStr, '|');

            try {
                int val = stoi(valStr);
                int stock = stoi(stockStr);

                revista r(id, titulo, autor, fecha, val, issn, clasif, stock);
                listaRevistas.insertarAlFinal(r);
            }
            catch (...) {
                cout << "Error al procesar línea de revista: " << linea << "\n";
            }
        }
        archivo.close();
    }

    for (int i = 0; i < cantidad; ++i) {
        revista nueva;
        nueva.setTitulo(titulos[i % 5]);
        nueva.setAutor(autores[i % 5]);
        nueva.setFecha(fechas[i % 5]);
        nueva.setValoracion(1 + rand() % 5);
        nueva.setISSN(ISSNs[i % 5]);
        nueva.setClasificacion(clasificaciones[i % 5]);
        nueva.setStock(1);

        bool encontrado = false;
        Nodo<revista>* actual = listaRevistas.getCabeza();
        while (actual) {
            if (actual->dato.esIgualContenido(nueva)) {
                actual->dato.setStock(actual->dato.getStock() + 1);
                encontrado = true;
                break;
            }
            actual = actual->siguiente;
        }

        if (!encontrado) {
            int idNum = -1;
            for (int j = 1; j <= 99; ++j) {
                if (!usados[j]) {
                    usados[j] = true;
                    idNum = j;
                    break;
                }
            }
            if (idNum == -1) {
                cout << "IDs agotados para revistas\n";
                break;
            }

            nueva.setId(generarID("revista", idNum));
            listaRevistas.insertarAlFinal(nueva);
        }
    }

    guardarRevistasEnArchivo(listaRevistas);
    cout << "Revistas generadas y stock actualizado correctamente.\n";
}


void generarDatasetTesis(int cantidad, ListaSimple<tesis>& listaTesis) {
    srand(time(0));
    bool usados[100] = { false };
    marcarIDsUsados(usados, "archivos_txt/tesis.txt", "IDTE");

    string titulos[] = {
        "Redes Neuronales", "Sistemas Distribuidos", "Criptografía Cuántica", "Realidad Aumentada", "Big Data",
        "Deep Learning", "Internet de las Cosas", "Blockchain", "Reconocimiento Facial", "Cómputo en la Nube",
        "Seguridad Informática", "Bases de Datos NoSQL", "Bioinformática", "Energías Renovables", "Análisis de Imágenes",
        "Inteligencia Artificial", "Minería de Datos", "Aprendizaje Automático", "Teoría de Grafos", "Simulación Molecular",
        "Control de Robots", "Algoritmos Evolutivos", "Computación Cuántica", "Mecatrónica", "Visión Computacional",
        "Lenguajes Formales", "Compiladores", "Videojuegos Educativos", "Realidad Virtual", "Sistemas Expertos",
        "Data Science", "Ingeniería Genética", "Procesamiento de Lenguaje Natural", "Finanzas Computacionales", "Matemática Discreta",
        "Electrónica Digital", "Telemedicina", "E-learning", "Ciberdefensa", "Criptografía Post-Cuántica",
        "Economía Digital", "Transformación Digital", "Neurociencia Computacional", "Bioingeniería", "Robótica Educativa",
        "Ingeniería del Software", "Sistemas Embebidos", "Inteligencia Ambiental", "Analítica Predictiva", "Ética en IA"
    };

    string autores[] = {
        "Ana Rojas", "Luis Salas", "María Díaz", "Pedro Castillo", "Jorge Fernández",
        "Lucía Gómez", "Carlos Herrera", "Patricia Méndez", "David Ruiz", "Andrea Salinas",
        "Renzo Torres", "Martina Paredes", "Sebastián Alva", "Fabiola Márquez", "Eduardo Chumpitaz",
        "Javier Lazo", "Melany Chávez", "Cristian Rosas", "Elena Zárate", "Rafael Gamboa",
        "Daniela Tello", "Iván Camargo", "Tatiana Mendoza", "Gustavo León", "Rocío Barrera",
        "Bruno Aguilar", "Celeste Velásquez", "Joaquín Rivas", "Noelia Farfán", "Oscar Mejía",
        "Alexandra Cubas", "Camilo Bravo", "Jimena Reátegui", "Valeria Llosa", "Martín Yauri",
        "Silvia Torres", "Enzo Poma", "Karina Quispe", "Luis Palma", "Paola Gutierrez",
        "Violeta Neyra", "Ximena Tuesta", "Cristian Delgado", "Irene Sotomayor", "Mateo Gonzales",
        "Victoria López", "Franco Vega", "Natalia Infante", "Luciano Vera", "Samantha Hoyos"
    };

    string fechas[] = {
        "2019", "2020", "2021", "2022", "2023",
        "2018", "2017", "2016", "2015", "2014",
        "2013", "2012", "2011", "2010", "2009",
        "2008", "2007", "2006", "2005", "2004",
        "2003", "2002", "2001", "2000", "1999",
        "1998", "1997", "1996", "1995", "1994",
        "1993", "1992", "1991", "1990", "1989",
        "1988", "1987", "1986", "1985", "1984",
        "1983", "1982", "1981", "1980", "1979",
        "1978", "1977", "1976", "1975", "1974"
    };

    string universidades[] = {
        "PUCP", "UNI", "UNMSM", "UPC", "UPCH",
        "USIL", "UDEP", "UCSUR", "USMP", "UIGV",
        "UNFV", "URP", "ULIMA", "UPN", "UTEC",
        "USAT", "UNSA", "UNPRG", "UNT", "UNAC",
        "UANCV", "UNHEVAL", "UNAJMA", "UNTRM", "UNJBG",
        "UNAP", "UNCP", "UNALM", "UCB", "UNIA",
        "UCSM", "ULADECH", "UNICA", "UMCH", "UCSP",
        "UAP", "UPSJB", "UPAO", "UCAL", "TECSUP",
        "ESAN", "UTP", "UTM", "UNAM", "UDEM",
        "ITAM", "ITESM", "UCA", "USAC", "UADY"
    };

    string paises[] = {
        "Perú", "Chile", "Argentina", "México", "Colombia",
        "Ecuador", "Bolivia", "Venezuela", "Paraguay", "Uruguay",
        "Brasil", "España", "Italia", "Alemania", "Francia",
        "Canadá", "Estados Unidos", "Portugal", "Reino Unido", "Suecia",
        "Noruega", "Finlandia", "Dinamarca", "Holanda", "Bélgica",
        "Austria", "Suiza", "Polonia", "Rusia", "China",
        "Japón", "India", "Australia", "Nueva Zelanda", "Sudáfrica",
        "Egipto", "Marruecos", "Nigeria", "Kenia", "Corea del Sur",
        "Tailandia", "Malasia", "Vietnam", "Indonesia", "Filipinas",
        "Irlanda", "Grecia", "Turquía", "Irán", "Israel"
    };


    // Leer archivo existente
    ifstream archivo("archivos_txt/tesis.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string id, titulo, autor, fecha, valStr, universidad, pais, stockStr;

            getline(ss, id, '|');
            getline(ss, titulo, '|');
            getline(ss, autor, '|');
            getline(ss, fecha, '|');
            getline(ss, valStr, '|');
            getline(ss, universidad, '|');
            getline(ss, pais, '|');
            getline(ss, stockStr, '|');

            try {
                int val = stoi(valStr);
                int stock = stoi(stockStr);

                tesis t(id, titulo, autor, fecha, val, universidad, pais, stock);
                listaTesis.insertarAlFinal(t);
            }
            catch (...) {
                cout << "Error al procesar línea de tesis: " << linea << "\n";
            }
        }
        archivo.close();
    }

    for (int i = 0; i < cantidad; ++i) {
        tesis nueva;
        nueva.setTitulo(titulos[i % 5]);
        nueva.setAutor(autores[i % 5]);
        nueva.setFecha(fechas[i % 5]);
        nueva.setValoracion(1 + rand() % 5);
        nueva.setUniversidad(universidades[i % 5]);
        nueva.setPais(paises[i % 5]);
        nueva.setStock(1);

        bool encontrado = false;
        Nodo<tesis>* actual = listaTesis.getCabeza();
        while (actual) {
            if (actual->dato.esIgualContenido(nueva)) {
                actual->dato.setStock(actual->dato.getStock() + 1);
                encontrado = true;
                break;
            }
            actual = actual->siguiente;
        }

        if (!encontrado) {
            int idNum = -1;
            for (int j = 1; j <= 99; ++j) {
                if (!usados[j]) {
                    usados[j] = true;
                    idNum = j;
                    break;
                }
            }
            if (idNum == -1) {
                cout << "IDs agotados para tesis\n";
                break;
            }

            nueva.setId(generarID("tesis", idNum));
            listaTesis.insertarAlFinal(nueva);
        }
    }

    guardarTesisEnArchivo(listaTesis);
    cout << "Tesis generadas y stock actualizado correctamente.\n";
}


void generarDatasetUsuarios(const string& tipo, int cantidad, ListaSimple<Usuario*>& listaUsuarios) {
    srand(time(0));
    bool usados[100] = { false };

    string archivoRuta;
    string prefijo;

    if (tipo == "lector") {
        archivoRuta = "archivos_txt/lectores.txt";
        prefijo = "IDLE";
    }
    else if (tipo == "bibliotecario") {
        archivoRuta = "archivos_txt/bibliotecarios.txt";
        prefijo = "IDBI";
    }
    else if (tipo == "administrador") {
        archivoRuta = "archivos_txt/administradores.txt";
        prefijo = "IDAD";
    }
    else {
        cout << "❌ Tipo de usuario no válido.\n";
        return;
    }

    marcarIDsUsados(usados, archivoRuta, prefijo);

    string nombres[] = {
        "Juan", "María", "Luis", "Ana", "Pedro", "Lucía", "Carlos", "Elena", "José", "Valeria",
        "Miguel", "Diana", "Rafael", "Patricia", "Sergio", "Andrea", "Alonso", "Camila", "Víctor", "Renata",
        "César", "Daniela", "Hugo", "Sofía", "Esteban", "Gabriela", "Martín", "Romina", "Joaquín", "Karla",
        "Julio", "Fabiola", "Felipe", "Natalia", "Andrés", "Mariela", "Roberto", "Alexa", "Francisco", "Milagros",
        "Bruno", "Fiorella", "Iván", "Celeste", "Mario", "Yuliana", "Axel", "Melanie", "Kevin", "Nicole"
    };

    for (int i = 0; i < cantidad; ++i) {
        string nombre = nombres[i % 50];
        string contrasenia = "pass" + to_string(rand() % 1000);

        int idNum = -1;
        for (int j = 1; j <= 99; ++j) {
            if (!usados[j]) {
                usados[j] = true;
                idNum = j;
                break;
            }
        }

        if (idNum == -1) {
            cout << "IDs agotados para " << tipo << "s\n";
            break;
        }

        string idGenerado = generarID(tipo, idNum);
        Usuario* nuevo;

        if (tipo == "lector")
            nuevo = new Lector(idGenerado, nombre, contrasenia);
        else if (tipo == "bibliotecario")
            nuevo = new Bibliotecario(idGenerado, nombre, contrasenia);
        else
            nuevo = new Administrador(idGenerado, nombre, contrasenia);

        listaUsuarios.insertarAlFinal(nuevo);
    }   

    if (tipo == "lector") {
        guardarLectoresEnArchivo(listaUsuarios);
    }
    else if (tipo == "bibliotecario") {
       guardarBibliotecariosEnArchivo(listaUsuarios);
    }
    else if (tipo == "administrador") {
       guardarAdministradoresEnArchivo(listaUsuarios);
    }

    cout << "Se creo" << cantidad << " usuarios (" << tipo << "s) generados correctamente.\n";
}

void generarDatasetUsuariosConPrestamosYMultas(
    int cantidadUsuarios,
    ListaSimple<Usuario*>& listaUsuarios,
    ListaSimple<RecursoBibliografico*>& recursos,
    Cola<Prestamo>& colaPrestamos,
    HashTable<Prestamo>& hashPrestamosConfirmados,
    ArbolBinario<Multa>& arbolMultas
) {
    srand(time(0));
    bool usados[100] = { false };
    marcarIDsUsados(usados, "archivos_txt/lectores.txt", "IDLE");

    string nombres[] = {
        "Juan", "María", "Luis", "Ana", "Pedro", "Lucía", "Carlos", "Elena", "José", "Valeria",
        "Miguel", "Diana", "Rafael", "Patricia", "Sergio", "Andrea", "Alonso", "Camila", "Víctor", "Renata",
        "César", "Daniela", "Hugo", "Sofía", "Esteban", "Gabriela", "Martín", "Romina", "Joaquín", "Karla",
        "Julio", "Fabiola", "Felipe", "Natalia", "Andrés", "Mariela", "Roberto", "Alexa", "Francisco", "Milagros",
        "Bruno", "Fiorella", "Iván", "Celeste", "Mario", "Yuliana", "Axel", "Melanie", "Kevin", "Nicole"
    };

    for (int i = 0; i < cantidadUsuarios; ++i) {
        // Crear lector
        string nombre = nombres[i % 50];
        string contrasenia = "pass" + to_string(rand() % 1000);

        int idNum = -1;
        for (int j = 1; j <= 99; ++j) {
            if (!usados[j]) {
                usados[j] = true;
                idNum = j;
                break;
            }
        }

        if (idNum == -1) {
            cout << "⚠ IDs agotados para lectores\n";
            break;
        }

        string idGenerado = generarID("lector", idNum);
        Lector* lector = new Lector(idGenerado, nombre, contrasenia);
        listaUsuarios.insertarAlFinal(lector);

        // Crear préstamo si hay recursos disponibles
        if (recursos.tamano() == 0) continue;

        RecursoBibliografico* recurso = recursos.getPorIndice(rand() % recursos.tamano());
        string idPrestamo = generarID("prestamo", 100 + rand() % 900);
        string fecha = Fecha().toString();

        Prestamo* prestamo = new Prestamo(idPrestamo, fecha, lector, recurso, "Confirmado");

        colaPrestamos.encolar(*prestamo);
        hashPrestamosConfirmados.insertar(*prestamo);

        // 33% probabilidad de multa
        if (rand() % 3 == 0) {
            string idMulta = generarID("multa", 100 + rand() % 900);
            Multa* multa = new Multa(idMulta, prestamo);  // <== CORREGIDO
            arbolMultas.insertar(*multa);
        }
    }

    // Guardado en archivos
    guardarLectoresEnArchivo(listaUsuarios);
    guardarTodosLosPrestamosEnArchivo(colaPrestamos);
    guardarPrestamosConfirmadosDesdeHashTable(hashPrestamosConfirmados);

    ofstream archivoMultas("archivos_txt/multas.txt");
    guardarMultasEnArchivoRecursivo(arbolMultas.getRaiz(), archivoMultas);
    archivoMultas.close();

    cout << "Dataset de lectores, préstamos confirmados y multas generado y guardado exitosamente.\n";
}
