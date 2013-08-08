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
  uint n=4,p=3;
  multiset m(n,p);
  combination c(n+p-1,p);
  do{
    m.print();
    std::cout << m.index() << std::endl;
  } while (m.next());
}
