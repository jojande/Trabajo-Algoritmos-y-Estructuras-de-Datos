#pragma once
#include <iostream>
#include "opciones.h"

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

    bool buscarporID(const string& idBuscado) {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato.getId() == idBuscado) {
                return &actual->dato;
            }
            actual = actual->siguiente;
        }
        return nullptr;
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

    void mostrarTodo() const {
        Nodo<T>* temp = cabeza;
        while (temp) {
            temp->dato.mostrar();
            cout << "------------------------\n";
            temp = temp->siguiente;
        }
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

};

template<typename T>
class Cola { // Cola simple
private:
    Nodo<T>* frente; // Apunta al primer elemento
    Nodo<T>* final;  // Apunta al último elemento

public:
    // Constructor
    Cola() : frente(nullptr), final(nullptr) {}

    // Destructor
    ~Cola() {
        while (!estaVacia()) {
            desencolar();
        }
    }

    // Verifica si la cola está vacía
    bool estaVacia() const {
        return frente == nullptr;
    }

    // Encolar (añadir al final)
    void encolar(const T& valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (estaVacia()) {
            frente = final = nuevo;
        }
        else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }

    // Desencolar (quitar del frente)
    void desencolar() {
        if (estaVacia()) {
            cout << "La cola está vacía. No se puede desencolar." << endl;
            return;
        }
        Nodo<T>* temp = frente;
        frente = frente->siguiente;
        delete temp;
        if (frente == nullptr) {
            final = nullptr;
        }
    }

    // Obtener el elemento del frente
    T verFrente() const {
        if (estaVacia()) {
            throw runtime_error("Cola vacía: no se puede acceder al frente.");
        }
        return frente->dato;
    }

    // Mostrar todos los elementos
    void mostrar() const {
        Nodo<T>* actual = frente;
        cout << "Cola: ";
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        cout << endl;
    }
};