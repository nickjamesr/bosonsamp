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
  combination c(m,p);
  std::complex<double> z;
  double cumulative=0;
  uint k,idx,progress=2;

  initscr();
  cbreak();
  noecho();
  curs_set(0);
  printw("Building cdf\n");
  addch('[');
  mvprintw(1,51,"]");
  addch('0');
  addch('%');
  refresh();

  seed = init;
  size = choose(m,p);
  cdf = new double[size];
  r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r, seed);
  // Generate the cdf...
  k = 0;
  do{
    while (100*k/(double)size > progress){
      mvprintw(1,progress/2,"#");
      mvprintw(1,52,"%d",progress);
      addch('%');
      progress += 2;
      refresh();
    }
    idx = 0;
    for (uint i=0; i<p; i++){
      for (uint j=0; j<p; j++){
        submat[idx] = mat[i*m+c[j]];
        idx++;
      }
    }
    z = permanent(submat);
    cumulative += std::real(z*std::conj(z));
    cdf[k] = cumulative;
    k++;
  } while (c.next());
  for (uint i=0; i<size; i++){
    cdf[i] /= cumulative;
  }
  endwin();
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
combination sampler_exact::get(){
  double x;
  uint lo=0,hi=size-1,mid;
  combination state(m,p);
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

// Overloads
sampler_reject sampler_reject::operator=(const sampler_reject& s){
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


