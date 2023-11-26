#ifndef SUFFIXAUTOMATON_CIRCULARARRAYMOD_H
#define SUFFIXAUTOMATON_CIRCULARARRAYMOD_H

#include <iostream>
#include <string>
#include "nodeMod.h"
using namespace std;

template <class T, typename K, typename V>
class CircularArray {
private:
    Node<K, V>* array;
    int capacity{};
    int factorMulti = 2; //factor de multiplicidad para escalado del array
    int back{}, front{};
public:
    explicit CircularArray(int _capacity = 10);
    virtual ~CircularArray();
    void push_front(Node<K, V> data); // inserta el valor al cominzo
    void push_back(Node<K, V> data);
    void insert(Node<K, V> data, int pos);
    Node<K, V> pop_front();
    Node<K, V> pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    Node<K, V>& operator[](int index);
    string to_string(string sep=" ");
private:
    int next(int);
    int prev(int);
    void redimensionar();
};

template <typename T, typename K, typename V>
int CircularArray<T, K, V>::next(int index) {
    return (index+1)%capacity;
}
template <typename T, typename K, typename V>
int CircularArray<T, K, V>::prev(int index) {
    if (index == -1 || index == 0)
        return capacity-1;
    return index-1;
}

template <typename T, typename K, typename V>
void CircularArray<T, K, V>::redimensionar() {
    int _capacity = capacity*factorMulti;
    Node<K, V>* arrayTemp = new Node<K, V>[_capacity];
    for(int i = 0; i < capacity; i++){
        arrayTemp[i] = array[(front+i)%capacity];
    }
    front = 0;
    back = capacity-1;
    capacity = _capacity;
    delete[] array;
    array = arrayTemp;
}

template <typename T, typename K, typename V>
CircularArray<T, K, V>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->array = new Node<K, V>[_capacity];
    this->front = this->back = -1;//empty
    this->factorMulti = 2;
}

template <typename T, typename K, typename V>
CircularArray<T, K, V>::~CircularArray() {
    delete [] array;
}

template <typename T, typename K, typename V>
void CircularArray<T, K, V>::push_front(Node<K, V> data) { // agrega al inicio del array Circular
    if(is_full()){
        redimensionar();
        front = prev(front);
    }
    else if(is_empty()){
        front = back = 0;
    }
    else {
        front = prev(front);
    }
    array[front] = data;
}

template <typename T, typename K, typename V>
void CircularArray<T, K, V>::push_back(Node<K, V> data){
    if(is_full()){
        redimensionar();
        back = next(back);
    }
    else if(is_empty()){
        front = back = 0;
    }
    else{
        back = next(back);
    }
    array[back] = data;
}

template <typename T, typename K, typename V>
void CircularArray<T, K, V>::insert(Node<K, V> data, int pos) {
    try{
        if(pos > size())
            throw std::exception();
        if(pos == 0){ // si se inserta al inicio del array, entonces solo se hace un push_front
            push_front(data);
        }
        else if(pos == size()-1){ //si se inserta al final del array, entonces solo hace un push_back
            push_back(data);
        }
        else{
            if(is_empty()){
                push_back(data);
            }
            if (size()+1 > capacity){
                redimensionar();
            }
            pos = (front+pos)%capacity;
            front = prev(front);
            array[front] = data;
            Node<K, V> aux;
            for(int i = front; i != pos; i = next(i)) {
                aux = array[i];
                array[i] = array[next(i)];
                array[next(i)] = aux;
            }
        }
    } catch (...){
        cout << "Index fuera de rango" << endl;
    }
}

template <typename T, typename K, typename V>
Node<K, V> CircularArray<T, K, V>::pop_front() {
    try{
        if(is_empty()){
            throw std::exception();
        }
        if(size() == 1) {
            int pos = front;
            clear();
            return array[pos];
        }
        else{
            front = next(front);
            return array[prev(front)];
        }
    } catch(...){
        cout << "Array vacio. No se puede hacer pop_front" << endl;
        static Node<K, V> dummy;
        return dummy;
    }
}

template <typename T, typename K, typename V>
Node<K, V> CircularArray<T, K, V>::pop_back() {
    try{
        if(is_empty()){
            throw std::exception();
        }
        if(size() == 1) {
            Node<K, V> result = array[back];
            clear();
            return result;
        }
        else{
            back = prev(back);
            return array[next(back)];
        }
    } catch(...){
        cout << "Array vacio. No se puede hacer pop_back" << endl;
        static Node<K, V> dummy;
        return dummy;
    }
}

template <typename T, typename K, typename V>
bool CircularArray<T, K, V>::is_full() {
    return back == prev(front);
}

template <typename T, typename K, typename V>
bool CircularArray<T, K, V>::is_empty() {
    if (front == -1 && back == -1) {
        return true;
    } return false;
}

template <typename T, typename K, typename V>
int CircularArray<T, K, V>::size() {
    if(front > back)
        return (capacity-front)+(back+1);
    else
        return (back-front)+1;
}

template <typename T, typename K, typename V>
void CircularArray<T, K, V>::clear() {
    front = back = -1;
}

template <typename T, typename K, typename V>
Node<K, V>& CircularArray<T, K, V>::operator[](int index) {
    try {
        if(is_empty())
            throw std::runtime_error("Array vacio");
        if(index>=size() || index < 0){
            throw std::exception();
        }
        if (front + index < capacity)
            return array[front + index];
        return array[(front+index)%capacity];
    } catch (const std::exception &e) {
        cout << e.what() << endl;
        static Node<K, V> dummy;
        return dummy;
    }
}

template <typename T, typename K, typename V>
string CircularArray<T, K, V>:: to_string(string sep){
    string result = "";
    int index = front;
    if(!is_empty()){
        int n = size();
        for(int i = 0; i<n; i++){
            result += std::to_string(array[index].key) + ": " + std::to_string(array[index].value) + sep;
            index = next(index);
        }
    }
    return result;
}

#endif //SUFFIXAUTOMATON_CIRCULARARRAYMOD_H