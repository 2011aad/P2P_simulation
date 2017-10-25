#ifndef __BLOCK_H__
#define __BLOCK_H__


class Block{
public:
    Block():block_size(1), downloaded_size(0),id(-1){}
    explicit Block(double x):block_size(x), downloaded_size(0),id(-1){}
    Block(int i, double x):block_size(x), downloaded_size(0),id(i){}

    Block(const Block &b):block_size(b.block_size), downloaded_size(b.downloaded_size), id(b.id){}

    Block& operator=(const Block& b){
        if(this==&b) return *this;

        block_size = b.block_size;
        downloaded_size = b.downloaded_size;
        id = b.id;
        return *this;
    }

    double remainSize() const {return block_size-downloaded_size;}

    double block_size;
    double downloaded_size;
    int id;
};



#endif // __BLOCK_H__
