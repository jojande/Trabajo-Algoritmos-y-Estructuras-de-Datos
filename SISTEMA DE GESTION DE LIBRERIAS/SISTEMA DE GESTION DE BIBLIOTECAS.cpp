#include <iostream>
#include <conio.h>
#include "Usuario.h"
#include "utils.h"
using namespace std;


int main() {
    cargarLibros("archivos_txt/libros.txt");
    cargarRevistas("archivos_txt/revistas.txt");
    cargarTesis("archivos_txt/tesis.txt");
	cargarLector("archivos_txt/lectores.txt");
	cargarBibliotecario("archivos_txt/bibliotecarios.txt");
	cargarAdministrador("archivos_txt/admins.txt");
	cargarPrestamo("archivos_txt/prestamos.txt");
    char opcion;
    do {
        system("cls");
        mostrarMenuPrincipal();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case '1':{
            cout << "Seleccione el tipo de usuario a registrar:\n";
            cout << "1. Lector\n";
            cout << "2. Bibliotecario\n";
            cout << "3. Administrador\n";
            string tipoUsuario;
			cin >> tipoUsuario;
			cin.ignore();
			if (tipoUsuario == "1") {
				registrarLector();
			}
			else if (tipoUsuario == "2") {
				registrarBibliotecario();
			}
			else if (tipoUsuario == "3") {
				registrarAdministrador();
			}
			else {
				cout << "Tipo de usuario no válido.\n";
			}
            break;
        }	
        case '2':
            iniciarSesionLector();
			

            break;
        case '3':
            iniciarSesionAdministrador();
            break;
        case '4':
            iniciarSesionBibliotecario();
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