#pragma once
#include "opciones.h"
#include <vector>

void pausar() {
    cout << "\nPresione cualquier tecla para continuar...";
    _getch();
}

void mostrarMenuPrincipal() {
    cout << "|===============================================|\n";
    cout << "|------SISTEMA DE GESTION DE BIBLIOTECAS--------|\n";
    cout << "|                                               |\n";
    cout << "|    1. REGISTRAR USUARIO                       |\n";
    cout << "|    2. INGRESAR COMO LECTOR                    |\n";
    cout << "|    3. INGRESAR COMO ADMINISTRADOR             |\n";
    cout << "|    0. SALIR                                   |\n";
    cout << "|===============================================|\n";
    cout << "Ingrese una opcion: ";
}


// ===================================================================

struct Prestamo {
    string usuario;
    string recursoID;
    string tipo;
    string fecha;
};


vector<Prestamo> prestamos;

void guardarPrestamos() {
    ofstream archivo("prestamos.txt");
    for (const auto& p : prestamos) {
        archivo << p.usuario << ";" << p.recursoID << ";" << p.tipo << ";" << p.fecha << "\n";
    }
    archivo.close();
}

void cargarPrestamos() {
    ifstream archivo("prestamos.txt");
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        size_t pos1 = linea.find(';');
        size_t pos2 = linea.find(';', pos1 + 1);
        size_t pos3 = linea.find(';', pos2 + 1);

        Prestamo p;
        p.usuario = linea.substr(0, pos1);
        p.recursoID = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        p.tipo = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        p.fecha = linea.substr(pos3 + 1);

        prestamos.push_back(p);
    }
    archivo.close();
}

void solicitarPrestamo(const string& usuario) {
    mostrarLibros();
    string id;
    cout << "Ingrese ID del libro que desea prestar: ";
    cin >> id;

    // Verifica si el ID existe
    if (!listaLibros.existeID(id)) {
        cout << "El libro con ID " << id << " no existe.\n";
        return;
    }

    // Verifica si ya lo tiene prestado
    for (const auto& p : prestamos) {
        if (p.usuario == usuario && p.recursoID == id) {
            cout << "Ya has solicitado este libro anteriormente.\n";
            return;
        }
    }

    // Fecha simplificada
    string fecha = "2025-05-11"; // Aquí podrías automatizar con <ctime>

    Prestamo nuevo{ usuario, id, "libro", fecha };
    prestamos.push_back(nuevo);
    guardarPrestamos();

    cout << "Libro prestado correctamente.\n";
}

void verMisPrestamos(const string& usuario) {
    cout << "\nPréstamos de " << usuario << ":\n";
    bool encontrado = false;
    for (const auto& p : prestamos) {
        if (p.usuario == usuario) {
            cout << "- " << p.tipo << " ID: " << p.recursoID << ", Fecha: " << p.fecha << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No tienes préstamos registrados.\n";
    }
}


// ===================================================================



// ===================================================================

void menuLector(const string& nombreUsuario) {
    int opcion;
    string tipo;

    do {
        system("cls");
        cout << "|============= MENU DEL LECTOR ===============|\n";
        cout << "| Bienvenido, " << nombreUsuario << endl;
        cout << "| 1. Ver recursos disponibles                  |\n";
        cout << "| 2. Solicitar prestamo de libro              |\n";
        cout << "| 3. Ver mis prestamos                         |\n";
        cout << "| 0. Cerrar sesión                             |\n";
        cout << "|=============================================|\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            cout << "Ingrese tipo de recurso (libro|revista|tesis): ";
            cin >> tipo;
            cin.ignore();
            if (tipo == "libro") mostrarLibros();
            else if (tipo == "revista") mostrarRevistas();
            else if (tipo == "tesis") mostrarTesis();
            else cout << "Tipo no válido.\n";
            pausar();
            break;

        case 2:
            solicitarPrestamo(nombreUsuario);
            pausar();
            break;

        case 3:
            verMisPrestamos(nombreUsuario);
            pausar();
            break;

        case 0:
            cout << "Cerrando sesión...\n";
            break;

        default:
            cout << "Opción inválida.\n";
            pausar();
            break;
        }

    } while (opcion != 0);
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

void menuAdministrador(const string& nombre, const string& contrasenia) {
    Administrador admin(nombre, contrasenia);
    int opcionADMIN;
    string tipo;

    do {
        system("cls");
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

bool iniciarSesion(const string& tipo) {
    string nombre, contrasenia;
    cout << "Ingrese nombre de " << tipo << ": ";
    getline(cin, nombre);
    cout << "Ingrese contrasenia: ";
    getline(cin, contrasenia);

    unique_ptr<Usuario> usuario = make_unique<Usuario>(nombre, contrasenia);

    if (usuario->IniciarSesion(tipo)) {
        cout << "Bienvenido, " << nombre << ".\n";
        if (tipo == "Administrador") {
            menuAdministrador(nombre, contrasenia);
        }
        else if (tipo == "Lector") {
            menuLector(nombre);
        }
        return true;
    }
    else {
        cout << "Nombre o contrasenia incorrectos.\n";
        return false;
    }
}


inline string seleccionarTipoCuenta() {
    int opcionTipo;
    cout << "\nSeleccione tipo de cuenta:\n";
    cout << "1. Lector\n";
    cout << "2. Administrador\n";
    cout << "Opcion: ";
    cin >> opcionTipo;
    cin.ignore();

    switch (opcionTipo) {
    case 1: return "Lector";
    case 2: return "Administrador";
    default: cout << "Opcion invalida. Se usará 'Lector' por defecto.\n"; return "Lector";
    }
}

inline void registrarUsuario() {
    string tipo = seleccionarTipoCuenta();
    string nombre, contrasenia;

    cout << "Ingrese nombre del " << tipo << ": ";
    cin >> nombre;
    cout << "Ingrese contrasenia: ";
    cin >> contrasenia;

    Usuario usuario(nombre, contrasenia);
    if (usuario.ComprobarUsuario(tipo)) {
        cout << "El " << tipo << " ya esta registrado.\n";
    }
    else {
        usuario.AgregarUsuario(tipo);
    }
}

inline void iniciarSesionUsuario(const string& tipo) {
    if (!iniciarSesion(tipo)) {
        cout << "Nombre o contrasenia incorrectos.\n";
    }
}