#pragma once
#include "opciones.h"

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
            
            pausar();
            break;

        case 3:
            
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








