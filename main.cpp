#include <iostream>
#include "suffixAutomaton.h"
#include "patriciaTrie.h"
#include "generadorPalabras.h"

#include <chrono>
using namespace std::chrono;

int main() {

//    int N = 10;
//    int sizeWord = 6;
//
//    srand(static_cast<unsigned>(time(nullptr)));
//
//    vector<string> randomWords = generateRandomWords(N, sizeWord);
//    auto start = high_resolution_clock::now();
//    for (auto word: randomWords) {
//
//    }

    string text = "banana";

    SuffixAutomaton sa(text);
    sa.insert("carolina");

    PatriciaTrie tp;
    tp.insert(text);

    // Ejemplo de cómo usar el autómata de sufijos para verificar la presencia de un sufijo
    cout << sa.containsSuffix("carolina") << endl; // Salida esperada: 1 (true)
    cout << sa.containsSuffix("banana") << endl;

    return 0;
}
