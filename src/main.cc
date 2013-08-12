// main.cc
// Main code file, currently used for testing

#include "heads/main.h"
#include "heads/vector.h"
#include "heads/matrix.h"
#include "heads/permanent.h"
#include "heads/combinatorics.h"
#include "heads/sampling.h"

#include <iostream>
#include <fstream>
#include <complex>

int main(int argc, char** argv){
  uint modes=25,photons=5,nreps=100000;
  std::ofstream fout("dat/5x5.dat", std::ostream::out);
  std::cout << choose(modes+photons-1,photons) << std::endl;
  matrix<std::complex<double> > m = haar(modes);
  sampler_exact s(m, photons);
  for (uint i=0; i<nreps; i++){
    fout << s.get().index() << std::endl;
  }
  fout.close();
}
