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

    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;

            delete temp->dato; 
            delete temp;      
        }
        cabeza = nullptr;
    }
    Nodo<T>* getCabeza() {
        return cabeza;
    }

    Nodo<T>* getCabezas() const {
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

    Nodo<T>* getFrente() const {
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
            Nodo<T>* actual = tabla[i].getCabeza();
            if (actual) {
                cout << "[" << i << "]: ";
                while (actual != nullptr) {
                    cout << "("
                        << actual->dato.getId() << ", "
                        << actual->dato.getSolicitante()->getNombre() << ", "
                        << actual->dato.getFechaVencimiento().toString()
                        << ") ";
                    actual = actual->siguiente;
                }
                cout << "\n";
            }
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



    void insertarRecursivo(NodoArbol<T>*& nodo, const T& nuevo) {
        if (nodo == nullptr) {
            nodo = new NodoArbol<T>(nuevo);
        }
        else if (nuevo < nodo->dato) {
            insertarRecursivo(nodo->izq, nuevo);
        }
        else {
            insertarRecursivo(nodo->der, nuevo);
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
        insertarRecursivo(raiz, nuevo);
    }

    void mostrarInOrden() {
        cout << "Elementos ordenados:\n";
        inOrden(raiz);
    }
};

template <typename T>
class Grafo {
private:
    Nodo<T>** listaAdyacencia; // Array de punteros a nodos (lista de adyacencia)
    int capacidad;             // Capacidad máxima del grafo
    int numNodos;              // Número actual de nodos
    bool dirigido;             // Tipo de grafo

    // Método privado para encontrar el índice de un nodo
    int encontrarIndice(const T& dato) {
        for (int i = 0; i < numNodos; ++i) {
            if (listaAdyacencia[i] != nullptr && listaAdyacencia[i]->dato == dato) {
                return i;
            }
        }
        return -1; // No encontrado
    }

public:
    // Constructor
    Grafo(int capacidad = 100, bool dirigido = false)
        : capacidad(capacidad), numNodos(0), dirigido(dirigido) {
        listaAdyacencia = new Nodo<T>*[capacidad];
        for (int i = 0; i < capacidad; ++i) {
            listaAdyacencia[i] = nullptr;
        }
    }

    // Destructor
    ~Grafo() {
        for (int i = 0; i < numNodos; ++i) {
            Nodo<T>* actual = listaAdyacencia[i];
            while (actual != nullptr) {
                Nodo<T>* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
        delete[] listaAdyacencia;
    }

    Nodo<T>* getNodo(int index) const {
        if (index >= 0 && index < numNodos) {
            return listaAdyacencia[index];
        }
        return nullptr;
    }

    // Agregar un nodo al grafo
    bool agregarNodo(const T& dato) {
        if (numNodos >= capacidad || encontrarIndice(dato) != -1) {
            return false;
        }
        listaAdyacencia[numNodos] = new Nodo<T>(dato);
        numNodos++;
        return true;
    }

    // Agregar una arista entre dos nodos
    bool agregarArista(const T& origen, const T& destino) {
        int idxOrigen = encontrarIndice(origen);
        int idxDestino = encontrarIndice(destino);

        if (idxOrigen == -1 || idxDestino == -1) {
            return false;
        }

        // Agregar a la lista de adyacencia del origen
        Nodo<T>* nuevo = new Nodo<T>(destino);
        nuevo->siguiente = listaAdyacencia[idxOrigen]->siguiente;
        listaAdyacencia[idxOrigen]->siguiente = nuevo;

        // Si no es dirigido, agregar arista inversa
        if (!dirigido) {
            Nodo<T>* nuevoInverso = new Nodo<T>(origen);
            nuevoInverso->siguiente = listaAdyacencia[idxDestino]->siguiente;
            listaAdyacencia[idxDestino]->siguiente = nuevoInverso;
        }

        return true;
    }

    // Mostrar el grafo
    void imprimir() const {
        cout << "Lista de adyacencia del grafo:" << endl;
        for (int i = 0; i < numNodos; ++i) {
            cout << listaAdyacencia[i]->dato << " -> ";
            Nodo<T>* actual = listaAdyacencia[i]->siguiente;
            while (actual != nullptr) {
                cout << actual->dato << " -> ";
                actual = actual->siguiente;
            }
            cout << "null" << endl;
        }
    }

    // Obtener el grado de un nodo
    int obtenerGrado(const T& dato) {
        int idx = encontrarIndice(dato);
        if (idx == -1) return -1;

        int grado = 0;
        Nodo<T>* actual = listaAdyacencia[idx]->siguiente;
        while (actual != nullptr) {
            grado++;
            actual = actual->siguiente;
        }
        return grado;
    }
};