#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <memory>
#include "Usuario.h"
#include "administrador.h"
#include "opciones.h"
#include "utils.h"
using namespace std;


int main() {
    cargarLibros("libros.txt");
    cargarRevistas("revistas.txt");
    cargarTesis("tesis.txt");

    char opcion;
    do {
        system("cls");
        mostrarMenuPrincipal();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case '1':
            registrarUsuario();
            break;
        case '2':
            iniciarSesionUsuario("Lector");
            break;
        case '3':
            iniciarSesionUsuario("Administrador");
            break;
        case '0':
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion equivocada. Intente nuevamente...\n";
            break;
        }

        pausar();
    } while (opcion != '0');

    return 0;
}