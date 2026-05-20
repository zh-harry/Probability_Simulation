// Write a pseudo code to sample from Poi(lambda) distribution with a random number 
// generator for Uni(0, 1). Then write a program to generate n samples and compute the
// sample mean and sample variance for lambda = 2 and n = 10000

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

int SampleFromPoisson(double lambda){
    int cnt = 0;
    double cur_time = 0;

    while(lambda >= cur_time){
        double U = (double)rand() / (RAND_MAX + 1.0);

        double inter_arrival = -std::log(U);

        cur_time += inter_arrival;

        if(lambda < cur_time) break;

        ++cnt;
    }

    return cnt;
}

int main(){
    std::srand(time(NULL));

    double lambda = 2;
    int n = 10000;
    std::vector<int> samples(n);

    double sum = 0;
    for(int i = 0;i < n;++i){
        samples[i] = SampleFromPoisson(lambda);
        sum += samples[i];
    }

    double mean = sum/n;
    
    double sum_of_diffsq = 0;
    for(int i = 0;i < n;++i){
        double diff = samples[i]-mean;
        sum_of_diffsq += diff * diff;
    }

    double var = sum_of_diffsq/(n-1);

    std::cout << "========================================\n";
    std::cout << "Sample Mean:\t\t" << mean << '\n';
    std::cout << "========================================\n";
    std::cout << "Sample Variance:\t" << var << '\n';
    std::cout << "========================================\n";

    return 0;
}