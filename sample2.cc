#include <iostream>
#include <fstream>

int main() {
  std::ifstream fin("sums.txt");
  std::ofstream fout("means.txt");
  double a;
  double sum = 0;
  double mean = 0;
  int n = 0;
  while (fin >> a) {
    sum += a;
    ++n;
    if (n == 9) {
      mean = sum / n;
      fout << mean << std::endl;

      std::cout <<"mean ="<< mean << std::endl; 
      sum = 0;
      n = 0;
    }
  }
  fin.close();
  fout.close();

  fin.open("sums.txt");
  std::ifstream fin2("means.txt");
  std::ofstream fout2("variances.txt");
  double x = 0;
  double y = 0;
  double V = 0;
  while (fin >> a) {
    if (n == 0) {
      fin2 >> mean;
    }
    y = (a - mean) * (a - mean);
    x += y;
    ++n;
    if (n == 9) {
      V = x / n;
      fout2 << V << std::endl;
      std::cout <<"Variance =" << V << std::endl; 
      x = 0;
      n = 0;
    }
  }
  fin.close();
  fin2.close();
  fout2.close();
}
