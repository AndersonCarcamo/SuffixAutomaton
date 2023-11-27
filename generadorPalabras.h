#ifndef PROYECTOAED_GENERADORPALABRAS_H
#define PROYECTOAED_GENERADORPALABRAS_H

#include <vector>
#include <random>
#include <ctime>
#include "circularArrayMod.h"

using namespace std;

string generateRandomWord(int length) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int charCount = characters.size();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, charCount - 1);

    string randomWord;
    for (int i = 0; i < length; ++i) {
        randomWord += characters[dis(gen)];
    }

    return randomWord;
}

CircularArray<string> generateRandomWords(int N, int wordLength) {
    CircularArray<string> randomWords;
    for (int i = 0; i < N; ++i) {
        randomWords.push_back(generateRandomWord(wordLength));
    }
    return randomWords;
}

#endif //PROYECTOAED_GENERADORPALABRAS_H