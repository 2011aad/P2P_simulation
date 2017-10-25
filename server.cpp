
#include "server.h"

//exponential service without block size
pair<double, bool> Server::upload(double start_time, int block_num){
    expdist = exponential_distribution<double>(service_rate);
    double service_finish_time = start_time + expdist(rand_engine);

    if(leave_time>service_finish_time){
        return make_pair(service_finish_time, true);
    }
    return make_pair(leave_time+(1e-3), false);
}

//constant service rate with block size
pair<double, bool> Server::upload(double start_time, Block& b){
    double service_finish_time = start_time + b.remainSize()/service_rate;

    if(leave_time>service_finish_time){
        b.downloaded_size = b.block_size;
        return make_pair(service_finish_time, true);
    }

    b.downloaded_size += (leave_time-start_time)*service_rate;
    return make_pair(leave_time+(1e-3), false);
}
