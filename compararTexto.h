#ifndef SUFFIXAUTOMATON_COMPARARTEXTO_H
#define SUFFIXAUTOMATON_COMPARARTEXTO_H


#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

#include "suffixAutomatonNO.h"

float compararTexto(const string& Txc, SuffixAutomaton& ejem) {
    float cont_oraciones_iguales = 0;
    float cont_oraciones_totales = 0;

    string oracion;
    for (char caracter : Txc) {
        if (caracter == '.') {
            cont_oraciones_totales += 1;

            if (!oracion.empty() && ejem.contains(oracion)) {
                cont_oraciones_iguales += 1;
            }

            oracion.clear();
        } else {
            oracion += caracter;
        }
    }

    return cont_oraciones_iguales / cont_oraciones_totales;
}

#endif //SUFFIXAUTOMATON_COMPARARTEXTO_H
