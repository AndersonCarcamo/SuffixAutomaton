#ifndef SUFFIXAUTOMATON_CIRCULARARRAYMOD_H
#define SUFFIXAUTOMATON_CIRCULARARRAYMOD_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class CircularArray {
private:
    T* array;
    int capacity{};
    bool isFull;
    int factorMulti = 2; //factor de multiplicidad para escalado del array
    int back{}, front{};
    static const int INVALID_INDEX = -1;
public:
    CircularArray(int _capacity = 10);
    virtual ~CircularArray();
    void push_front(T data); // inserta el valor al cominzo
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    T getFront();
    T getBack();
    int Idxback() {return back;}
    int Idxfront() {return front;}
    int getCapacity() {return capacity;}
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T& operator[](int index);
    string to_string(string sep=" ");
    int next(int);
    int prev(int);
private:
    void redimensionar();
};

template <typename T>
int CircularArray<T>::next(int index) {
    return (index+1)%capacity;
}
template <typename T>
int CircularArray<T>::prev(int index) {
    if (index == -1 || index == 0)
        return capacity-1;
    return index-1;
}

template <typename T>
void CircularArray<T>::redimensionar() {
    int _capacity = capacity * factorMulti;
    T* arrayTemp = new T[_capacity];
    int _size = size(), _back = front;

    for (int i = 0; i < _size; i++) {
        arrayTemp[(front + i) % _capacity] = array[(front + i) % capacity];
        _back = (_back + 1) % _capacity;
    }

    delete[] array;
    array = arrayTemp;
    capacity = _capacity;

    // Update back index based on the new capacity
    back = prev(_back);
}



template <typename T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->array = new T[_capacity];
    this->front = this->back = -1;//empty
    this->factorMulti = 2;
    this->isFull = false;
}

template <typename T>
CircularArray<T>::~CircularArray() {

}

template <typename T>
void CircularArray<T>::push_front(T data) { // agrega al inicio del array Circular
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

template <typename T>
void CircularArray<T>::push_back(T data){
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

template <typename T>
void CircularArray<T>::insert(T data, int pos) {
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
            T aux;
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

template <typename T>
T CircularArray<T>::pop_front() {

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
}

template <typename T>
T CircularArray<T>::pop_back() {
    if(is_empty()){
        throw std::exception();
    }
    if(size() == 1) {
        T result = array[back];
        clear();
        return result;
    }
    else{
        back = prev(back);
        return array[next(back)];
    }
}

template <typename T>
T CircularArray<T>::getFront() {
    return array[front];
}

template <typename T>
T CircularArray<T>::getBack() {
    return array[back];
}

template <typename T>
bool CircularArray<T>::is_full() {
    return back == prev(front);
}

template <typename T>
bool CircularArray<T>::is_empty() {
    if (front == -1 && back == -1) {
        return true;
    } return false;
}

template <typename T>
int CircularArray<T>::size() {
    if(front > back)
        return (capacity-front)+(back+1);
    else
        return (back-front)+1;
}

template <typename T>
void CircularArray<T>::clear() {
    front = back = -1;
}

template <typename T>
T& CircularArray<T>::operator[](int index) {
    if (front + index < capacity)
        return array[front + index];
    return array[(front+index)%capacity];
}

template <typename T>
string CircularArray<T>:: to_string(string sep){
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