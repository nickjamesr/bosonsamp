// main.cc
// Main code file, currently used for testing

#include "heads/main.h"
#include "heads/vector.h"
#include "heads/matrix.h"
#include "heads/permanent.h"
#include "heads/combinatorics.h"

#include <iostream>
#include <complex>

int main(int argc, char** argv){
  uint m=4,p=3;
  multiset c(m,p);
  for (uint i=0; i<choose(m+p-1,p); i++){
    c.fromindex(i);
    c.print();
  }
}
