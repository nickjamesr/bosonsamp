// combinatorics.cc
// definitions for combinatorics classes and functions

#include "heads/combinatorics.h"

//---functions---//
long unsigned int choose(uint n, uint r){
  double out=1;
  if (n<r){
    return 0;
  }
  for (uint i=1; i<=(n-r); i++){
    out *= (i+r)/(double) i;
  }
  return (long unsigned int)(out+0.5);
}

//---combination class---//
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

long unsigned int combination::index(){
  long unsigned int out=0;
  long unsigned int max = choose(m,p);
  for (uint i=1; i<=p; i++){
    out += choose(m-data[p-i]-1,i);
  }
  return max-out-1;
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

void combination::fromindex(uint idx){
  uint n=m,r=p,i=0,y=0,max=choose(m,p);
  if (idx>=max){
    std::cerr << "Index out of range" << std::endl;
    return;
  }
  idx = max-idx-1;
  while (n>0){
    if (n>r && r>=0){
      y = choose(n-1,r);
    }
    else{
      y = 0;
    }
    if (idx>=y){
      idx=idx-y;
      data[i] = m-n;
      r--;
      i++;
    }
    n--;
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

//---multiset class---//

multiset::multiset(){
  m=0;
  p=0;
  data = new uint[0];
}

multiset::multiset(uint i, uint j){
  m = i;
  p = j;
  data = new uint[p];
  for (uint i=0; i<p; i++){
    data[i] = 0;
  }
}

multiset::multiset(const multiset& c){
  m = c.m;
  p = c.p;
  data = new uint[p];
  for (uint i=0; i<p; i++){
    data[i] = c.data[i];
  }
}

// destructor
multiset::~multiset(){
  delete[] data;
}

// overloads
multiset multiset::operator=(const multiset& c){
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
uint& multiset::operator[](uint i) const{
  return data[i];
}

long unsigned int multiset::index(){
  long unsigned int out=0;
  long unsigned int max = choose(m+p-1,p);
  for (uint i=1; i<=p; i++){
    out += choose(m-data[p-i]+i-2,i);
  }
  return max-out-1;
}

// output
void multiset::print() const{
  std::cout << "multiset (" << m << "," << p << ") {" << std::endl;
  for (uint i=0; i<p; i++){
    std::cout << " " << data[i] << std::endl;
  }
  std::cout << "}" << std::endl;
}

// initialisation
void multiset::first(){
  for (uint i=0; i<p; i++){
    data[i] = 0;
  }
}

void multiset::last(){
  for (uint i=0; i<p; i++){
    data[i] = m-1;
  }
}

void multiset::fromindex(uint idx){
  uint n=m+p-1,r=p,i=0,y=0,max=choose(m+p-1,p);
  if (idx>=max){
    std::cerr << "Index out of range" << std::endl;
    return;
  }
  idx = max-idx-1;
  while (n>0){
    if (n>r && r>=0){
      y = choose(n-1,r);
    }
    else{
      y = 0;
    }
    if (idx>=y){
      idx=idx-y;
      data[i] = m+p-1-n-i;
      r--;
      i++;
    }
    n--;
  }
}

// iteration
bool multiset::prev(){
  for (uint i=0; i<p-1; i++){
    if (data[p-i-1]>data[p-i-2]){
      data[p-i-1]--;
      for (uint j=p-i; j<p; j++){
        data[j] = m-1;
      }
      return true;
    }
  }
  if (data[0]>0){
    data[0]--;
    for (uint j=1; j<p; j++){
      data[j] = m-1;
    }
    return true;
  }
  return false;
}

bool multiset::next(){
  for (uint i=0; i<p; i++){
    if (data[p-i-1]<m-1){
      data[p-i-1]++;
      for (uint j=p-i; j<p; j++){
        data[j] = data[p-i-1];
      }
      return true;
    }
  }
  return false;
}

