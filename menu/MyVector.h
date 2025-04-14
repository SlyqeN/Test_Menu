#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>

template <typename T>
class MyVector {
private:
    T* arr;          
    int size;        
    int capacity;    

   
    void resize(int newCapacity) {
        T* temp = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        capacity = newCapacity;
    }

public:
   
    MyVector() {
        arr = nullptr;
        size = 0;
        capacity = 0;
    }

    
    MyVector(int n, const T& value = T()) {
        size = n;
        capacity = n;
        arr = new T[capacity];
        for (int i = 0; i < size; ++i) {
            arr[i] = value;
        }
    }

    
    ~MyVector() {
        delete[] arr;
    }

    
    void push_back(const T& value) {
        if (size >= capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        arr[size] = value;
        ++size;
    }

    
    void erase(int index) {
        if (index < 0 || index >= size) return;
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --size;
    }

    
    int getSize() const {
        return size;
    }

    
    T& operator[](int index) {
        return arr[index];
    }

    const T& operator[](int index) const {
        return arr[index];
    }

    
    T* begin() { return arr; }
    T* end() { return arr + size; }
    const T* begin() const { return arr; }
    const T* end() const { return arr + size; }

    
    T* data() {
        return arr;
    }
};

#endif 
