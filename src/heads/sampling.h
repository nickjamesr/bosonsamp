// sampling.h
// header files for sampling algorithms

#ifndef sample_h
#define sample_h

#include "combinatorics.h"
#include "permanent.h"
#include "matrix.h"

#include <complex>
#include <gsl/gsl_rng.h>
#include <curses.h>

class sampler_exact{
  private:
    uint m;
    uint p;
    uint size;
    uint seed;
    gsl_rng* r;
  protected:
  public:
    double* cdf;
    // Constructors
    sampler_exact();
    sampler_exact(const sampler_exact&);
    sampler_exact(matrix<std::complex<double> >, uint, uint init=0);
    // Destructor
    ~sampler_exact();
    // Overloads
    sampler_exact operator=(const sampler_exact&);
    // Access
    combination get();
};

class sampler_reject{
  private:
    matrix<std::complex<double> > u;
    uint m;
    uint seed;
    gsl_rng* r;
  protected:
  public:
    // Constructors
    sampler_reject();
    sampler_reject(const sampler_reject&);
    sampler_reject(matrix<std::complex<double> >, uint init=0);
    // Destructor
    // Overloads
    sampler_reject operator=(const sampler_reject&);
    // Access
    combination get(uint);
};

#endif
