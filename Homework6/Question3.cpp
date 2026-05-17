// Let X and Y be independent random variables with identical distribution. Define
// M = max(X, Y) and L = min(X, Y). Find cov(M, L) for the following cases
//
// (a) X, Y ~ Exp(1)
// (b) X, Y ~ N(0, 1)

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

double Mean(const std::vector<double>& v){
    int n = v.size();
    double sum = 0.0;
    for(int i = 0;i < n;sum += v[i++]);
    return sum/n;
}

void PromblemA(std::mt19937& gen){
    // generate value on exponential distribution
    double lambda = 1.0;
    std::exponential_distribution<> X(lambda);
    std::exponential_distribution<> Y(lambda);

    // simulate the results
    int samples = 10000;
    std::vector<double> M(samples);
    std::vector<double> L(samples);
    std::vector<double> ML(samples);
    for(int i = 0;i < samples;++i){
        double x = X(gen);
        double y = Y(gen);
        M[i] = std::max(x,y);
        L[i] = std::min(x,y);
        ML[i] = M[i] * L[i];
    }

    // calculate the covariance
    double E_M = Mean(M);
    double E_L = Mean(L);
    double E_ML = Mean(ML);
    double cov_ML = E_ML - (E_M * E_L);

    std::cout << "(a) X, Y ~ Exp(0, 1)" << std::endl;
    std::cout << "cov(M, L) = " << cov_ML << std::endl;
}

void PromblemB(std::mt19937& gen){
    // generate value on normal distribution
    std::normal_distribution<> X(0.0, 1.0);
    std::normal_distribution<> Y(0.0, 1.0);

    // simulate the results
    int samples = 10000;
    std::vector<double> M(samples);
    std::vector<double> L(samples);
    std::vector<double> ML(samples);
    for(int i = 0;i < samples;++i){
        double x = X(gen);
        double y = Y(gen);
        M[i] = std::max(x,y);
        L[i] = std::min(x,y);
        ML[i] = M[i] * L[i];
    }

    // calculate the covariance
    double E_M = Mean(M);
    double E_L = Mean(L);
    double E_ML = Mean(ML);
    double cov_ML = E_ML - (E_M * E_L);

    std::cout << "(b) X, Y ~ N(1)" << std::endl;
    std::cout << "cov(M, L) = " << cov_ML << std::endl;
}

int main(){
    // set random seed
    std::random_device rd;
    std::mt19937 gen(rd());

    PromblemA(gen);
    PromblemB(gen);

    return 0;
}