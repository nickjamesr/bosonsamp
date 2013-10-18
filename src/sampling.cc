// sampling.cc
// definitions for sampling classes/algorithms

#include "heads/sampling.h"

//---exact sampling---//
// Constructors
sampler_exact::sampler_exact(){
  m = p = seed = 0;
  size = 1;
  pdf = new double[1];
  pdf[0] = 1.0;
  gen = gsl_ran_discrete_preproc(1,pdf);
  rng = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng, seed);
};

sampler_exact::sampler_exact(const sampler_exact& s){
  m = s.m;
  p = s.p;
  size = s.size;
  pdf = new double[size];
  for (uint i=0; i<size; i++){
    pdf[i] = s.pdf[i];
  }
  seed = s.seed;
  gen = gsl_ran_discrete_preproc(size, pdf);
  rng = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng, seed);
}

sampler_exact::sampler_exact(matrix<std::complex<double> > mat, uint nphotons,
    uint init){
  m = mat.size();
  p = nphotons;

  matrix<std::complex<double> > submat(p);
  combination c(m,p);
  std::complex<double> z;
  uint k,idx;

  seed = init;
  size = choose(m,p);
  pdf = new double[size];
  rng = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng, seed);
  // Generate the pdf
  k = 0;
  do{
    idx = 0;
    for (uint i=0; i<p; i++){
      for (uint j=0; j<p; j++){
        submat[idx] = mat[c[i]*m+j];
        idx++;
      }
    }
    z = permanent(submat);
    pdf[k] = std::real(z*std::conj(z));
    k++;
  } while (c.next());
  gen = gsl_ran_discrete_preproc(size, pdf);
}

// Destructor
sampler_exact::~sampler_exact(){
  delete[] pdf;
  gsl_rng_free(rng);
  gsl_ran_discrete_free(gen);
}

// Overloads
sampler_exact sampler_exact::operator=(const sampler_exact& s){
  gsl_ran_discrete_free(gen);
  delete[] pdf;
  m = s.m;
  p = s.p;
  size = s.size;
  seed = s.seed;
  pdf = new double[size];
  gsl_rng_set(rng,seed);
  for (uint i=0; i<size; i++){
    pdf[i] = s.pdf[i];
  }
  gen = gsl_ran_discrete_preproc(size, pdf);
  return *this;
}

// Access
combination sampler_exact::get(){
  combination state(m,p);
  state.fromindex(gsl_ran_discrete(rng, gen));
  return state;
}

//---approximate rejection sampling---//
// Constructors
sampler_reject::sampler_reject(){
  u = matrix<std::complex<double> >(1,1);
  m = 1;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  seed = 0;
  gsl_rng_set(r, seed);
}

sampler_reject::sampler_reject(const sampler_reject& s){
  u = s.u;
  m = s.m;
  seed = s.seed;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
}

sampler_reject::sampler_reject(matrix<std::complex<double> > mat, uint init){
  u = mat;
  m = u.size();
  seed = init;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
}

// Destructor
sampler_reject::~sampler_reject(){
  gsl_rng_free(r);
}

// Overloads
sampler_reject sampler_reject::operator=(const sampler_reject& s){
  gsl_rng_free(r);
  u = s.u;
  m = s.m;
  seed = s.seed;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
  return *this;
}

// Access
combination sampler_reject::get(uint p){
  uint size = choose(m,p);
  matrix<std::complex<double> > submat(p);
  bool rtn=true;
  combination c(m,p);
  double prob, rng, threshold=1./size;
  std::complex<double> amp;
  uint samp;

  while (rtn){
    samp = (uint) (gsl_rng_uniform(r)*size);
    c.fromindex(samp);
    for (uint i=0; i<p; i++){
      for (uint j=0; j<p; j++){
        submat[i*p+j] = u[i*m+c[j]];
      }
    }
    amp = permanent(submat);
    prob = std::real(amp*std::conj(amp));
    if (prob>threshold){
      rtn = false;
    }
    else{
      rng = gsl_rng_uniform(r)*threshold;
      if (rng < prob){
        rtn = false;
      }
    }
  }
  return c;
}

//---classical sampling---//
// Constructors
sampler_classical::sampler_classical(){
  u = matrix<double>(1,1);
  m = 1;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  seed = 0;
  gsl_rng_set(r,seed);
}

sampler_classical::sampler_classical(const sampler_classical& s){
  u = s.u;
  m = s.m;
  seed = s.seed;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r,seed);
}

sampler_classical::sampler_classical(matrix<std::complex<double> > mat,
    uint init){
  m = mat.size();
  u = matrix<double>(m);
  for (uint i=0; i<m*m; i++){
    u[i] = std::real(mat[i]*std::conj(mat[i]));
  }
  seed = init;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r,seed);
}

// Destructor
sampler_classical::~sampler_classical(){
  gsl_rng_free(r);
}

// Overloads
sampler_classical sampler_classical::operator=(const sampler_classical& s){
  u = s.u;
  m = u.size();
  seed = s.seed;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
  return *this;
}

// Access
combination sampler_classical::get(uint nphotons){
  combination c(m,nphotons);
  uint prev, curr;
  bool collision=true;
  double *pdf=new double[m];
  std::vector<uint> list(nphotons);
  gsl_ran_discrete_t *gen;

  while (collision){
    for (uint i=0; i<nphotons; i++){
      for (uint j=0; j<m; j++){
        pdf[j] = u[j*m+i];
      }
      gen = gsl_ran_discrete_preproc(m,pdf);
      // Sample from the 1 photon distribution
      list[i] = gsl_ran_discrete(r, gen);
      gsl_ran_discrete_free(gen);
    }
    std::sort(list.begin(), list.end());
    // Check for duplicates
    collision = false;
    prev = list[0];
    for (uint i=1; i<nphotons; i++){
      curr = list[i];
      if (prev==curr){
        collision = true;
        break;
      }
      prev = curr;
    }
  }
  for (uint i=0; i<nphotons; i++){
    c[i] = list[i];
  }
  delete[] pdf;
  return c;
}

//---uniform sampling---//
// Constructors
sampler_uniform::sampler_uniform(){
  m = 1;
  seed = 0;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
}

sampler_uniform::sampler_uniform(const sampler_uniform& s){
  m = s.m;
  seed = s.seed;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
}

sampler_uniform::sampler_uniform(uint nmodes, uint init){
  m = nmodes;
  seed = init;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
}

// Destructor
sampler_uniform::~sampler_uniform(){
  gsl_rng_free(r);
}

// Overloads
sampler_uniform sampler_uniform::operator=(const sampler_uniform& s){
  gsl_rng_free(r);
  m = s.m;
  seed = s.seed;
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
  return *this;
}

// Access
combination sampler_uniform::get(uint nphotons){
  uint idx = gsl_rng_uniform_int(r, choose(m, nphotons));
  combination c(m, nphotons);
  c.fromindex(idx);
  return c;
}





