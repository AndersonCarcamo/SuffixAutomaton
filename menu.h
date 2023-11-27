#ifndef SUFFIXAUTOMATON_MENU_H
#define SUFFIXAUTOMATON_MENU_H

#include <iostream>
#include "suffixAutomaton.h"
#include "patriciaTrie.h"
#include "generadorPalabras.h"
#include "compararTexto.h"

#include <unordered_set>
#include <chrono>
using namespace std::chrono;

class Menu{
private:

public:
    Menu() = default;

    void start();
    void salida(int code){
        cerr << "Hasta Luego. Code :" << code;
    }
    void pruebaRendimiento();
    void aplicativo();
    void conString();
    void conNombreArchivo();
};

void Menu::start() {
    int a;
    cout << "SUFFIX AUTOMATON" << endl;
    cout << "Opciones:\n 1. Prueba de rendimiento para un string con N palabras\n2. Inserseccion de text\n";
    cin >> a;
    if (a == 1){
        pruebaRendimiento();
    }
    else if(a == 2){
        aplicativo();
    }
    else{
        start();
    }
}

void Menu::pruebaRendimiento() {
    int len, n;
    cout << "Prueba para N palabras:\n";
    cout << "Inserte longitud de los strings:\n";
    cin >> len;
    cout << "N: \n";
    cin >> n;
    string word =  "";
    for (int i = 0; i < n; ++i) {
        word += generateRandomWord(len) + " ";
    }
    auto start = high_resolution_clock::now();
    SuffixAutomaton sa = SuffixAutomaton(word);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tiempo en ms: " << duration.count() << endl;

//    start = high_resolution_clock::now();
//    SuffixAutomatonOp saOp = SuffixAutomatonOp(word);
//    stop = high_resolution_clock::now();
//    duration = duration_cast<microseconds>(stop - start);
//    cout << "Tiempo en ms sin Optimizar: " << duration.count() << endl;
}

void Menu::aplicativo() {
    short int a;
    cout << "1. Prueba con entrada string\n 2. prueba con archivo\n";
    cin >> a;
    if (a == 1)
        conString();
    else if(a == 2)
        conNombreArchivo();
}

void Menu::conString(){
    string s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese el string:" << endl;
    getline(cin, s);  // Lee toda la línea, incluyendo espacios en blanco
    cout << "Esperando..." << endl;
    auto start = high_resolution_clock::now();
    SuffixAutomaton sa = SuffixAutomaton(s);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Tiempo de ejecucion: " << duration.count() << " microseconds\n";
    cout << "String: \"" << s << "\" is of size " << s.size() << " and its automaton has " << sa.states.size() << " states" << endl;
    while (true){
        char a;
        cout << "Accion a realizar:\n[e]xiste en el automata\n[p]rimera posicion del substring\n[t]odas las posiciones del substring\n[s]ailda" << endl;
        unordered_set<char> input{'e', 'p', 's', 't'};
        cin.get(a);
        while (input.count(a) < 1)
        {
            cin.get(a);
        }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (a == 't')
        {
            cout << "Enter a substring to see its positions:" << endl;

            string p;
            cin.get(a);
            while (a != '\n')
            {
                p.push_back(a);
                cin.get(a);
            }
            vector<int> positions = sa.positions(p);
            if (positions.size() != 0)
            {
                cout << "YES, \"" << s << "\" contains the substring " << "\"" << p << "\" at positions\n[ ";
                for (auto& i : positions)
                {
                    cout << i << " ";
                }
                cout << "]" << endl;
                for (auto& position : positions)
                {
                    int id = min(10, position);
                    if (position > 10) cout << "...";
                    for (int pf = position-id; pf < position; pf++)
                    {
                        cout <<s[pf];
                    }
                    cout << "(" << p << ")";
                    for (id = p.size()+position; (id < s.size() && id < p.size()+position+10); id++)
                    {
                        cout << s[id];
                    }
                    if (id < s.size()) cout << "...";
                    cout << endl;
                }
            }
            else
            {
                cout << "NO, \"" << s << "\" does not contain the substring " << "\"" << p << "\"" << endl;
            }
        }
        else if (a == 'p')
        {
            cout << "Enter a substring to see its first position:" << endl;

            string p;
            cin.get(a);
            while (a != '\n')
            {
                p.push_back(a);
                cin.get(a);
            }
            int position = sa.first(p);
            if (position != -1)
            {
                cout << "YES, \"" << s << "\" contains the substring " << "\"" << p << "\" at position " << position << ":" << endl;
                int id = min(10, position);
                if (position > 10) cout << "...";
                for (int pf = position-id; pf < position; pf++)
                {
                    cout <<s[pf];
                }
                cout << "(" << p << ")";
                for (id = p.size()+position; (id < s.size() && id < p.size()+position+10); id++)
                {
                    cout << s[id];
                }
                if (id < s.size()) cout << "...";
                cout << endl;

            } else
            {
                cout << "NO, \"" << s << "\" does not contain the substring " << "\"" << p << "\"" << endl;
            }
        }
        else if (a == 'e')
        {
            cout << "Enter a substring to see if it occurs:" << endl;

            string p;
            cin.get(a);
            while (a != '\n')
            {
                p.push_back(a);
                cin.get(a);
            }

            start = high_resolution_clock::now();
            bool occurs = sa.contains(p);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Tiempo de ejecucion de busqueda: " << duration.count() << " microseconds\n";
            if (occurs)
            {
                cout << "YES, \"" << s << "\" contains the substring " << "\"" << p << "\"" << endl;
            } else
            {
                cout << "No, \"" << s << "\" does not contain the substring " << "\"" << p << "\"" << endl;
            }
        }
        else if (a == 's')
        {
            cout << "Quitting" << endl;
            return;
        }
    }
}

void Menu::conNombreArchivo() {
    float cont = 0;
    string nombreArchivo = "texto_base.txt";

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
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
        return;
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

}


#endif //SUFFIXAUTOMATON_MENU_H