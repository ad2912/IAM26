#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
    return std::pow(mu, k) * std::exp(-mu) / std::tgamma(k + 1.0);
}

double prob(const std::vector<int>& data, double mu) {
    double likelihood = 1;

    for (int k : data) {
        likelihood = likelihood * poisson(mu, k);
    }

    return likelihood;
}

double nll(const std::vector<int>& data, double mu) {
    double sum = 0;

    for (int k : data) {
        sum = sum + std::log(poisson(mu, k));
    }

    return -2 * sum;
}

int main() {
    std::ifstream fin("sums.txt");
    std::vector<int> data;

    int a;
    int n = 0;
    double sum = 0;

    while (fin >> a) {
        data.push_back(a);
        ++n;
        sum += a;
    }
    fin.close();

    double mean = sum/n;

    std::cout << "L(n bar) = " << prob(data, mean) << std::endl;

    std::ofstream fout("likelihood.txt");
    std::ofstream nllout("nll.txt");
    std::ofstream deltaout("deltanll.txt");

    /*  for (int i = 0; i <= 60; ++i) {
    double mu = i * 0.1;
    double likelihood = prob(data, mu);
    double negativeLogLikelihood = nll(data, mu);

    fout << mu << " " << likelihood << std::endl;
    nllout << mu << " " << negativeLogLikelihood << std::endl;
    }*/

    for (int i = 0; i <= 6000; ++i) {
        double mu = i * 0.001;
        double likelihood = prob(data, mu);
        double negativeLogLikelihood = nll(data, mu);
        double deltanll = nll(data, mu) - nll(data, mean);

        fout << mu << " " << likelihood << std::endl;
        nllout << mu << " " << negativeLogLikelihood << std::endl;
        deltaout << mu << " " << deltanll << std::endl;
    }

    fout.close();
    nllout.close();
    deltaout.close();

    double saturated = 0;

    for (int k : data) {
        saturated = saturated + std::log(poisson(k, k));
    }

    saturated = -2 * saturated;

    double ratio = nll(data, mean) - saturated;

    int ndof = n - 1;

    double z = (ratio - ndof) / std::sqrt(2.0 * ndof);

    std::cout << "-2 ln Lambda = " << ratio << std::endl;
    std::cout << "z = " << z << std::endl;
}
