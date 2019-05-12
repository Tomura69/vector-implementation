#pragma once
#include <iostream>

using std::cout;
using std::endl;

template <class T>
class Vector{
private:
    int size;
    int capacity;
    T* values;
public:

    typedef T* Iterator;

    Vector ();
    Vector (int size_);
    Vector (int size_, const T & values_);
    Vector (const Vector<T>& v);
    ~Vector ();

    inline int capacityFun () const {return capacity;}
    inline int sizeFun () const {return size;}
    inline bool empty () const {return size == 0;}
    inline T* begin () {return values;}
    inline T* end () {return values + size;}
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
    size = 0;
    capacity = 0;
    values = 0;
}

template<class T>
Vector<T>::Vector(int size_) {
    size = size_;
    capacity = size_;
    values = new T[capacity];
}

template<class T>
Vector<T>::Vector(int size_, const T& values_) {
    size = size_;
    capacity = size_;
    values = new T [capacity];
    for (int i = 0; i < size; i++)
        values[i] = values_;
}

template<class T>
Vector<T>::Vector(const Vector<T> & v) {
    size = v.size;
    capacity = v.capacity;
    values = new T[size];
    for (int i = 0; i < size; i++)
        values[i] = v.values[i];
}

template<class T>
Vector<T>::~Vector() {
    delete[] values;
}

template<class T>
void Vector<T>::push_back(const T& v) {
    size++;
    if (size > capacity) {
        reserve(capacity * 2);
    }
    values[size] = v;
}

template<class T>
void Vector<T>::pop_back() {
    //delete [] values;
    size--;
}
template<class T>
void Vector<T>::reserve(int capacity_) {
    T* newvalues = new T[capacity_];

    for (int i = 0; i < size; i++)
        newvalues[i] = values[i];

    cout << "afsgfD" << size << endl;
    capacity = capacity_;
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
    size = v.size;
    capacity = v.capacity;
    values = new T [capacity];
    for (int i = 0; i < size; i++)
        values[i] = v.values[i];
    return *this;
}

template <class T>
void Vector<T>::clear() {
    delete[] values;
    capacity = 0;
    size = 0;
    values = 0;
}


/*
#define MAX_VECTOR_SIZE 1073741824U
template<typename T>
inline typename Vector<T>::size_type Vector<T>::max_size() const noexcept
{
    return MAX_VECTOR_SIZE;
}

template <class T>
class  Vector {
public:

    typedef T* Iterator;

    Vector();
    Vector(unsigned int size);
    Vector(unsigned int size, const T & initial);
    Vector(const Vector<T>& v);
    ~Vector();

    unsigned int capacity() const;
    unsigned int size() const;
    bool empty() const;
    Iterator begin();
    Iterator end();
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();

    void reserve(unsigned int capacity);
    void resize(unsigned int size);

    T & operator[](unsigned int index);
    Vector<T> & operator = (const Vector<T> &);
    void clear();
private:
    unsigned int _size;
    unsigned int _capacity;
    unsigned int Log;
    T* buffer;
};
template<class T>
Vector<T>::Vector() {
    _capacity = 0;
    _size = 0;
    buffer = 0;
    Log = 0;
}

template<class T>
Vector<T>::Vector(const Vector<T> & v) {
    _size = v._size;
    Log = v.Log;
    _capacity = v._capacity;
    buffer = new T[_size];
    for (unsigned int i = 0; i < _size; i++)
        buffer[i] = v.buffer[i];
}

template<class T>
Vector<T>::Vector(unsigned int size) {
    _size = size;
    Log = ceil(log((double) size) / log(2.0));
    _capacity = 1 << Log;
    buffer = new T[_capacity];
}

template <class T>
bool Vector<T>:: empty() const {
    return _size == 0;
}
template<class T>
Vector<T>::Vector(unsigned int size, const T& initial) {
    _size = size;
    Log = ceil(log((double) size) / log(2.0));
    _capacity = 1 << Log;
    buffer = new T [_capacity];
    for (unsigned int i = 0; i < size; i++)
        buffer[i] = initial;
}

template<class T>
Vector<T>& Vector<T>::operator = (const Vector<T> & v) {
    delete[] buffer;
    _size = v._size;
    Log = v.Log;
    _capacity = v._capacity;
    buffer = new T [_capacity];
    for (unsigned int i = 0; i < _size; i++)
        buffer[i] = v.buffer[i];
    return *this;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::begin() {
    return buffer;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::end() {
    return buffer + size();
}
template<class T>
T& Vector<T>::front() {
    return buffer[0];
}

template<class T>
T& Vector<T>::back() {
    return buffer[_size - 1];
}

template<class T>
void Vector<T>::push_back(const T & v) {
    /*
        Incidentally, one common way of regrowing an array is to double the size as needed.
        This is so that if you are inserting n items at most only O(log n) regrowths are performed
        and at most O(n) space is wasted.
    *//*
    if (_size >= _capacity) {
        reserve(1 << Log);
        Log++;
    }
    buffer [_size++] = v;
}

template<class T>
void Vector<T>::pop_back() {
    _size--;
}
template<class T>
void Vector<T>::reserve(unsigned int capacity) {
    T * newBuffer = new T[capacity];

    for (unsigned int i = 0; i < _size; i++)
        newBuffer[i] = buffer[i];

    _capacity = capacity;
    delete[] buffer;
    buffer = newBuffer;
}

template<class T>
unsigned int Vector<T>::size() const {
    return _size;
}

template<class T>
void Vector<T>::resize(unsigned int size) {
    Log = ceil(log((double) size) / log(2.0));
    reserve(1 << Log);
    _size = size;
}

template<class T>
T& Vector<T>::operator[](unsigned int index) {
    return buffer[index];
}

template<class T>
unsigned int Vector<T>::capacity()const {
    return _capacity;
}
template<class T>
Vector<T>::~Vector() {
    delete[] buffer;
}

template <class T>
void Vector<T>::clear() {
    _capacity = 0;
    _size = 0;
    buffer = 0;
    Log = 0;
}*/