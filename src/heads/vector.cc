// vector.h
// Definitions for my (minimal) vector class

// Constructors
template <class T>
vector<T>::vector(){
  data = new T[0];
  len = 0;
}

template <class T>
vector<T>::vector(uint n){
  data = new T[n];
  len = n;
}

template <class T>
vector<T>::vector(uint n, T t){
  data = new T[n];
  len = n;
  for (uint i=0; i<n; i++){
    data[i] = t;
  }
}

template <class T>
vector<T>::vector(const vector<T>& t){
  len = t.len;
  data = new T[len];
  for (uint i=0; i<len; i++){
    data[i] = t.data[i];
  }
}

// Destructor
template <class T>
vector<T>::~vector(){
  delete[] data;
}

// Overloads
template <class T>
vector<T> vector<T>::operator=(const vector<T> &t){
  delete[] data;
  len = t.len;
  data = new T[len];
  for (uint i=0; i<len; i++){
    data[i] = t.data[i];
  }
  return *this;
}

// Access
template <class T>
T& vector<T>::operator[](uint i){
  return data[i];
}

// Output
template <class T>
void vector<T>::print(){
  std::cout << "vector [\n";
  for (uint i=0; i<len; i++){
    std::cout << " " << data[i] << "\n";
  }
  std::cout << "]" << std::endl;
}

