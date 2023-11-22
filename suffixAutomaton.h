#ifndef PROYECTOAED_SUFFIXAUTOMATON_H
#define PROYECTOAED_SUFFIXAUTOMATON_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class SuffixAutomaton {
private:
    struct State {
        unordered_map<char, int> transitions;
        int link = -1;
        int length = 0;
        bool isTerminal = false;
    };

    vector<State> states;
    int lastState;

public:
    SuffixAutomaton(){
        lastState = -1;
    }
    SuffixAutomaton(const string& str) {
        states.emplace_back();
        lastState = 0;
        states[0].link = -1;
        states[0].length = 0;

        for (char c : str)
            extend(c);
    }

    void insert(string str){
        for (char c : str)
            extend(c);
    }

    void extend(char c) {
        int newStateIndex = states.size();
        states.emplace_back();
        int currentState = lastState;

        states[newStateIndex].length = states[currentState].length + 1;
        states[newStateIndex].isTerminal = true;


        // vuelve hasta que el current state no sea igual a -1 y que el stado no tenga una transicion hacia el estado con la lectra c
        while (currentState != -1 && !states[currentState].transitions.count(c)) {
            states[currentState].transitions[c] = newStateIndex;
            currentState = states[currentState].link;
        }

        if (currentState == -1) {
            states[newStateIndex].link = 0;
        } else {
            int nextState = states[currentState].transitions[c];
            if (states[currentState].length + 1 == states[nextState].length) {
                states[newStateIndex].link = nextState;
            } else {
                int cloneStateIndex = states.size();
                states.emplace_back(states[nextState]);
                states[cloneStateIndex].length = states[currentState].length + 1;

                while (currentState != -1 && states[currentState].transitions[c] == nextState) {
                    states[currentState].transitions[c] = cloneStateIndex;
                    currentState = states[currentState].link;
                }

                states[nextState].link = cloneStateIndex;
                states[newStateIndex].link = cloneStateIndex;
            }
        }

        lastState = newStateIndex;
    }

    // Función para verificar si un sufijo está presente en el autómata de sufijos
    bool containsSuffix(const string& suffix) {
        int currentState = 0;
        for (char c : suffix) {
            if (!states[currentState].transitions.count(c)) {
                return false;
            }
            currentState = states[currentState].transitions[c];
        }
        return states[currentState].isTerminal;
    }
};

#endif //PROYECTOAED_SUFFIXAUTOMATON_H