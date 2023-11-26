#include <iostream>
#include "suffixAutomaton.h"
#include "patriciaTrie.h"
#include "generadorPalabras.h"

#include <unordered_set>
#include <chrono>
using namespace std::chrono;

int main()
{
    string s;
    char a;
    cout << "Enter the string to construct a su,,,ffix automaton:" << endl;
    cin.get(a);
    while (a != '\n')
    {
        s.push_back(a);
        cin.get(a);
    }
    cout << "Constructing automaton..." << endl;

    auto start = high_resolution_clock::now();
    SuffixAutomaton sa = SuffixAutomaton(s);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Tiempo de ejecucion: " << duration.count() << " microseconds\n";

    cout << "String: \"" << s << "\" is of size " << s.size() << " and its automaton has " << sa.states.size() << " states" << endl;
    while (true)
    {
        cout << "Would you like to check for the [o]ccurrence of a substring, the [f]irst position of a substring, [a]ll positions of a substring, or [q]uit?" << endl;
        unordered_set<char> input{'a', 'o', 'f', 'q'};
        cin.get(a);
        while (input.count(a) < 1)
        {
            cin.get(a);
        }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (a == 'a')
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
        else if (a == 'f')
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
        else if (a == 'o')
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
        else if (a == 'q')
        {
            cout << "Quitting" << endl;
            return 0;
        }
    }
}