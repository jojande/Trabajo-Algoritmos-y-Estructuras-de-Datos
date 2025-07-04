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

template <typename T>
class HashTable {
private:
    static const int tamanio = 50;  
    ListaSimple<T> tabla[tamanio];

    int funcionHash(const string& clave) {
        int suma = 0;
        for (char c : clave) {
            suma += c;
        }
        return suma % tamanio;
    }

public:
    void insertar(const T& elemento) {
        int index = funcionHash(elemento.getId());
        tabla[index].insertarAlFinal(elemento);
    }

    T* buscar(const string& id) {
        int index = funcionHash(id);
        return tabla[index].hallarID(id);
    }

    bool eliminar(const string& id) {
        int index = funcionHash(id);
        return tabla[index].eliminarPorID(id);
    }
    ListaSimple<T>* getTabla() {
        return tabla;  
    }

    void insertarEnCubeta(const T& elemento, int cubetaIndex) {
        if (cubetaIndex >= 0 && cubetaIndex < tamanio) {
            tabla[cubetaIndex].insertarAlFinal(elemento);
        }
    }

    Nodo<T>* getCubeta(int index) {
        if (index >= 0 && index < tamanio)
            return tabla[index].getCabeza();
        return nullptr;
    }

    void mostrar() {
        for (int i = 0; i < tamanio; ++i) {
            cout << "[" << i << "]: ";
            Nodo<T>* actual = tabla[i].getCabeza();
            while (actual != nullptr) {
                cout << "(" << actual->dato.getId() << ", " << actual->dato.getSolicitante()->getNombre() << ") ";
                actual = actual->siguiente;
            }
            cout << "\n";
        }
    }
};

template <typename T>
class NodoArbol {
public:
    T dato;
    NodoArbol* izq;
    NodoArbol* der;

    NodoArbol(T _dato) : dato(_dato), izq(nullptr), der(nullptr) {}
};

template <typename T>
class ArbolBinario {
private:
    NodoArbol<T>* raiz;

public:
    ArbolBinario() : raiz(nullptr) {}
    ~ArbolBinario() { liberarMemoria(raiz); }



    void insertar(NodoArbol<T>*& nodo, const T& nuevo) {
        if (nodo == nullptr) {
            nodo = new NodoArbol<T>(nuevo);
        }
        else if (nuevo.getFechaVencimiento() < nodo->dato.getFechaVencimiento()) {
            insertar(nodo->izq, nuevo);
        }
        else {
            insertar(nodo->der, nuevo);
        }
    }
    
    NodoArbol<T>* getRaiz() const {
        return raiz;
    }

    void inOrden(NodoArbol<T>* nodo) {
        if (nodo != nullptr) {
            inOrden(nodo->izq);
            cout << nodo->dato.getResumen() << endl;
            inOrden(nodo->der);
        }
    }

    void liberarMemoria(NodoArbol<T>* nodo) {
        if (nodo) {
            liberarMemoria(nodo->izq);
            liberarMemoria(nodo->der);
            delete nodo;
        }
    }


    void insertar(const T& nuevo) {
        insertar(raiz, nuevo);
    }

    void mostrarInOrden() {
        cout << "Préstamos ordenados por fecha de vencimiento:\n";
        inOrden(raiz);
    }
};