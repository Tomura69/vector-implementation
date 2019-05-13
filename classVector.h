#pragma once
#include <iostream>

using std::cout;
using std::endl;

template <class T>
class Vector{
private:
    int ssize;
    int ccapacity;
    T* values;
public:

    typedef T* Iterator;

    Vector ();
    Vector (int size_);
    Vector (int size_, const T & values_);
    Vector (const Vector<T>& v);
    ~Vector ();

    inline int capacity () const {return ccapacity;}
    inline int size () const {return ssize;}
    inline bool empty () const {return ssize == 0;}
    inline T* begin () {return values;}
    inline T* end () {return values + ssize;}
    void push_back (const T& v);
    void pop_back ();

    void reserve (int capacity_);
    void resize (int size_);

    inline T& operator[] (int index) {return values[index];}
    Vector<T> & operator = (const Vector<T>&);
    void clear ();
};

template<class T>
Vector<T>::Vector() {
    ssize = 0;
    ccapacity = 0;
    values = 0;
}

template<class T>
Vector<T>::Vector(int size_) {
    ssize = size_;
    ccapacity = size_;
    values = new T[ccapacity];
}

template<class T>
Vector<T>::Vector(int size_, const T& values_) {
    ssize = size_;
    ccapacity = size_;
    values = new T [ccapacity];
    for (int i = 0; i < ssize; i++)
        values[i] = values_;
}

template<class T>
Vector<T>::Vector(const Vector<T> & v) {
    ssize = v.ssize;
    ccapacity = v.ccapacity;
    values = new T[ssize];
    for (int i = 0; i < ssize; i++)
        values[i] = v.values[i];
}

template<class T>
Vector<T>::~Vector() {
    delete[] values;
}

template<class T>
void Vector<T>::push_back(const T& v) {
    ssize++;
    if (ssize > ccapacity) {
        reserve(ccapacity * 2);
    }
    values[ssize - 1] = v;
}

template<class T>
void Vector<T>::pop_back() {
    //delete [] values;
    ssize--;
}
template<class T>
void Vector<T>::reserve(int capacity_) {
    T* newvalues = new T[capacity_];

    for (int i = 0; i < ssize; i++)
        newvalues[i] = values[i];

    ccapacity = capacity_;
    delete[] values;
    values = newvalues;
}

/*template<class T>
void Vector<T>::resize(int size) {
    Log = ceil(log((double) size) / log(2.0));
    reserve(1 << Log);
    _size = size;
}*/

template<class T>
Vector<T>& Vector<T>::operator = (const Vector<T> & v) {
    delete[] values;
    ssize = v.ssize;
    ccapacity = v.ccapacity;
    values = new T [ccapacity];
    for (int i = 0; i < ssize; i++)
        values[i] = v.values[i];
    return *this;
}

template <class T>
void Vector<T>::clear() {
    delete[] values;
    ccapacity = 0;
    ssize = 0;
    values = 0;
}


/*
#define MAX_VECTOR_SIZE 1073741824U
template<typename T>
inline typename Vector<T>::size_type Vector<T>::max_size() const noexcept
{
    return MAX_VECTOR_SIZE;
}*/