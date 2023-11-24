#ifndef PROYECTOAED_GENERADORPALABRAS_H
#define PROYECTOAED_GENERADORPALABRAS_H

#include <vector>
#include <random>
#include <ctime>

using namespace std;

// Function to generate a random word of given length
string generateRandomWord(int length) {
    const string characters = "abcdefghijklmnopqrstuvwxyz";
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

// Function to generate a vector of N random words of given length
vector<string> generateRandomWords(int N, int wordLength) {
    vector<string> randomWords;
    for (int i = 0; i < N; ++i) {
        randomWords.push_back(generateRandomWord(wordLength));
    }
    return randomWords;
}

#endif //PROYECTOAED_GENERADORPALABRAS_H