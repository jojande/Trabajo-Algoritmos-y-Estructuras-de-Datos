#pragma once
#include <iostream>
#include <string> 
using namespace std;

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(const T& dato) : dato(dato), siguiente(nullptr) {}

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

    Nodo<T>* getCabeza() {
        return cabeza;
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

    T* hallarID(const string& idBuscado) {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato.getId() == idBuscado) {
                return &(actual->dato);  // Devuelves la dirección del objeto
            }
            actual = actual->siguiente;
        }
        return nullptr;  // No encontrado
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

    int extraerNumeroID(const string& id) {
        string numero = "";
        for (char c : id) {
            if (isdigit(c)) numero += c;
        }
        return numero.empty() ? 0 : stoi(numero);
    }

    // Obtener un dato en una posición específica
    T getPorIndice(int index) {
        Nodo<T>* actual = cabeza;
        int i = 0;
        while (actual != nullptr) {
            if (i == index)
                return actual->dato;
            actual = actual->siguiente;
            i++;
        }
    }

    // Modificar el dato en una posición específica
    void setPorIndice(int index, const T& nuevoDato) {
        Nodo<T>* actual = cabeza;
        int i = 0;
        while (actual != nullptr) {
            if (i == index) {
                actual->dato = nuevoDato;
                return;
            }
            actual = actual->siguiente;
            i++;
        }
    }

};

template<typename T>
class Cola { 
private:
    Nodo<T>* frente; // primer elemento
    Nodo<T>* final;  // ultimo elemento

public:
    
    Cola() : frente(nullptr), final(nullptr) {}

    ~Cola() {
        while (!estaVacia()) {
            desencolar();
        }
    }

    bool estaVacia() const {
        return frente == nullptr;
    }

    void encolar(const T& valor) { // añadir al final
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (estaVacia()) {
            frente = final = nuevo;
        }
        else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }

    Nodo<T>* hallarID(const string& idBuscado) {
        Nodo<T>* actual = frente;
        while (actual != nullptr) {
            if (actual->dato.getId() == idBuscado) {
                return actual;  // Devuelve el nodo encontrado
            }
            actual = actual->siguiente;
        }
        return nullptr;  // No encontrado
    }


    void desencolar() { //quitar elemento del frente
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

    // obtener el elemento del frente
    Nodo<T>* getFrente() {
        return frente;
    }

    // mostrar todos los elementos
    void mostrar() const {
        Nodo<T>* actual = frente;
        cout << "Cola: ";
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        cout << endl;
    }

	void mostrarTodo() const {
		Nodo<T>* temp = frente;
		while (temp) {
			temp->dato.detallesPrestamo();
			cout << "------------------------\n";
			temp = temp->siguiente;
		}
	}

    int tamanio() {
		int cont = 0;
		Nodo<T>* temp = frente;
		while (temp) {
			cont++;
			temp = temp->siguiente;
		}
		return cont;
    }

};