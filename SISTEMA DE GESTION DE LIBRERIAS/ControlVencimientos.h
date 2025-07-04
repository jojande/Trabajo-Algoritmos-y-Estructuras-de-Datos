#pragma once
#include "Prestamos.h"
#include "lector.h"

const int MAX_VENCIMIENTOS = 100;

class ControlVencimientos {
private:
    Prestamo* heap[MAX_VENCIMIENTOS];  
    int tamanio;

    int mayor(int i) { return (i - 1) / 2; }
    int izq(int i) { return 2 * i + 1; }
    int der(int i) { return 2 * i + 2; }

    void subir(int i) {
        while (i > 0 && heap[i]->getFechaVencimiento() < heap[mayor(i)]->getFechaVencimiento()) {
            swap(heap[i], heap[mayor(i)]);
            i = mayor(i);
        }
    }

    void bajar(int i) {
        int menor = i;
        int l = izq(i), r = der(i);
        if (l < tamanio && heap[l]->getFechaVencimiento() < heap[menor]->getFechaVencimiento())
            menor = l;
        if (r < tamanio && heap[r]->getFechaVencimiento() < heap[menor]->getFechaVencimiento())
            menor = r;
        if (menor != i) {
            swap(heap[i], heap[menor]);
            bajar(menor);
        }
    }

public:
    ControlVencimientos() {
        tamanio = 0;
    }

    void agregarPrestamo(Prestamo* p) {
        if (tamanio >= MAX_VENCIMIENTOS) {
            cout << "Heap lleno.\n";
            return;
        }
        heap[tamanio] = p;
        subir(tamanio);
        tamanio++;
    }

    void mostrarVencimientos() {
        cout << "\n--- Próximos vencimientos ---\n";
        for (int i = 0; i < tamanio; i++) {
            cout << i + 1 << ") ";
            cout << "ID Préstamo: " << heap[i]->getId()
                << ", Lector: " << heap[i]->getSolicitante()->getNombre()
                << ", Recurso: " << heap[i]->getRecurso()->getTitulo()
                << ", Vence: " << heap[i]->getFechaVencimiento().toString() << endl;
        }
    }

    int getTamanio() const { return tamanio; }

    Prestamo* getPrestamo(int i) const {
        if (i >= 0 && i < tamanio)
            return heap[i];
        return nullptr;
    }


    Prestamo* obtenerMasUrgente() {
        if (tamanio == 0) return nullptr;
        return heap[0];
    }

    void eliminarMasUrgente() {
        if (tamanio == 0) return;
        heap[0] = heap[--tamanio];
        bajar(0);
    }
};
