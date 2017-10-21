
#include "serverPool.h"

bool ServerPool::hasFreeServer() const{
    return !free_server_index.empty();
}

Server ServerPool::getServer(){
    int index = free_server_index.front();
    free_server_index.pop();
    all_server[index].is_free = false;

    return all_server[index];
}

int ServerPool::add(const Server &s){
    int index = 0;
    if(!removed_server_index.empty()){
        index = removed_server_index.front();
        removed_server_index.pop();
        free_server_index.push(index);
        all_server[index] = s;
    }
    else{
        all_server.push_back(s);
        index = all_server.size()-1;
        free_server_index.push(index);
    }

    all_server[index].id = index;
    return index;
}

void ServerPool::remove(int server_id){
    all_server[server_id].is_active = false;
    removed_server_index.push(server_id);
}

void ServerPool::free(int server_id){
    all_server[server_id].is_free = true;
    free_server_index.push(server_id);
}

int ServerPool::serverNumber() const{
    return all_server.size() - removed_server_index.size();
}


int ServerPool::freeServerNumber() const {
    return free_server_index.size();;
}
