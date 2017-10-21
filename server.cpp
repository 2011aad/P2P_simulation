
#include "server.h"

pair<double, bool> Server::upload(double start_time, int block_num){
    expdist = exponential_distribution<double>(service_rate);
    double service_finish_time = start_time + expdist(rand_engine);

    if(leave_time>service_finish_time){
        return make_pair(service_finish_time, true);
    }
    return make_pair(leave_time+(1e-3), false);
}
