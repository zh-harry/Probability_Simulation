// Let Nj be the number of times that face j shows up in n throws of a fair dice. Find
// 
// (a) var(N1)
// (b) var(N1 + N2)
// (c) cov(N1, N2)
// (d) cov(N1 + N2, N5 + N6)

#include <iostream>
#include <random>

constexpr int trials = 10000;
constexpr int n = 13;

std::vector<int> results_N1(n+1, 0);
std::vector<int> results_N2(n+1, 0);
std::vector<int> results_N1_plus_N2(n+1, 0);
std::vector<int> results_N5_plus_N6(n+1, 0);
std::vector<int> results_N1_plus_N2_N5_plus_N6(n+1, 0);

double Mean(const std::vector<int>& v){
    int sz = v.size();
    int sum = 0;

    for(int i = 1;i < sz;++i)
        sum += i * v[i];
    
    double E = (double)sum / trials;
    return E;
}

double MeanForSquare(const std::vector<int>& v){
    int sz = v.size();
    int sum = 0;

    for(int i = 1;i < sz;++i)
        sum += (i * i) * v[i];
    
    double E = (double)sum / trials;
    return E;
}

void GeneratingResults(std::mt19937& gen){
    // simulate the results
    for(int i = 0;i < trials;++i){
        // generate value on binomial distribution
        // strats with N1
        std::binomial_distribution<> N1(n, 1.0/6.0);
        int n1 = N1(gen);
        ++results_N1[n1];

        // after deducting N1 from total times
        // times of N2 still follow binomial distribution
        // but with larger probabity 1/(6-1)
        std::binomial_distribution<> N2(n-n1, 1.0/5.0);
        int n2 = N2(gen);
        ++results_N2[n2];

        std::binomial_distribution<> N5(n-n1-n2, 1.0/4.0);
        int n5 = N5(gen);

        std::binomial_distribution<> N6(n-n1-n2-n5, 1.0/3.0);
        int n6 = N6(gen);

        ++results_N1_plus_N2[n1 + n2];
        ++results_N5_plus_N6[n5 + n6];
        ++results_N1_plus_N2_N5_plus_N6[n1 + n2 + n5 + n6];
    }
}

double Var(const std::vector<int>& X){
    double EX = Mean(X);
    double EXsquare = MeanForSquare(X);
    double var = EXsquare - (EX * EX);
    return var;
}

double Cov(const std::vector<int>& X, const std::vector<int>& Y, 
            const std::vector<int> X_plus_Y){
    double varX_plus_Y = Var(X_plus_Y);
    double varX = Var(X);
    double varY = Var(Y);
    double cov = (varX_plus_Y - varX - varY)/2;
    return cov;
}

int main(){
    // set random seed
    std::random_device rd;
    std::mt19937 gen(rd());

    GeneratingResults(gen);
    
    double varN1 = Var(results_N1);
    double varN1_plus_N2 = Var(results_N1_plus_N2);
    double covN1_N2 = Cov(results_N1, results_N2, results_N1_plus_N2);
    double covN1_plus_N2_N5_plus_N6 = Cov(results_N1_plus_N2, results_N5_plus_N6, 
                                            results_N1_plus_N2_N5_plus_N6);

    // output answer
    std::cout << "(a) var(N1) = " << varN1 << std::endl;
    std::cout << "(b) var(N1 + N2) = " << varN1_plus_N2 << std::endl;
    std::cout << "(c) cov(N1, N2) = " << covN1_N2 << std::endl;
    std::cout << "(d) cov(N1 + N2, N5 + N6) = " << covN1_plus_N2_N5_plus_N6 << std::endl;

    return 0;
}