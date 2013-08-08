// combinatorics.h
// header file for combinatorics classes/functions

#ifndef comb_h
#define comb_h

#include <iostream>
#include <cstdlib>

long unsigned int choose(uint, uint);

class combination{
  private:
    uint m;
    uint p;
    uint *data;
  protected:
  public:
    // constructors
    combination();
    combination(uint, uint);
    combination(const combination&);
    // destructor
    ~combination();
    // overloads
    combination operator=(const combination&);
    // output
    void print() const;
    // access
    uint& operator[](uint) const;
    long unsigned int index();
    // initialisation
    void first();
    void last();
    void fromindex(uint);
    // iteration
    bool prev();
    bool next();
};

class multiset{
  private:
    uint m;
    uint p;
    uint *data;
  protected:
  public:
    // constructors
    multiset();
    multiset(uint, uint);
    multiset(const multiset&);
    // destructor
    ~multiset();
    // overloads
    multiset operator=(const multiset&);
    // output
    void print() const;
    // access
    uint& operator[](uint) const;
    long unsigned int index();
    // initialisation
    void first();
    void last();
    void fromindex(uint);
    // iteration
    bool prev();
    bool next();
};

#endif
