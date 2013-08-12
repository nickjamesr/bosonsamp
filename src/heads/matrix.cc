// matrix.h
// Definitions for my (minimal) matrix class

// Constructors
template <class T>
matrix<T>::matrix(){
  data = new T[0];
  dim = 0;
}

template <class T>
matrix<T>::matrix(uint n){
  data = new T[n*n];
  dim = n;
}

template <class T>
matrix<T>::matrix(uint n, T t){
  data = new T[n*n];
  dim = n;
  for (uint i=0; i<n*n; i++){
    data[i] = t;
  }
}

template <class T>
matrix<T>::matrix(const matrix<T>& t){
  dim = t.dim;
  data = new T[dim*dim];
  for (uint i=0; i<dim*dim; i++){
    data[i] = t.data[i];
  }
}

// Destructor
template <class T>
matrix<T>::~matrix(){
  delete[] data;
}

// Overloads
template <class T>
matrix<T> matrix<T>::operator=(const matrix<T> &t){
  delete[] data;
  dim = t.dim;
  data = new T[dim*dim];
  for (uint i=0; i<dim*dim; i++){
    data[i] = t.data[i];
  }
  return *this;
}

// Access
template <class T>
T& matrix<T>::operator[](uint i){
  return data[i];
}

template <class T>
uint matrix<T>::size(){
  return dim;
}

// Output
template <class T>
void matrix<T>::print() const{
  std::cout << "matrix [\n";
  for (uint i=0; i<dim; i++){
    for (uint j=0; j<dim; j++){
      std::cout << " " << data[i*dim+j];
    }
    std::cout << std::endl;
  }
  std::cout << "]" << std::endl;
}




