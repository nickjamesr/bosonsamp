// matrix.h
// header file for my (minimal) matrix class

#ifndef matrix_h 
#define matrix_h

#include <cstdlib>
#include <iostream>

template <class T>
class matrix{
  private:
    uint dim;
    T *data;
  protected:
  public:
    // Constructors
    matrix();
    matrix(uint n);
    matrix(uint n, T t);
    matrix(const matrix<T>&);
    // Destructor
    ~matrix();
    // Overloads
    matrix<T> operator=(const matrix<T>&);
    // Access
    T& operator[](uint);
    uint size();
    // Output
    void print();
};

#include "matrix.cc"

#endif
