
#include <algorithm>
using std::copy;

#ifndef VECTOR_H
#define VECTOR_H

//! Templated Vector Class
/*! A vector class that approximates the STL vector. */
template<typename T>
class vector
{
private:
    int size_v; /*!< Contains the number of elements in the vector. */
    T* elem;    /*!< Pointer to a dynamically allocated array on the heap. */
    int space;  /*!< Contains the capacity of the vector. */

public:
    //! Default Constructor
    /*! Constructs a new vector object. */
    vector(); // default constructor

    //! Alternate Constructor
    /*! Constructs a new vector object.
        \param s an integer argument for size.
    */
    explicit vector(int s); // alternate constructor

    //! Copy Constructor
    /*! Constructs a new vector object, copying the contents from the other vector.
        \param vector& an lvalue vector.
    */
    vector(const vector&); // copy constructor

    //! Copy Assignment
    /*! Copies the contents of one vector to the other.
        \param vector& an lvalue vector.
    */
    vector& operator=(const vector&); // copy assignment

    //! Move Constructor
    /*! Constructs a new vector object, moving the contents from the other vector.
        \param vector&& an rvalue vector.
    */
    vector(vector&&); // move constructor

    //! Move Assignment
    /*! Moves the contents of one vector to the other.
        \param vector&& an rvalue vector.
    */
    vector& operator=(vector&&); // move assignment

    //! Destructor
    /*! Destructs the vector object. */
    ~vector(); // destructor

    //! Overloaded Subscript Operator
    /*! Allows for access of a particular element.
        \param n an integer index.
        \return The element at a particular index.
    */
    T& operator[] (int n); // access: return reference

    //! Overloaded Subscript Operator
    /*! Allows for access of a particular element.
        \param n an integer index.
        \return A constant reference to the element at a particualr index.
    */
    const T& operator[] (int n) const; // access: return reference

    //! Member function that returns the size of the vector.
    /*!
        \return An integer size of the vector.
    */
    int size() const; // the current size

    //! Member function that returns the capacity of the vector.
    /*!
        \return An integer capacity of the vector.
    */
    int capacity() const; // current available space

    //! Member function that resizes the vector based on the parameter.
    /*!
        \param newsize an integer argument for size.
    */
    void resize(int newsize); // grow

    //! Member function that adds an element to the end of the vector.
    /*!
        \param val a value that is added to the back of the vector.
    */
    void push_back(T val); // add element

    //! Member function that reserves more space for the vector.
    /*!
        \param newalloc an integer capacity of the vector.
    */
    void reserve(int newalloc); // get more space
    using iterator = T*;
    using const_iterator = const T*;

    //! The begin iterator.
    /*!
        \return Iterator to the first element.
    */
    iterator begin() { // points to first element
        if (size_v == 0) {
            return nullptr;
        }
        return &elem[0];
    }

    //! The begin const_iterator.
    /*!
        \return Constant iterator to the first element.
    */
    const_iterator begin() const {
        if (size_v == 0) {
            return nullptr;
        }
        return &elem[0];
    }
    
    //! The end iterator.
    /*!
        \return Iterator to one past the last element.
    */
    iterator end() { // points to one beyond the last element
        if (size_v == 0) {
            return nullptr;
        }
        return &elem[size_v];
    }
    
    //! The end const_iterator.
    /*!
        \return Constant iterator to one past the last element.
    */
    const_iterator end() const {
        if (size_v == 0) {
            return nullptr;
        }
        return &elem[size_v];
    }

    //! Insert a new element at the iterator.
    /*!
        \param p an iterator pointing to the insertion position.
        \param v an element being inserted into the vector.
    */
    iterator insert(iterator p, const T& v) { // insert a new element v before p
        if (size_v == space) {
            return nullptr;
        }
        for (iterator pos = p + 1; pos != end(); pos++) {
            *(pos + 1) = *pos;
        }
        *p = v;
        size_v++;
        return nullptr;
    }

    //! Remove an element at the iterator.
    /*!
        \param p an iterator pointing to the deletion position.
        \return The iterator.
    */
    iterator erase(iterator p) { // remove element pointed to by p
        if (p == end()) {
            return p;
        }
        for (iterator pos = p + 1; pos != end(); pos++) {
            *(pos - 1) = *pos;
        }
//        delete (end() - 1);
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
    delete[] elem;
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
