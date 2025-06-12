#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "RecursoBibliografico.h"
using namespace std;

class Usuario {
private:
    string id;
    string nombre;
    string contrasenia;

public:
    Usuario(string nombre, string contrasenia) {
        this->nombre = nombre;
        this->contrasenia = contrasenia;
        this->id = "";
    }

    ~Usuario() {}

    void setNombre(string n) { nombre = n; }
    void setContrasenia(string c) { contrasenia = c; }
    string getNombre() { return nombre; }
    string getContrasenia() { return contrasenia; }
    string getId() { return id; }

    void AgregarUsuario(string tipo) {
        ifstream archivoLectura("usuarios.txt");
        int contadorLectores = 0, contadorAdmins = 0;
        string linea;

        while (getline(archivoLectura, linea)) {
            if (linea.find("Lector") == 0) contadorLectores++;
            else if (linea.find("Administrador") == 0) contadorAdmins++;
        }
        archivoLectura.close();

        if (tipo == "Administrador") {
            id = "IDAD" + to_string(contadorAdmins + 1);
            ofstream archivo("usuarios.txt", ios::app);
            if (archivo.is_open()) {
                archivo << "Administrador|" << id << "|" << nombre << "|" << contrasenia << endl;
                archivo.close();
                cout << "Administrador registrado correctamente con ID " << id << endl;
            }
        }
        else if (tipo == "Lector") {
            id = "IDUS" + to_string(contadorLectores + 1);
            ofstream archivo("usuarios.txt", ios::app);
            if (archivo.is_open()) {
                archivo << "Lector|" << id << "|" << nombre << "|" << contrasenia << endl;
                archivo.close();
                cout << "Lector registrado correctamente con ID " << id << endl;
            }
        }
        else {
            cout << "Error tipo de usuario" << endl;
        }


    }

    bool ComprobarUsuario(string tipo) {
        ifstream archivo("usuarios.txt");
        string linea;

        while (getline(archivo, linea)) {

            size_t pos1 = linea.find('|');
            size_t pos2 = linea.find('|', pos1 + 1);
            size_t pos3 = linea.find('|', pos2 + 1);

            string tipoArchivo = linea.substr(0, pos1);
            string nombreArchivo = linea.substr(pos2 + 1, pos3 - pos2 - 1);

            if (tipoArchivo == tipo && nombreArchivo == nombre) {
                archivo.close();
                return true;
            }
        }

        archivo.close();
        return false;
    }

    bool IniciarSesion(string tipo) {
        ifstream archivo("usuarios.txt");
        string linea;

        while (getline(archivo, linea)) {

            size_t pos1 = linea.find('|');
            size_t pos2 = linea.find('|', pos1 + 1);
            size_t pos3 = linea.find('|', pos2 + 1);

            string tipoArchivo = linea.substr(0, pos1);
            string nombreArchivo = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string contraseniaArchivo = linea.substr(pos3 + 1);

            if (tipoArchivo == tipo && nombreArchivo == nombre && contraseniaArchivo == contrasenia) {
                archivo.close();
                return true;
            }
        }

        archivo.close();
        return false;
    }

};
