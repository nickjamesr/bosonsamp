// matrix.h
// header file for my (minimal) matrix class

#ifndef matrix_h 
#define matrix_h

#include <cstdlib>
#include <iostream>
#include <complex>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "combinatorics.h"

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
    void print() const;
};

matrix<std::complex<double> > haar(uint, uint seed=0);
std::complex<double> amplitude(multiset, matrix<std::complex<double> >,
  multiset);
std::complex<double> amplitude(combination, matrix<std::complex<double> >,
  combination);

#include "matrix.cc"

#endif
