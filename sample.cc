#include <iostream>
#include <fstream>
#include <cmath>

int main() {
  std::ifstream fin("sums.txt");
  double a;
  double sum = 0;
  int n = 0;
  while (fin >> a) {
    sum += a;
    ++n;
  }
  fin.close();
  double mean = sum / n;
  std::cout << "N = " << n << std::endl;
  std::cout << "mean = " << mean << std::endl;


  //std::ifstream fin("sums.txt");
  fin.open("sums.txt");
  a=0;
  double x=0;
  double y=0;
  while (fin>>a){
    y= (a - mean) * (a - mean) ;
    x += y;   
  }
  fin.close();
  double V= x/n ;
  std::cout << "Variance = " << V <<std::endl;
  std::cout <<"sigma =" << std::sqrt(V) << std::endl;    
  
}
