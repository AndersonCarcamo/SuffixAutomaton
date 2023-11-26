#ifndef SUFFIXAUTOMATON_NODEMOD_H
#define SUFFIXAUTOMATON_NODEMOD_H

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node();
    Node(K k, V v);
    ~Node();
};

template <typename K, typename V>
Node<K, V>::Node(K k, V v): key(k), value(v){}

template <typename K, typename V>
Node<K,V>::~Node() {
}

#endif //SUFFIXAUTOMATON_NODEMOD_H
