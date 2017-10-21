#ifndef __EVENT_H__
#define __EVENT_H__

#include "server.h"
#include <string>

class Server;

using namespace std;

class Event{

public:
    enum{FILE_ARRIVAL=0, SERVER_ARRIVAL=1, BLOCK_SERVED=2, SERVER_LEAVE=3, RELEASE_BLOCK=4};

    Event(){}
    Event(unsigned int e_type, double time, int ser=-1, int bn=-1):event_type(e_type), end_time(time), server_index(ser), block_num(bn){}

    Event(const Event &other):event_type(other.event_type), end_time(other.end_time), server_index(other.server_index), block_num(other.block_num){}

    bool operator<(const Event& e) const{
        return end_time<e.end_time;
    }

    bool operator>(const Event& e) const{
        return end_time>e.end_time;
    }

    double getTime() const {return end_time;}

    string getType(){
        switch( event_type){
            case FILE_ARRIVAL: return "FILE_ARRIVAL";
            case SERVER_ARRIVAL: return "SERVER_ARRIVAL";
            case BLOCK_SERVED: return "BLOCK_SERVED";
            case SERVER_LEAVE: return "SERVER_LEAVE";
            case RELEASE_BLOCK: return "RELEASE_BLOCK";
        }
        return "NONE";
    }

    unsigned int event_type;
private:
    double end_time;

public:
    int server_index;
    int block_num;
};

#endif // __EVENT_H__






