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
using namespace std::chrono;

string limpiarPalabra(const string& palabra) {
    string palabraLimpia;
    for (char c : palabra) {
        if (c == ',' || c == '.') {
            continue; // Omitir puntos y comas
        }
        palabraLimpia += c;
    }
    return palabraLimpia;
}

string leerContenidoArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return "";
    }

    ostringstream contenido;
    string linea;
    while (getline(archivo, linea)) {
        contenido << linea << ' '; // Agregar la línea y un espacio
    }

    archivo.close();
    return contenido.str();
}

vector<string> obtenerPalabrasDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return {};
    }

    vector<string> palabras;
    string palabra;
    while (archivo >> palabra) {
        palabra = limpiarPalabra(palabra);
        if (!palabra.empty()) {
            palabras.push_back(palabra);
        }
    }

    archivo.close();
    return palabras;
}

float calcularSimilitud(SuffixAutomaton& automaton, const vector<string>& palabras) {
    float cont = 0;
    for (const auto& p : palabras) {
        if (automaton.containsSuffix(p)) {
            cont += 1;
        }
    }
    return (cont / palabras.size()) * 100;
}


int main() {
    float cont = 0;
    string nombreArchivoBase = "texto_base.txt";

    string contenidoBase = leerContenidoArchivo(nombreArchivoBase);
    SuffixAutomaton ejem(contenidoBase);

    string nombreArchivoCopia = "texto_copia.txt";
    vector<string> palabrasCopia = obtenerPalabrasDesdeArchivo(nombreArchivoCopia);

    for (const auto& p : palabrasCopia) {
        if (ejem.containsSuffix(p)) {
            cont += 1;
        }
    }

    float total = (cont / palabrasCopia.size()) * 100;
    cout << "El total de similitud en el texto es: " << fixed << setprecision(2) << total << "%" << endl;

    return 0;
}
