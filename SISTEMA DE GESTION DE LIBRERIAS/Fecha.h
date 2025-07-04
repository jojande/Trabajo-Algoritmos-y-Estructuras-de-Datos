#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdio>

using namespace std;

class Fecha {
private:
    int dia, mes, anio;

public:
    Fecha() : dia(0), mes(0), anio(0) {}

    Fecha(const string& fechaStr) {
        sscanf_s(fechaStr.c_str(), "%d/%d/%d", &dia, &mes, &anio);
    }

    void sumarDias(int n) {
        struct tm t = {};
        t.tm_mday = dia + n;
        t.tm_mon = mes - 1;
        t.tm_year = anio - 1900;

        mktime(&t);  

        dia = t.tm_mday;
        mes = t.tm_mon + 1;
        anio = t.tm_year + 1900;
    }

    string toString() const {
        stringstream ss;
        ss << setw(2) << setfill('0') << dia << "/"
            << setw(2) << setfill('0') << mes << "/"
            << setw(4) << setfill('0') << anio;
        return ss.str();
    }

    bool operator<(const Fecha& otra) const {
        if (anio != otra.anio) return anio < otra.anio;
        if (mes != otra.mes) return mes < otra.mes;
        return dia < otra.dia;
    }

    bool operator==(const Fecha& otra) const {
        return dia == otra.dia && mes == otra.mes && anio == otra.anio;
    }
};
