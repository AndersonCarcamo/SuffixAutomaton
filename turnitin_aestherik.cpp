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

string leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }

    ostringstream contenido;
    string linea;
    while (getline(archivo, linea)) {
        contenido << linea << ' ';
    }

    archivo.close();
    return contenido.str();
}

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
    string nombreArchivoBase = "texto_base.txt";
    string nombreArchivoCopia = "texto_copia.txt";

    string contenidoBase = leerArchivo(nombreArchivoBase);
    string contenidoCopia = leerArchivo(nombreArchivoCopia);

    SuffixAutomaton ejem(contenidoBase);

    float resultado = compararTexto(contenidoCopia, ejem);

    cout << "El total de similitud en el texto es: " << fixed << setprecision(2) << resultado * 100 << "%" << endl;

    return 0;
}
