#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Prestamos.h"
using namespace std;

class Multa {
private:
    string idMulta;
    double monto;
    Prestamo* prestamo;

public:
    
    Multa(const string idMulta, Prestamo* prestamo) {
        this->idMulta = idMulta;
        this->monto = generarMontoAleatorio();
        prestamo = prestamo;
    }

    string getIdMulta() const { return idMulta; }
    double getMonto() const { return monto; }
    Prestamo* getPrestamo() const { return prestamo; }

    void setMonto(double nuevoMonto) {
        monto = nuevoMonto;
    }

    bool operator<(const Multa& otra) const {
        return this->getMonto() < otra.getMonto();
    }


    void mostrarMulta() const {
        cout << "=== Multa ===\n";
        cout << "ID: " << idMulta << "\n";
        cout << "Monto: S/. " << monto << "\n";
        if (prestamo) {
            cout << "--- Préstamo asociado ---\n";
            prestamo->detallesPrestamo();
        }
    }


    double generarMontoAleatorio() {
        srand(static_cast<unsigned>(time(nullptr)));
        return 5.0 + static_cast<double>(rand() % 46); // 5 a 50 soles
    }
};
