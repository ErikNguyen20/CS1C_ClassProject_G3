// a vector which approximates the stl vector

#include <algorithm>
using std::copy;

#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class vector
{
private:
    int size_v; // the size
    T* elem; // a pointer to the array of elements
    int space; // size+free_space (capacity)

public:
    vector(); // default constructor
    explicit vector(int s); // alternate constructor
    vector(const vector&); // copy constructor
    vector& operator=(const vector&); // copy assignment
    vector(vector&&); // move constructor
    vector& operator=(vector&&); // move assignment
    ~vector(); // destructor
    T& operator[] (int n); // access: return reference
    const T& operator[] (int n) const; // access: return reference
    int size() const; // the current size
    int capacity() const; // current available space
    void resize(int newsize); // grow

    void push_back(T val); // add element
    void reserve(int newalloc); // get more space
    using iterator = T*;
    using const_iterator = const T*;

    iterator begin() { // points to first element
        if (size_v == 0) {
            return nullptr;
        }
        return &elem[0];
    }
    const_iterator begin() const {
        if (size_v == 0) {
            return nullptr;
        }
        return &elem[0];
    }
    
    iterator end() { // points to one beyond the last element
        if (size_v == 0) {
            return nullptr;
        }
        return &elem[size_v];
    }
    
    const_iterator end() const {
        if (size_v == 0) {
            return nullptr;
        }
        return &elem[size_v];
    }
    iterator insert(iterator p, const T& v) { // insert a new element v before p
        if (size_v == space) {
            return nullptr;
        }
        for (iterator pos = p + 1; pos != end(); pos++) {
            *(pos + 1) = *pos;
        }
        elem[p] = v;
        size_v++;
        return nullptr;
    }
    iterator erase(iterator p) { // remove element pointed to by p
        if (p == end()) {
            return p;
        }
        for (iterator pos = p + 1; pos != end(); pos++) {
            *(pos - 1) = *pos;
        }
        delete (end() - 1);
        size_v--;
        return p;
    }
    
};

// definitions

template<typename T>
vector<T>::vector() : size_v{ 0 }, elem{ nullptr }, space{ 0 } {}

template<typename T>
vector<T>::vector(int s) : size_v{ 0 }, elem{ new T[s] }, space{ s } {}

template<typename T>
vector<T>::vector(const vector& v) : size_v{ v.size_v }, elem{ new T[v.space] }, space{ v.space }
{
    copy(v.elem, v.elem + size_v, elem);
}

template<typename T>
vector<T>& vector<T>::operator=(const vector& v)
{
    T *p = new T[v.size_v];
    copy(v.elem, v.elem + v.size_v, p);
    delete elem;
    elem = p;
    size_v = v.size_v;
    return *this;
}

template<typename T>
vector<T>::vector(vector&& v)
{
    elem = v.elem;

    size_v = v.size_v;
    space = v.space;

    v.elem = nullptr;
}

template<typename T>
vector<T>& vector<T>::operator=(vector&& v)
{
    delete[] elem;

    elem = v.elem;

    size_v = v.size_v;
    space = v.space;

    v.elem = nullptr;

    return *this;
}

template<typename T>
vector<T>::~vector()
{
    delete[] elem;
}

template<typename T>
T& vector<T>::operator[] (int n)
{
    return elem[n];
}

template<typename T>
const T& vector<T>::operator[] (int n) const
{
    return elem[n];
}

template<typename T>
int vector<T>::size() const
{
    return size_v;
}

template<typename T>
int vector<T>::capacity() const
{
    return space;
}

template<typename T>
void vector<T>::resize(int newsize)
{
    reserve(newsize);
    /*for (int i = size_v; i < newsize; i++) {
        elem[i] = 0;
    }*/
    size_v = newsize;
}

template<typename T>
void vector<T>::push_back(T val) {
    if (space == 0) {
        reserve(8);
    }
    else if (size_v == space) {
        reserve(2 * space);
    }
    elem[size_v] = val;
    size_v++;
}

template<typename T>
void vector<T>::reserve(int newalloc) {
    if(newalloc <= space) {
        return;
    }
    T *p = new T[newalloc];
    for (int i = 0; i < size_v; i++) {
        p[i] = elem[i];
    }
    delete[] elem;
    elem = p;
    space = newalloc;
}

#endif
