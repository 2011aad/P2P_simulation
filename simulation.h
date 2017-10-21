#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "serverPool.h"
#include "fileQueue.h"
#include "event.h"
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

class Simulation{

public:
    void run();

    void Observe();

    double meanQueueLength() const{return total_queue_length/observe_counter;}

    double meanServerNumber() const {return total_server_number/observe_counter;}

    Simulation():numOfBlock(100), numOfFile(10000), lambda_c(10), lambda_s(10), mu_c(10), mu_s(1){
        rand_engine.seed(time(0));
    }

    Simulation(int bn, int fn, double lc, double ls, double mc, double ms):
        numOfBlock(bn), numOfFile(fn), lambda_c(lc), lambda_s(ls), mu_c(mc), mu_s(ms){
        rand_engine.seed(time(0));
    }
private:
    const int numOfBlock;
    const int numOfFile;
    const double lambda_c;
    const double lambda_s;
    const double mu_c;
    const double mu_s;
    default_random_engine rand_engine;
    exponential_distribution<double> expdist;
    double total_queue_length = 0;
    int observe_counter = 0;
    double total_server_number = 0;

    ServerPool serv_pool;
    FileQueue file_queue;
    priority_queue<Event, vector<Event>, greater<Event>> event_queue;
};

#endif // __SIMULATION_H__
