// sampling.cc
// definitions for sampling classes/algorithms

#include "heads/sampling.h"

//---exact sampling---//
// Constructors
sampler_exact::sampler_exact(){
  m = p = size = seed = 0;
  cdf = new double[1];
  cdf[0] = 1.0;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
};

sampler_exact::sampler_exact(const sampler_exact& s){
  m = s.m;
  p = s.p;
  size = s.size;
  seed = s.seed;
  cdf = new double[size];
  for (uint i=0; i<size; i++){
    cdf[i] = s.cdf[i];
  }
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
}

sampler_exact::sampler_exact(matrix<std::complex<double> > mat, uint nphotons,
    uint init){
  m = mat.size();
  p = nphotons;

  matrix<std::complex<double> > submat(p);
  multiset c(m,p);
  std::complex<double> z;
  double cumulative=0;
  uint k,idx;
  double progress = 0;

  seed = init;
  size = choose(m+p-1,p);
  cdf = new double[size];
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
  // Generate the cdf...
  k = 0;
  do{
    while (k/(double)size > progress){
      std::cout << 100*progress << "%" << std::endl;
      progress += 0.02;
    }
    idx = 0;
    for (uint i=0; i<p; i++){
      for (uint j=0; j<p; j++){
        submat[idx] = mat[i*m+c[j]];
        //std::cout << "  " << i << "," << c[j] << std::endl;
        idx++;
      }
    }
    //submat.print();
    //c.print();
    //std::cout << norm(c) << std::endl;
    z = permanent(submat)*norm(c);
    //std::cout << z << std::endl;
    cumulative += std::real(z*std::conj(z));
    cdf[k] = cumulative;
    k++;
  } while (c.next());
  std::cout << "\n" << cumulative << std::endl;
}

// Destructor
sampler_exact::~sampler_exact(){
  delete[] cdf;
  gsl_rng_free(r);
}

// Overloads
sampler_exact sampler_exact::operator=(const sampler_exact& s){
  delete[] cdf;
  m = s.m;
  p = s.p;
  size = s.size;
  seed = s.seed;
  cdf = new double[size];
  gsl_rng_set(r,seed);
  for (uint i=0; i<size; i++){
    cdf[i] = s.cdf[i];
  }
  return *this;
}

// Access
multiset sampler_exact::get(){
  double x;
  uint lo=0,hi=size-1,mid;
  multiset state(m,p);
  x = gsl_rng_uniform(r);
  if (x<cdf[0]){
    state.fromindex(0);
    return state;
  }
  while (hi-lo>1){
    mid = (hi+lo+1)/2;
    if (cdf[mid]>x){
      hi = mid;
    }
    else{
      lo = mid;
    }
  }
  state.fromindex(hi);
  return state;
}






