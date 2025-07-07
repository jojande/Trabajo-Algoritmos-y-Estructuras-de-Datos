#include <iostream>
#include <conio.h>
#include "Usuario.h"
#include "utils.h"

using namespace std;



int main() {
    system("chcp 65001");

    ListaSimple<Usuario*> listaLectores;
    ListaSimple<RecursoBibliografico*> listaRecursos;
    ListaSimple<Usuario*> listaAdmi;
    ListaSimple<Usuario*> listaBibliotecario;

    ListaSimple<libro> listaLibros;
    ListaSimple<revista> listaRevistas;
    ListaSimple<tesis> listaTesis;

    Cola<Prestamo> colaPrestamos;
    HashTable<Prestamo> hashPrestamos;
    ArbolBinario<Multa> arbolMultas;

    cargarLibros("archivos_txt/libros.txt");
    cargarRevistas("archivos_txt/revistas.txt");
    cargarTesis("archivos_txt/tesis.txt");
	cargarLector("archivos_txt/lectores.txt");
	cargarBibliotecario("archivos_txt/bibliotecarios.txt");
    cargarAdministrador("archivos_txt/administradores.txt");
	cargarPrestamo("archivos_txt/prestamos.txt");
    cargarTablaPrestamosConfirmados("archivos_txt/prestamostablahash.txt", tablaOrdenada);
    cargarmultas("archivos_txt/multas.txt");
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
        case '5': {
            generarDatasetLibros(30, listaLibros);
            generarDatasetRevistas(20, listaRevistas);
            generarDatasetTesis(15, listaTesis);
            generarDatasetUsuarios("administrador", 10, listaAdmi);
            generarDatasetUsuarios("bibliotecario", 10, listaBibliotecario);
            

            listaRecursos.limpiar();

            Nodo<libro>* actL = listaLibros.getCabeza();
            while (actL) {
                listaRecursos.insertarAlFinal(new libro(actL->dato));
                actL = actL->siguiente;
            }

            Nodo<revista>* actR = listaRevistas.getCabeza();
            while (actR) {
                listaRecursos.insertarAlFinal(new revista(actR->dato));
                actR = actR->siguiente;
            }

            Nodo<tesis>* actT = listaTesis.getCabeza();
            while (actT) {
                listaRecursos.insertarAlFinal(new tesis(actT->dato));
                actT = actT->siguiente;
            }

            int cantidadLectores = 50;

            generarDatasetUsuariosConPrestamosYMultas(
                cantidadLectores,
                listaLectores,
                listaRecursos,
                colaPrestamos,
                hashPrestamos,
                arbolMultas
            );

            break;
        }
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