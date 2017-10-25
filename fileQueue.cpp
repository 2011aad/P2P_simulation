
#include "fileQueue.h"
#include <iostream>

void FileQueue::add(const File &f){
    file_queue.push(f);
}

File FileQueue::front() const{
    File f = file_queue.front();
    return f;
}

void FileQueue::remove_front(){
    file_queue.pop();
}

bool FileQueue::empty() const{
    return file_queue.empty();
}

int FileQueue::size() const{
    return file_queue.size();
}
