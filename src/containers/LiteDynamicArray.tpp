//
// Created by kacpe on 27.12.2022.
//
//
// Created by kacper on 14.03.2022.
//

#include "../../inc/containers/LiteDynamicArray.h"
#include "../../inc/containers/Member.h"
#include <fstream>
#include <iostream>


template<typename T>
LiteDynamicArray<T>::LiteDynamicArray() {
    //Initializing head
    this->head = new T[0];

    this->size = 0;
}

template<typename T>
LiteDynamicArray<T>::LiteDynamicArray(const LiteDynamicArray<T> &existingArray): size(existingArray.size) {
    head = new T[size];

    for (int i = 0; i < size; i++) {
        head[i] = existingArray.head[i];
    }
}

template<typename T>
LiteDynamicArray<T>::~LiteDynamicArray() {
    //Deleting head if it exists
    if (this->head != nullptr) {
        delete[] this->head;
    }
}

template<typename T>
T &LiteDynamicArray<T>::operator[](const size_t &index) {
    //Checking whether index is in bounds of array
    if (index > this->size) {
        std::string errorMsg = "Index " + std::to_string(index) + " out of bounds!";
        throw std::invalid_argument(errorMsg);
    }

    return *(this->head + index);
}

template<typename T>
LiteDynamicArray<T> &LiteDynamicArray<T>::operator=(const LiteDynamicArray<T> other) {
    delete[] head;

    this->size = other.size;
    this->head = new T[other.size];

    for (size_t i = 0; i < size; i++) {
        this->head[i] = other.head[i];
    }

    return *this;
}

template<typename T>
bool LiteDynamicArray<T>::operator==(const LiteDynamicArray<T> other) {
    if (this->size != other.size) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (this->head[i] != other.head[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
void LiteDynamicArray<T>::addBack(const T &val) {
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
void LiteDynamicArray<T>::addFront(const T &val) {
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
void LiteDynamicArray<T>::removeBack() {
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
void LiteDynamicArray<T>::removeFront() {
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
void LiteDynamicArray<T>::remove(const size_t &position) {
    //Checking whether position is within bounds of the array
    if (position >= this->size) {
        throw std::out_of_range("Out of range!");
    }

    //Checking whether array is empty
    if (this->size == 0) {
        return;
    }

    //Checking whether to call removeFront()
    if (position == 0) {
        removeFront();
        return;
    }

    //Checking whether to call removeBack()
    if (position == size - 1) {
        removeBack();
        return;
    }

    //Creating new head
    T *newHead = new T[this->size - 1];

    //Restoring ol elements till position index
    for (int i = 0; i < position; i++) {
        newHead[i] = this->head[i];
    }

    //Restoring rest of the elements without one on position index
    for (int i = position; i < this->size - 1; i++) {
        newHead[i] = this->head[i + 1];
    }

    //Deleting old head and swapping it for the new one
    delete[] this->head;
    this->head = newHead;
    this->size--;
}

template<typename T>
T LiteDynamicArray<T>::at(int index) const {
    if (index > this->size || index < 0) {
        std::string errorMsg = "Index " + std::to_string(index) + " out of bounds!";
        throw std::invalid_argument(errorMsg);
    }

    return *(this->head + index);
}

template<typename T>
T *LiteDynamicArray<T>::begin() {
    return head;
}

template<typename T>
T *LiteDynamicArray<T>::end() {
    return head + size;
}

template<typename T>
bool LiteDynamicArray<T>::isEmpty() {
    return this->size == 0;
}

template<typename T>
void LiteDynamicArray<T>::clear() {
    delete[] head;

    this->head = new T[0];
    this->size = 0;
}

template<typename T>
bool LiteDynamicArray<T>::contains(T element) {
    for (int i = 0; i < size; ++i) {
        if (head[i] == element) {
            return true;
        }
    }

    return false;
}

template<typename T>
void LiteDynamicArray<T>::swap(int index1, int index2) {
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

template<typename T>
void LiteDynamicArray<T>::sort() {
    quickSort(0, size - 1);
}

template<typename T>
void LiteDynamicArray<T>::quickSort(int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

template<typename T>
int LiteDynamicArray<T>::partition(int low, int high) {
    T pivot = head[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates
    // the right position of pivot found so far

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (head[j] < pivot) {
            i++; // increment index of smaller element
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return (i + 1);
}

template
class LiteDynamicArray<Member>;
