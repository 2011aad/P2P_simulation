#ifndef __FILEQUEUE_H__
#define __FILEQUEUE_H__

#include "file.h"
#include <queue>

using namespace std;

class FileQueue{
public:
    void add(const File &f);

    File front() const;

    void remove_front();

    bool empty() const;

    int size() const;

private:
    queue<File> file_queue;
};

#endif // __FILEQUEUE_H__
