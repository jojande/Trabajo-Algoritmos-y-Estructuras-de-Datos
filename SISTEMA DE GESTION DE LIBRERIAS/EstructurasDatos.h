#pragma once
#include <iostream>
#include <functional>
#include "opciones.h"
using namespace std;

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(T dato) {
        this->dato = dato;
        this->siguiente = nullptr;
    }
};

template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;

public:
    ListaSimple() : cabeza(nullptr) {}

    ~ListaSimple() {
        while (cabeza) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    void insertarAlFinal(const T& dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (!cabeza) {
            cabeza = nuevo;
        }
        else {
            Nodo<T>* temp = cabeza;
            while (temp->siguiente)
                temp = temp->siguiente;
            temp->siguiente = nuevo;
        }
    }

    bool existeID(const string& idBuscado) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato.getId() == idBuscado) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    bool eliminarPorID(const string& idBuscado) {
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;

        while (actual) {
            if (actual->dato.getId() == idBuscado) {
                if (anterior) {
                    anterior->siguiente = actual->siguiente;
                }
                else {
                    cabeza = actual->siguiente;
                }
                delete actual;
                return true; 
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        return false; 
    }

    bool modificarPorID(const string& idBuscado, const T& nuevosDatos) {
        Nodo<T>* actual = cabeza;

        while (actual) {
            if (actual->dato.getId() == idBuscado) {
                actual->dato = nuevosDatos;  
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    T* buscar(function<bool(const T&)> criterio) {
        Nodo<T>* temp = cabeza;
        while (temp) {
            if (criterio(temp->dato))
                return &temp->dato;
            temp = temp->siguiente;
        }
        return nullptr;
    }

    void mostrarTodo() const {
        Nodo<T>* temp = cabeza;
        while (temp) {
            temp->dato.mostrar();
            cout << "------------------------\n";
            temp = temp->siguiente;
        }
    }

    void ordenar(function<bool(const T&, const T&)> comparador) {
        if (!cabeza || !cabeza->siguiente) return;
        bool cambiado;
        do {
            cambiado = false;
            Nodo<T>* actual = cabeza;
            while (actual->siguiente) {
                if (comparador(actual->siguiente->dato, actual->dato)) {
                    swap(actual->dato, actual->siguiente->dato);
                    cambiado = true;
                }
                actual = actual->siguiente;
            }
        } while (cambiado);
    }

    int tamano() const {
        int cont = 0;
        Nodo<T>* temp = cabeza;
        while (temp) {
            cont++;
            temp = temp->siguiente;
        }
        return cont;
    }

    void recorrer(function<void(const T&)> accion) const {
        Nodo<T>* temp = cabeza;
        while (temp) {
            accion(temp->dato);
            temp = temp->siguiente;
        }
    }

};