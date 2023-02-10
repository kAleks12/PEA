//
// Created by kacper on 14.03.2022.
//

#pragma once

#include <cstdio>
#include <string>

template<typename T>
class LiteDynamicArray {
    //Class variables
    T *head = nullptr;
    size_t size = 0;

    int partition(int low, int high);
    void quickSort(int low, int high);

public:
    LiteDynamicArray();
    LiteDynamicArray(const LiteDynamicArray<T> &existingArray);
    ~LiteDynamicArray();

    T at(int index) const;
    T *begin();
    T *end();
    T &operator[](const size_t &index); //Overload of [] operator
    LiteDynamicArray<T> &operator=(LiteDynamicArray<T> other); //Overload of = operator
    bool operator==(LiteDynamicArray<T> other); //Overload of == operator

    void swap(int index1, int index2); //Swap index 1 with index 2
    void addBack(const T &val); //Add val at the end of the table
    void addFront(const T &val); //Add val at the beginning of the table
    void add(const T &val, int position); //Add val at the beginning of the table
    void removeBack(); //Remove element from the end of the table
    void removeFront(); //Remove element from the front of the table
    void remove(const size_t &position); //Remove element from the front of the table
    void clear();
    bool contains(T element);
    bool isEmpty();
    void sort();

    //Return curr size of the table
    int getSize() const {
        return this->size;
    }
};
