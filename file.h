#ifndef __FILE_H__
#define __FILE_H__

#include "block.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

class File{
public:
    File(){}
    File(int n):numOfBlock(n), remain_block(n){
        for(int i=0;i<n;++i){
            empty_blocks.push(i);
            all_blocks.push_back(Block(i, 1));
        }
    }

    File(const File &f):numOfBlock(f.numOfBlock), empty_blocks(f.empty_blocks), remain_block(f.remain_block),all_blocks(f.all_blocks){}

    File& operator=(const File& f){
        if(this==&f) return *this;

        numOfBlock = f.numOfBlock;
        empty_blocks = f.empty_blocks;
        remain_block = f.remain_block;
        all_blocks.assign(f.all_blocks.begin(), f.all_blocks.end());

        return *this;
    }

    bool hasEmptyBlock() const;

    Block& getEmptyBlock();

    void returnEmptyBlock(const Block &b);

    bool allBlockServed() const {return remain_block==0;}

    void blockServed(const Block &b){
        --remain_block;
        if(b.id>=0 && b.id<numOfBlock){
            all_blocks[b.id] = b;
        }
    }

    int remainBlockNumber() const {return remain_block;}

private:
    int numOfBlock;
    queue<int> empty_blocks;
    int remain_block;
    vector<Block> all_blocks;
};

#endif // __FILE_H__
