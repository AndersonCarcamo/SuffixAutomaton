#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "SuffixAutomaton.h"
#include <chrono>
using namespace std;
typedef std::pair<char, int> tr;


float compararTexto(const string& Txc, SuffixAutomaton& ejem) {
    float cont_oraciones_iguales = 0;
    float cont_oraciones_totales = 0;

    string oracion;
    for (char caracter : Txc) {
        if (caracter == '.') {
            cont_oraciones_totales += 1;

            if (!oracion.empty() && ejem.containsSuffix(oracion)) {
                cont_oraciones_iguales += 1;
            }

            oracion.clear();
        } else {
            oracion += caracter;
        }
    }

    return cont_oraciones_iguales / cont_oraciones_totales;
}

int main() {
    float cont = 0;
    string nombreArchivo = "texto_base.txt";

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 1;
    }

    ostringstream contenido;
    string linea;
    while (getline(archivo, linea)) {
        contenido << linea << ' ';
    }

    string contenidoFinal = contenido.str();
    archivo.close();

    SuffixAutomaton ejem(contenidoFinal);

    ifstream archivo2("texto_copia.txt");
    if (!archivo2.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 1;
    }

    ostringstream contenidoCopia;
    string lineaCopia;
    while (getline(archivo2, lineaCopia)) {
        contenidoCopia << lineaCopia << ' ';
    }

    string textoCopia = contenidoCopia.str();
    archivo2.close();


    float resultado = compararTexto(textoCopia, ejem);
    cout << "El total de similitud en el texto es: " << fixed << setprecision(2) << resultado * 100 << "%" << endl;

    return 0;
}
