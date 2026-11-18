#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
  return std::pow(mu, k) * std::exp(-mu) / std::tgamma(k + 1.0);
}

int main() {
  std::ifstream fin("sums.txt");
  // std::ofstream fout("hist.txt");
  std::ofstream fout("histpoi.txt");
  std::vector<int> counts(11);
  int a;         
  int n = 0;
  double sum = 0;
  while (fin >> a) {
    counts.at(a) += 1;               
      ++n;               
      sum += a;               
  }
  fin.close();

  double mean = sum/n;
  std::cout << "N = " << n << ", mean = " << mean << std::endl;

  for (unsigned int k = 0; k < counts.size(); ++k) {
    std::cout << k << ":" << counts[k] << std::endl;
    //fout << k << " " << counts[k] << std::endl;
    fout << k << " " << counts[k] << " " << n * poisson(mean,k)<< std::endl;
   }
  
}
