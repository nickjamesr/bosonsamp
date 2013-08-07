// vector.h
// header file for my (minimal) vector class

#ifndef vector_h
#define vector_h

#include <cstdlib>
#include <iostream>

template <class T>
class vector{
  private:
    uint len;
    T *data;
  protected:
  public:
    // Constructors
    vector();
    vector(uint n);
    vector(uint, T);
    vector(const vector<T>&);
    // Destructor
    ~vector();
    // Overloads
    vector<T> operator=(const vector<T>&);
    // Access
    T& operator[](uint);
    // Output
    void print();
};

#include "vector.cc"

#endif
