// permanent.h
// header files for permanent calculations

#ifndef permanent_h
#define permanent_h

#include "matrix.h"
#include "combinatorics.h"

template <class T>
inline T permanent1(matrix<T>);

template <class T>
inline T permanent2(matrix<T>);

template <class T>
inline T permanent3(matrix<T>);

template <class T>
inline T permanent4(matrix<T>);

template <class T>
T permanent_naive(matrix<T>);

template <class T>
T permanent_ryser(matrix<T>);

class set{
  private:
  protected:
  public:
};

#include "permanent.cc"

#endif
