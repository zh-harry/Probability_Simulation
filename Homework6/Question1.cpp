// Route-1 bus departs from terminal regularly every hour. Route-2 bus departs from
// terminal with random exponential time between departures, one departure per hour
// on average. Paul arrives at the terminal at uniform random time.
//
// (a) What is the probability that he sees route-1 bus departs first?
// (b) What is the probability that he sees route-1 bus departs first given that route-2
//     bus departs within an hour?

#include <iostream>
#include <random>

int main(){
    // set random seed
    std::random_device rd;
    std::mt19937 gen(rd());

    // waiting time for route-1 and route-2
    double T1,T2;

    // generate value on uniform distribution
    std::uniform_real_distribution<> Uni(0.0, 1.0);
    
    // generate value on exponential distribution
    double lambda = 1.0;
    std::exponential_distribution<> Exp(lambda);

    // simulate the results
    int samples = 10000, success = 0, valid_condition = 0,success_condition = 0;
    for(int i = 0;i < samples;++i){
        T1 = Uni(gen);
        T2 = Exp(gen);

        // for problem (a) (no condition)
        if(T1 < T2) ++success;

        //for problem (b) (given condition)
        if(T2 <= 1.0){
            ++valid_condition;
            if(T1 < T2) ++success_condition;
        }
    }

    std::cout << "(a) Probability that he sees route-1 bus departs first" << std::endl;
    std::cout << "ANS: " << (double)success/samples << std::endl;
    std::cout << "(a) probability that he sees route-1 bus departs first given that route-2" << std::endl;
    std::cout << "    bus departs within an hour" << std::endl;
    std::cout << "ANS: " << (double)success_condition/valid_condition << std::endl;
    
    return 0;
}