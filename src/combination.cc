// combination.cc
// definitions for combination class

#include "heads/combination.h"

combination::combination(){
  m=0;
  p=0;
  data = new uint[0];
}

combination::combination(uint i, uint j){
  m = i;
  p = j;
  data = new uint[p];
  for (uint i=0; i<p; i++){
    data[i] = i;
  }
}

combination::combination(const combination& c){
  m = c.m;
  p = c.p;
  data = new uint[p];
  for (uint i=0; i<p; i++){
    data[i] = c.data[i];
  }
}

// destructor
combination::~combination(){
  delete[] data;
}

// overloads
combination combination::operator=(const combination& c){
  delete[] data;
  m = c.m;
  p = c.p;
  data = new uint[p];
  for (uint i=0; i<p; i++){
    data[i] = c.data[i];
  }
  return *this;
}

// access
uint& combination::operator[](uint i) const{
  return data[i];
}

// output
void combination::print() const{
  std::cout << "combination (" << m << "," << p << ") {" << std::endl;
  for (uint i=0; i<p; i++){
    std::cout << " " << data[i] << std::endl;
  }
  std::cout << "}" << std::endl;
}

// initialisation
void combination::first(){
  for (uint i=0; i<p; i++){
    data[i] = i;
  }
}

void combination::last(){
  for (uint i=0; i<p; i++){
    data[i] = m+i-p;
  }
}

// iteration
bool combination::prev(){
  for (uint i=0; i<p-1; i++){
    if (data[p-i-1]>data[p-i-2]+1){
      data[p-i-1]--;
      for (uint j=p-i; j<p; j++){
        data[j] = m+j-p;
      }
      return true;
    }
  }
  if (data[0]>0){
    data[0]--;
    for (uint j=1; j<p; j++){
      data[j] = m+j-p;
    }
    return true;
  }
  return false;
}

bool combination::next(){
  for (uint i=0; i<p; i++){
    if (data[p-i-1]<m-i-1){
      data[p-i-1]++;
      for (uint j=p-i; j<p; j++){
        data[j] = data[p-i-1]+j+i+1-p;
      }
      return true;
    }
  }
  return false;
}


