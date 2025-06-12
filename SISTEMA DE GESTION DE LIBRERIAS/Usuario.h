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


};
