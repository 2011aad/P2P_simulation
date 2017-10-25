#include "file.h"

bool File::hasEmptyBlock() const{
    return !empty_blocks.empty();
}

Block& File::getEmptyBlock(){
    int x = empty_blocks.front();
    empty_blocks.pop();
    return all_blocks[x];
}

void File::returnEmptyBlock(const Block &b){
    if(b.id<0 || b.id>numOfBlock) return;
    all_blocks[b.id] = b;
    empty_blocks.push(b.id);
}
