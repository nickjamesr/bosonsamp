// combination.h
// header file for combination class

#ifndef combination_h
#define combination_h

#include <iostream>
#include <cstdlib>

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
    // initialisation
    void first();
    void last();
    // iteration
    bool prev();
    bool next();
};

#endif
