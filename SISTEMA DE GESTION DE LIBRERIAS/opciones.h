#pragma once
#include "EstructurasDatos.h"
#include "lector.h"
#include "bibliotecario.h"
#include "administrador.h"
#include "libro.h"
#include "tesis.h"
#include "revista.h"
#include "archivos.h"

ListaSimple<libro> listaLibros;
ListaSimple<tesis> listaTesis;
ListaSimple<revista> listaRevistas;
ListaSimple<Administrador> listaAdmins;
ListaSimple<Lector> listaLectores;
ListaSimple<Bibliotecario> listaBibliotecarios;

Cola<Prestamo> colaPrestamos;

int obtenerUltimoID(const string& archivoNombre, const string& prefijo) {
    ifstream archivo(archivoNombre);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivoNombre << endl;
        return 0;
    }

    string linea;
    int maxID = 0;

    while (getline(archivo, linea)) {
        if (linea.substr(0, prefijo.size()) == prefijo) {
            string numStr = linea.substr(prefijo.size(), 2);
            try {
                int num = stoi(numStr);
                if (num > maxID) {
                    maxID = num;
                }
            }
            catch (...) {
                // Ignorar errores por si hay líneas mal formateadas
            }
        }
    }

    archivo.close();
    return maxID;
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
    int ultimoID = obtenerUltimoID("archivos_txt/libros.txt", "IDLI");
    string id = generarID("libro", ultimoID + 1);
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
    int ultimoID = obtenerUltimoID("archivos_txt/revistas.txt", "IDRE");
    string id = generarID("libro", ultimoID + 1);
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
    int ultimoID = obtenerUltimoID("archivos_txt/tesis.txt", "IDTE");
    string id = generarID("libro", ultimoID + 1);
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

    cout << "Préstamo registrado correctamente con ID: " << id << "\n";
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
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);
        size_t pos4 = linea.find('|', pos3 + 1);
        size_t pos5 = linea.find('|', pos4 + 1);
        size_t pos6 = linea.find('|', pos5 + 1);
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
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);
        size_t pos4 = linea.find('|', pos3 + 1);
        size_t pos5 = linea.find('|', pos4 + 1);
        size_t pos6 = linea.find('|', pos5 + 1);
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
		size_t pos1 = linea.find('|');
		size_t pos2 = linea.find('|', pos1 + 1);
		size_t pos3 = linea.find('|', pos2 + 1);
		size_t pos4 = linea.find('|', pos3 + 1);
		try {
			string id = linea.substr(0, pos1);
			string fecha = linea.substr(pos1 + 1, pos2 - pos1 - 1);
			string idLector = linea.substr(pos2 + 1, pos3 - pos2 - 1);
			string idRecurso = linea.substr(pos3 + 1, pos4 - pos3 - 1);
			string estado = linea.substr(pos4 + 1);
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
			}
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
                << lib.getValoracion() << "|" << lib.getGenero() << "|" << lib.getEditorial() << endl;
            actual = actual->siguiente;
        }

        archivo.close();
        cout << "Archivo actualizado.\n";

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
                << lib.getValoracion() << "|" << lib.getISSN() << "|" << lib.getClasificacion() << endl;
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
                << lib.getValoracion() << "|" << lib.getUniversidad() << "|" << lib.getPais() << endl;
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

void elimnarBibliotecario() {
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

void elimnarAdmin() {
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

void pausar() {
    cout << "\nPresione cualquier tecla para continuar...";
    _getch();
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
    pausar();
}

void Ejectuar_menuAdministrador(const string& id, const string& nombre, const string& contrasenia) {
    Administrador admin(id, nombre, contrasenia);
    int opcionADMIN;
    string tipo;

    do {
        system("cls");
        cout << "Bienvenido " << nombre << "\n";
        admin.menuAdministrador();
        cout << "Ingrese una opcion: ";
        cin >> opcionADMIN;
        cin.ignore();

        if (opcionADMIN >= 1 && opcionADMIN <= 4) {
            cout << "Ingrese tipo de recurso (libro|revista|tesis): ";
            cin >> tipo;
            cin.ignore();
        }

        gestionarRecursos(tipo, opcionADMIN);

    } while (opcionADMIN != 0);
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
            mostrarPrestamos();
            break;
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
        pausar();
    } while (opcionLECTOR != 0);
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
            // Mostrar prestamos solicitados
            cout << "Funcionalidad no implementada.\n";
            break;
        case 2:
            // Confirmar prestamo
            cout << "Funcionalidad no implementada.\n";
            break;
        case 3:
            // Denegar prestamo
            cout << "Funcionalidad no implementada.\n";
            break;
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

