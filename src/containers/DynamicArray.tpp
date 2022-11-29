//
// Created by kacper on 14.03.2022.
//

#include "../../inc/containers/DynamicArray.hpp"
#include <fstream>
#include <iostream>


template<typename T>
DynamicArray<T>::DynamicArray() {
    //Initializing head
    this->head = new T[0];

    this->size = 0;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &existingArray): size(existingArray.size) {
    head = new T[size];

    for (int i = 0; i < size; i++) {
        head[i] = existingArray.head[i];
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(int start, int tableSize) {
    size = tableSize;
    head = new T[size];
    for (int i = 0; i < size; i++) {
        head[i] = start++;
    }
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    //Deleting head if it exists
    if (this->head != nullptr) {
        delete[] this->head;
    }
}

template<typename T>
T &DynamicArray<T>::operator[](const size_t &index) {
    //Checking whether index is in bounds of array
    if (index > this->size) {
        std::string errorMsg = "Index " + std::to_string(index) + " out of bounds!";
        throw std::invalid_argument(errorMsg);
    }

    return *(this->head + index);
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> other)
{
    delete[] head;

    this->size = other.size;
    this->head = new T[other.size];

    for (size_t i = 0; i < size; i++)
    {
        this->head[i] = other.head[i];
    }

    return *this;
}

template<typename T>
void DynamicArray<T>::addBack(const T &val) {
    //Creating new head
    T *newHead = new T[this->size + 1];

    //Restoring elements from the old table
    if (this->size > 0) {
        for (int i = 0; i < this->size; i++) {
            newHead[i] = this->head[i];
        }
    }

    //Setting new element
    newHead[this->size] = val;

    //Deleting old head and swapping it for the new one
    delete[] this->head;
    this->head = newHead;
    this->size++;
}

template<typename T>
void DynamicArray<T>::addFront(const T &val) {
    //Creating new head
    T *newHead = new T[this->size + 1];

    //Setting value
    newHead[0] = val;

    //restoring elements from old array
    if (this->size > 0) {
        for (int i = 1; i <= this->size; i++) {
            newHead[i] = this->head[i - 1];
        }
    }

    //Deleting old head and swapping it for the new one
    delete[] this->head;
    this->head = newHead;
    this->size++;
}


template<typename T>
void DynamicArray<T>::removeBack() {
    //Checking whether array is empty
    if (this->size == 0) {
        return;
    }

    //Creating new head
    T *newHead = new T[this->size - 1];

    //Restoring old elements without the last one
    for (int i = 0; i < this->size - 1; i++) {
        newHead[i] = this->head[i];
    }

    //Deleting old head and swapping it for the new one
    delete[] this->head;
    this->head = newHead;
    this->size--;
}

template<typename T>
void DynamicArray<T>::removeFront() {
    //Checking whether array is empty
    if (this->size == 0) {
        return;
    }

    //Creating new head
    T *newHead = new T[this->size - 1];

    //Restoring old elements without the first one
    for (int i = 0; i < this->size - 1; i++) {
        newHead[i] = this->head[i + 1];
    }

    //Deleting old head and swapping it for the new one
    delete[] this->head;
    this->head = newHead;
    this->size--;
}

template<typename T>
T DynamicArray<T>::at(int index) const {
    if (index > this->size || index < 0) {
        std::string errorMsg = "Index " + std::to_string(index) + " out of bounds!";
        throw std::invalid_argument(errorMsg);
    }

    return *(this->head + index);
}

template<typename T>
T *DynamicArray<T>::begin() {
    return head;
}


template<typename T>
T *DynamicArray<T>::end() {
    return head + size;
}


template<typename T>
void DynamicArray<T>::print() {
    std::cout << "Array body: \n( ";

    for (int i = 0; i < this->size; i++) {
        if (i == size - 1) {
            std::cout << head[i];
            continue;
        }

        std::cout << head[i] << ", ";
    }
    std::cout << " )\n";
}

template<typename T>
void DynamicArray<T>::clear() {
    delete[] head;

    this->head = new T[0];
    this->size = 0;
}

template<typename T>
void DynamicArray<T>::swap(int index1, int index2) {
    if (index1 > this->size || index1 < 0) {
        std::string errorMsg = "Index " + std::to_string(index1) + " out of bounds!";
        throw std::invalid_argument(errorMsg);
    }
    if (index2 > this->size || index2 < 0) {
        std::string errorMsg = "Index " + std::to_string(index2) + " out of bounds!";
        throw std::invalid_argument(errorMsg);
    }
    if (index1 == index2) {
        return;
    }

    auto tmp = head[index1];
    head[index1] = head[index2];
    head[index2] = tmp;
}

template
class DynamicArray<int>;

template
class DynamicArray<size_t>;