#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Usuario {
protected:
    string id;
    string nombre;
    string contrasenia;

public:
    Usuario(const string id, const string nombre, const string contrasenia) {
        this->nombre = nombre;
        this->contrasenia = contrasenia;
        this->id = id;
    }

    ~Usuario() {}

    void setNombre(string n) { nombre = n; }
    void setContrasenia(string c) { contrasenia = c; }
    string getNombre() const { return nombre; }
    string getContrasenia() const { return contrasenia; }
    string getId() const { return id; }

    void mostrar(){
		cout << "ID: " << id << endl;
		cout << "Nombre: " << nombre << endl;
		cout << "Contrasenia: " << contrasenia << endl;
    }

};
