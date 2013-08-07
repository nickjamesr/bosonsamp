// main.cc
// Main code file, currently used for testing

#include "heads/main.h"
#include "heads/vector.h"
#include "heads/matrix.h"
#include "heads/permanent.h"
#include "heads/combination.h"

#include <iostream>

int main(int argc, char** argv){
  combination c(5,3);
  do{
    c.print();
  } while (c.next());
}
