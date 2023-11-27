    #ifndef SUFFIXAUTOMATON_SUFFIXAUTOMATONNO_H
    #define SUFFIXAUTOMATON_SUFFIXAUTOMATONNO_H

    #include <unordered_map>
    #include "circularArrayMod.h"

    #include <vector> // para calcular las posiciones de todas las palabras parecidas
    #include <string>
    #include <algorithm>
    #include <limits>
    #include "nodeMod.h"

    typedef Node<char, int> tr; // para una transición
    using namespace std;

    struct State {
        int len; // longitud de la cadena
        int link; //posicion del estado al que está linqueado
        int first; // posicion de la primera ocurrencia en ese estado
        bool clone = false; // si el estado es un estado clonado
        CircularArray<tr> transitions; // transiciones salientes hacia otros estados
        CircularArray<int> suffixreferences; // referencias a sufijos
        bool terminal = false; // si un estado es terminal
        int index; // indice del estado

        // añade una transicion  al estado actual con caracter c con indice i
        // Complejidad // O(1)
        void AddTransition(char c, int i)
        {
            transitions.push_back(tr(c, i));
        }

        // Devuelve el indice de un estado al que se realiza una transición con el caracter c
        // si no existe devuelve -1.
        // Complejidad: O(T), donde T es la cantidad de transiciones del estado. El peor caso sería: O(|S|_q - 1) -> O(n)
        int GetTransition(char c)
        {
            for (int i=transitions.Idxfront(); i<=transitions.Idxback(); i = (i+1)%transitions.getCapacity())
            {
                if (transitions[i].key == c)
                {
                    return transitions[i].value;
                }
            }
            return -1;
        }

        // Actualiza la transicion a través del caracter c al nuevo indice
        void UpdateTransition(char c, int i)
        {
            for (int j=transitions.Idxfront(); j<=transitions.Idxback(); j=(j+1)%transitions.getCapacity())
            {
                if (transitions[j].key == c)
                {
                    transitions[j].value = i;
                    return;
                }
            }
        }
    };

    struct SuffixAutomaton {
        bool issuffixreferences = false; // indica si se ha calculado las referencia a sufijos
        CircularArray<State> states; // vector de estados
        State GetState(int i)  // devuelve el estado con indice i
        {
            return states[i];
        }

        // crea un nuevo estado con longitud len y retorna su indice
        int AddState(int len)
        {
            State a;
            a.len = len;
            a.index = states.getBack().index + 1;
            states.push_back(a);
            return a.index;
        }

        // Completa cada estado con un vector de sus hijos en el arbol de enlaces
        void ComputeSuffixReferences()
        {
            for (int i=states.Idxfront(); i<=states.Idxback(); i = (i+1)%states.getCapacity())
            {
                states[states[i].link].suffixreferences.push_back(i);
            }
            issuffixreferences = true;
        }

        // crea el automata para una cadena s
        SuffixAutomaton(string s) {
            // inicializa un estado inicial
            State l;
            l.len = 0;
            l.link = -1;
            l.index = 0;
            states.push_back(l);

            // iteracion para la cadena de entrada
            int last = 0; // se iniciliza con el ultimo estado procesado
            for (auto& c : s) // O(s)
            {
                bool done = false;
                // se crea un nuevo estado con longitud incrementada con respecto a la longitud del estado anterior
                int cur = AddState(states[last].len + 1);
                // se marca la posicion final de la primera ocurrencia de este estado
                states[cur].first = states[last].len;
                // se sigue el enlace desde el ulimo estado linkeado hasta encontrar una transicion con el caracter c
                int linked = last;
                int t = states[linked].GetTransition(c);
                // si no se encuentra una transicion, se sube por la cadena de enlaces hasta encontrar un estado de transicion
                while (t == -1)
                {
                    // se agrega una transicion desde el estado linkeado hasta el estado cur
                    states[linked].AddTransition(c, states[cur].index);
                    // si linked tiene un enlace, se actualiza y se intenta encontrar la transicion de nuevo.
                    if (states[linked].link != -1)
                    {
                        linked = states[linked].link;
                        t = states[linked].GetTransition(c);
                    }
                    // si no tiene enlace , se agrega cur como hijo del estado raiz y se avanza al proximo caracter
                    else
                    {
                        states[cur].link = 0;
                        last = cur;
                        done = true;
                        break;
                    }
                }
                if (done) continue;

                // ssi el estado q tiene una longitud igual a la longitud de p +1, entonces cur
                // es un hijo de q y se avanza al nuevo caracter
                int p = linked;
                int q = t;
                if (states[q].len == states[p].len + 1)
                {
                    // Cur is a child of q in the link tree, process next character
                    states[cur].link = states[q].index;
                    last = cur;
                    continue;
                }
                // si no, se crea un estado clone, que sera el padre de q y cur en la cadena de links
                int clone = AddState(states[p].len + 1);
                states[clone].link = states[q].link;
                states[clone].transitions = states[q].transitions;
                states[clone].first = states[q].first;
                states[clone].clone = true;
                states[cur].link = states[clone].index;
                states[q].link = states[clone].index;
                // Se crea un nuevo estado clone con la longitud apropiada.
                // Se establece el enlace de clone y se copian las transiciones y la posición final desde q.
                // Se marca clone como un estado clonado.
                // Se actualizan los enlaces desde cur y q hacia clone.

                // se actuliza las transiciones desde linked hacia clone para reflejar el nuevo estado creado.
                // Se sigue subiendo por los enlaces y se actualizan las transiciones hasta que se alcance el final o se encuentre una transición diferente.
                linked = p;
                while (t == q)
                {
                    states[linked].UpdateTransition(c, clone);
                    linked = states[linked].link;
                    if (linked != -1)
                    {
                        t = states[linked].GetTransition(c);
                    }
                    else
                    {
                        break;
                    }
                }
                last = cur;
            }

            // se marca el ultimo estado como final (trivial)
            // se sube por los links y se marca como terminales dichos estados hasta llegar a la raiz
            states[last].terminal = true;
            int link = states[last].link;
            while (link != -1)
            {
                int linked = link;
                states[linked].terminal = true;
                link = states[linked].link;
            }
        }

        // O(s) Verifica si la cadena fuente contiene la subcadena 's'
        bool contains(string s)
        {
            int i = 0;
            for (auto& c : s)
            {
                i = states[i].GetTransition(c);
                if (i == -1)
                {
                    return false;
                }
            }
            return true;
        }

        // devuelve la posicion de la primera ocurrencia de la cadena 's' o -1 si no ocurre
        int first(string s)
        {
            int next = 0;
            for (int i = 0; i < s.size(); i++)
            {
                next = states[next].GetTransition(s[i]);
                if (next == -1) return -1;
            }
            return states[next].first - s.size() + 1;
        }

        //devuelve un vector de posiciones donde ocurre la cadena s
        vector<int> positions(string s)
        {
            vector<int> p;
            int sz = s.size();
            if (!issuffixreferences) ComputeSuffixReferences();
            int next = 0;
            for (int i = 0; i < sz; i++)
            {
                next = states[next].GetTransition(s[i]);
                if (next == -1) return {};
            }
            // Traverse link tree down from first occurrence to find all others
            CircularArray<int> stack = {next};
            while (stack.size() > 0)
            {
                next = stack.getBack();
                stack.pop_back();
                if (!states[next].clone) p.push_back(states[next].first - sz + 1);
                for (int i=states[next].suffixreferences.Idxfront(); i<=states[next].suffixreferences.Idxback(); i = (i+1)%states[next].suffixreferences.getCapacity())
                {
                    stack.push_back(i);
                }
            }
            std::sort(p.begin(), p.end());
            return p;
        }
    };

    #endif //SUFFIXAUTOMATON_SUFFIXAUTOMATONNO_H