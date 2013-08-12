// sampling.h
// header files for sampling algorithms

#ifndef sample_h
#define sample_h

#include "combinatorics.h"
#include "permanent.h"
#include "matrix.h"

#include <complex>
#include <gsl/gsl_rng.h>

class sampler_exact{
  private:
    uint m;
    uint p;
    uint size;
    uint seed;
  protected:
  public:
    double* cdf;
    gsl_rng* r;
    // Constructors
    sampler_exact();
    sampler_exact(const sampler_exact&);
    sampler_exact(matrix<std::complex<double> >, uint, uint init=0);
    // Destructor
    ~sampler_exact();
    // Overloads
    sampler_exact operator=(const sampler_exact&);
    // Access
    multiset get();
};

#endif
