#ifndef __SERVERPOOL_H__
#define __SERVERPOOL_H__

#include "Server.h"
#include <queue>
#include <vector>

using namespace std;

class ServerPool{
public:
    Server getServer();

    bool hasFreeServer() const;

    int add(const Server& s);

    void remove(int server_id);

    void free(int server_id);

    int serverNumber() const;

    int freeServerNumber() const;

private:

    vector<Server> all_server;
    queue<int> free_server_index;
    queue<int> removed_server_index;
};

#endif // __SERVERPOOL_H__
