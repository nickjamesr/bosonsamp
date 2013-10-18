// sampling.h
// header files for sampling algorithms

#ifndef sample_h
#define sample_h

#include "combinatorics.h"
#include "permanent.h"
#include "matrix.h"

#include <vector>
#include <complex>
#include <algorithm>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <curses.h>

class sampler_exact{
  private:
    uint m;
    uint p;
    uint size;
    uint seed;
    double *pdf;
    gsl_rng* rng;
    gsl_ran_discrete_t* gen;
  protected:
  public:
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
    ~sampler_reject();
    // Overloads
    sampler_reject operator=(const sampler_reject&);
    // Access
    combination get(uint);
};

class sampler_classical{
  private:
    matrix<double> u;
    uint m;
    uint seed;
    gsl_rng* r;
  protected:
  public:
    // Constructors
    sampler_classical();
    sampler_classical(const sampler_classical&);
    sampler_classical(matrix<std::complex<double> >, uint init=0);
    // Destructor
    ~sampler_classical();
    // Overloads
    sampler_classical operator=(const sampler_classical&);
    // Access
    combination get(uint);
};

class sampler_uniform{
  private:
    uint m;
    uint seed;
    gsl_rng* r;
  protected:
  public:
    // Constructors
    sampler_uniform();
    sampler_uniform(const sampler_uniform&);
    sampler_uniform(uint, uint init=0);
    // Destructor
    ~sampler_uniform();
    // Overloads
    sampler_uniform operator=(const sampler_uniform&);
    // Access
    combination get(uint);
};

#endif
