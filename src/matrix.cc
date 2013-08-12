// matrix.cc
// specialised matrix functions

#include "heads/matrix.h"

matrix<std::complex<double> > haar(uint n, uint seed){
  gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
  matrix<std::complex<double> > m(n);
  std::complex<double> z,ii,ij;
  double x,y;
  gsl_rng_set(r, seed);
  // Generate Gaussian random matrix
  for (uint i=0; i<m.size()*m.size(); i++){ 
    x = gsl_ran_gaussian(r, 0.5);
    y = gsl_ran_gaussian(r, 0.5);
    z = std::complex<double>(x, y);
    m[i] = z;
  }
  gsl_rng_free(r);
  // Apply Gram-Schmidt
  for (uint i=0; i<n; i++){
    // Normalise the i-th row
    ii = 0;
    for (uint k=0; k<n; k++){
      ii += std::conj(m[i*n+k])*m[i*n+k];
    }
    ii = std::sqrt(ii);
    for (uint k=0; k<n; k++){
      m[i*n+k] = m[i*n+k]/ii;
    }
    for (uint j=i+1; j<n; j++){
      // Compute the projection
      ij = 0;
      for (uint k=0; k<n; k++){
        ij += std::conj(m[i*n+k])*m[j*n+k];
      }
      // Subtract the projection
      for (uint k=0; k<n; k++){
        m[j*n+k] = m[j*n+k]-ij*m[i*n+k];
      }
    }
  }
  return m;
}
