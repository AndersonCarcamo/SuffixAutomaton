#ifndef SUFFIXAUTOMATON_NODEMOD_H
#define SUFFIXAUTOMATON_NODEMOD_H

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node() = default;
    Node(K k, V v);
    ~Node() =  default;
};

template <typename K, typename V>
Node<K, V>::Node(K k, V v): key(k), value(v){}


#endif //SUFFIXAUTOMATON_NODEMOD_H
