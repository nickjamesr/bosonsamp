// permanent.cc
// definitions for permanent calculations

template <class T>
T permanent1(matrix<T> M){
  return M[0];
}

template <class T>
T permanent2(matrix<T> M){
  return M[0]*M[3]+M[1]*M[2];
}

template <class T>
T permanent3(matrix<T> M){
  return M[0]*(M[4]*M[8]+M[5]*M[7])+
         M[1]*(M[5]*M[6]+M[3]*M[8])+
         M[2]*(M[3]*M[7]+M[4]*M[6]);
}

template <class T>
T permanent4(matrix<T> M){
  return M[0]*(M[5]*(M[10]*M[15]+M[11]*M[14])+
               M[6]*(M[11]*M[13]+M[9]*M[15])+
               M[7]*(M[9]*M[14]+M[10]*M[13]))+
         M[1]*(M[4]*(M[10]*M[15]+M[11]*M[14])+
               M[6]*(M[11]*M[12]+M[8]*M[15])+
               M[7]*(M[8]*M[14]+M[10]*M[12]))+
         M[2]*(M[4]*(M[9]*M[15]+M[11]*M[13])+
               M[5]*(M[11]*M[12]+M[8]*M[15])+
               M[7]*(M[8]*M[13]+M[9]*M[12]))+
         M[3]*(M[4]*(M[9]*M[14]+M[10]*M[13])+
               M[5]*(M[8]*M[14]+M[10]*M[12])+
               M[6]*(M[8]*M[13]+M[9]*M[12]));
}

template <class T>
T permanent_naive(matrix<T> M){
  uint n = M.size();
  if (n==0){
    return 0;
  }
  else if (n==1){
    return M[0];
  }
  else if (n==2){
    return permanent2(M);
  }
  else if (n==3){
    return permanent3(M);
  }
  else if (n==4){
    return permanent4(M);
  }
  else{
    matrix<T> submat(n-1);
    T sum = 0;
    uint idx,odx; // (in and out indices)
    for (uint k=0; k<n; k++){
      // Build submatrix
      // first partial block (if necessary) // i=0
      for (uint j=0; j<k; j++){
        submat[j] = M[n+j];
      }
      // main loop
      idx = k;
      odx = n+k+1;
      for (uint i=0; i<(n-2); i++){
        for (uint j=0; j<(n-1); j++){
          submat[idx] = M[odx];
          idx++; odx++;
        }
        odx++;
      }
      // last partial block (if necessary)  // i=n-2
      for (uint j=k; j<n-1; j++){
        submat[idx] = M[odx];
        idx++; odx++;
      }
      sum += M[k]*permanent_naive(submat);
    }
    return sum;
  }
}

template <class T>
T permanent_ryser(matrix<T> M){
  T perm=0, parity=1, sum=0, prod=1;
  uint n=M.size();
  combination c;
  // Loop over subsets
  for (uint k=1; k<=n; k++){
    parity*=-1;
    c = combination(n, k);
    do{
      // Calculate the product
      prod = 1;
      for (uint i=0; i<n; i++){
        // Calculate the sum
        sum = 0;
        for (uint j=0; j<k; j++){
          sum += M[i*n+j];
        }
        prod *= sum;
      }
      perm += parity*prod;
    } while (c.next());
  }
  return parity*perm;
}

template <class T>
T permanent(matrix<T> M){
  uint n = M.size();
  if (n<=5){
    return permanent_naive(M);
  }
  else{
    return permanent_ryser(M);
  }
}





