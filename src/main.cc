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
  multiset m(3,4);
  do{
    m.print();
    std::cout << norm(m) << std::endl;
  } while (m.next());
}
