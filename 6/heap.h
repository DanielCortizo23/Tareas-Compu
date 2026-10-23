/*
 * heap.cpp
 *
 *  Created on: 23/10/2026
 *      Author: Daniel Cortizo
 */

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class Heap {
private:
    T *data;
	unsigned int max_size;
	unsigned int count;

	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);

public:
    Heap(unsigned int);
    ~Heap();
    string toString() const;
    bool empty() const;
	bool full() const;
	void pop();
	void push(T);
	unsigned int size() const;
	T top() const;
	void add(T);
};

template <class T>
Heap<T>::Heap(unsigned int sze) {
    max_size = sze;
    data = new T[max_size];
    count = 0;
}

template <class T>
Heap<T>::~Heap() {
    delete [] data;
    data = 0;
    max_size = 0;
    count = 0;
}


template <class T>
bool Heap<T>::empty() const {
    return (count == 0);
}

template <class T>
bool Heap<T>::full() const {
	return (count == max_size); 
}

template <class T>
unsigned int Heap<T>::size() const {
    return count;
}

template <class T>
unsigned int  Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return ((2 * pos) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return ((2 * pos) + 1);
}

template <class T>
string Heap<T>::toString() const {
    stringstream aux;

	aux << "[";
	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		}
		aux << data[i];
	}
	aux << "]";
	return aux.str();
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;

	if (le <= count && data[le] < data[min]) {
		min = le;
	}
	if (ri <= count && data[ri] < data[min]) {
		min = ri;
	}

	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::add(T val) {
    if (full()) {
        return;
    }
    unsigned int pos = count;
    count++;
    while (pos > 0 && val < data[parent(pos)]) {
        data[pos] = data[parent(pos)];
        pos = parent(pos);
    }
    data[pos] = val;
}

template <class T>
void Heap<T>::push(T val) {
	add(val);
}

template <class T>
void Heap<T>::pop() {
	if (empty()) {return;}

	count--;
	data[0] = data[count];
	heapify(0);
}

template <class T>
T Heap<T>::top() const {
	return data[0];
}

#endif