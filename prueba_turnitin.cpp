#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "SuffixAutomaton.h"
typedef std::pair<char, int> tr;
using namespace std;
#include <chrono>
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

// A single state in our DFA, which represents an equivalence class.
int main(){
    float cont=0;
    string nombreArchivo = "texto_base.txt";

    // Objeto ifstream para abrir el archivo
    ifstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 1; // Terminar el programa con un código de error
    }

    // Leer y concatenar el contenido del archivo en un solo string
    ostringstream contenido;
    string linea;
    while (getline(archivo, linea)) {
        contenido << linea << ' '; // Agregar la línea y un espacio
    }

    // Obtener el string resultante
    string contenidoFinal = contenido.str();

    // Cerrar el archivo después de leer
    archivo.close();


    // Mostrar el contenido resultante
    SuffixAutomaton ejem(contenidoFinal);
    ifstream archivo2("texto_copia.txt");
    if (!archivo2.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 1; // Terminar el programa con un código de error
    }
    vector<string> palabras;
    string palabra;
    while (archivo2 >> palabra) {
        palabra = limpiarPalabra(palabra);

        if (!palabra.empty()) 
            palabras.push_back(palabra);
    }
    archivo2.close();
    for (const auto& p : palabras) {
        if(ejem.containsSuffix(p))
            cont+=1;
    }
    float total=(cont/palabras.size())*100;
    cout<<"El total de similitud en el texto es: "<<fixed << setprecision(2)<<total<<"%"<<endl;

    return 0;
    
}