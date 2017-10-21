#ifndef __FILE_H__
#define __FILE_H__

#include <queue>

using namespace std;

class File{
public:
    File(){}
    File(int n):numOfBlock(n), remain_block(n){
        for(int i=0;i<n;++i){
            empty_blocks.push(i);
        }
    }

    File(const File &f):numOfBlock(f.numOfBlock), empty_blocks(f.empty_blocks), remain_block(f.remain_block){}

    bool hasEmptyBlock() const;

    int getEmptyBlock();

    void returnEmptyBlock(int block_num);

    bool allBlockServed() const {return remain_block==0;}

    void blockServed(int block_num){--remain_block;}

    int remainBlockNumber() const {return remain_block;}

private:
    int numOfBlock;
    queue<int> empty_blocks;
    int remain_block;
};

#endif // __FILE_H__
