#ifndef __SERVER_H__
#define __SERVER_H__


#include "event.h"
#include "block.h"
#include <ctime>
#include <random>

using namespace std;

class Event;

class Server{
public:
    Server():service_rate(1), leave_rate(1), arrive_time(0), is_free(true), is_active(true), id(-1){
        rand_engine.seed(time(0));
        expdist = exponential_distribution<double>(leave_rate);
        leave_time = arrive_time + expdist(rand_engine);
    }

    Server(double sr, double lr, double arr_time):service_rate(sr), leave_rate(lr),arrive_time(arr_time), is_free(true), is_active(true),id(-1){
        rand_engine.seed(time(0));
        expdist = exponential_distribution<double>(leave_rate);
        leave_time = arrive_time + expdist(rand_engine);
    }

    Server(const Server &other):service_rate(other.service_rate), leave_rate(other.leave_rate), arrive_time(other.arrive_time), is_free(other.is_free), is_active(other.is_active),leave_time(other.leave_time),id(other.id){
        rand_engine.seed(time(0));
        expdist = other.expdist;
    }

    Server& operator=(const Server &other){
        if(this==&other) return *this;

        service_rate = other.service_rate;
        leave_rate = other.leave_rate;
        arrive_time = other.arrive_time;
        leave_time = other.leave_time;
        is_free = other.is_free;
        is_active = other.is_active;
        expdist = other.expdist;
        id = other.id;
        return *this;
    }


    pair<double, bool> upload(double start_time, int block_num);
    pair<double, bool> upload(double start_time, Block& b);

private:
    double service_rate;
    double leave_rate;
    double arrive_time;
    default_random_engine rand_engine;
    exponential_distribution<double> expdist;

public:
    bool is_free;
    bool is_active;
    double leave_time;
    int id;
};

#endif // __SERVER_H__
