#include "file.h"

bool File::hasEmptyBlock() const{
    return !empty_blocks.empty();
}

int File::getEmptyBlock(){
    int x = empty_blocks.front();
    empty_blocks.pop();
    return x;
}

void File::returnEmptyBlock(int block_num){
    empty_blocks.push(block_num);
}

